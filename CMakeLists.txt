cmake_minimum_required(VERSION 3.11)

if (NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    if (DEFINED ENV{VITASDK})
        set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
    else ()
        message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
    endif ()
endif ()

project(VitaKodiRemote)
include("${VITASDK}/share/vita.cmake" REQUIRED)

include(cmake/Config.cmake)
include(cmake/Dependencies.cmake)
include(cmake/Vita3K.cmake)
include(cmake/Files.cmake)
include(cmake/VitaMaterialKit.cmake)

find_package(Git)
if (NOT Git_FOUND)
    message(WARNING "Git not found, using unknown as tag...")
    add_definitions(-DGIT_COMMIT="unknown")
else ()
    execute_process(
            COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
            WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
            OUTPUT_VARIABLE DGIT_COMMIT
            OUTPUT_STRIP_TRAILING_WHITESPACE
            ERROR_QUIET
    )

    add_definitions(-DGIT_COMMIT="${DGIT_COMMIT}")
endif ()


set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -fpermissive -std=gnu11 -Wall ")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fpermissive -std=c++11 -Wall ")

find_package(CURL REQUIRED)
find_package(OpenSSL REQUIRED)
pkg_check_modules(CURLPP REQUIRED curlpp)

add_executable(${PROJECT_NAME}
        src/main.cpp

        ${MKIT_LIB}
        ${MKIT_CORE}
        ${MKIT_UI}
        ${MKIT_UTILS}

        src/app/utils/Config.cpp
        src/app/utils/Request.cpp

        src/app/views/Settings.cpp
        )

#Add definitions
target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_IP="\\"${DEBUG_IP}\\"" DEBUG_PORT=${DEBUG_PORT} VMKIT_VERSION=${VITA_VERSION})
if (CMAKE_BUILD_TYPE MATCHES Debug)
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_APP=1)
    target_link_libraries(${PROJECT_NAME}
            debugnet
            SceNetCtl_stub
            SceNet_stub)
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE DEBUG_APP=0)
endif()


# Library to link to (drop the -l prefix). This will mostly be stubs.
target_link_libraries(${PROJECT_NAME}
        vita2d
        SceDisplay_stub
        SceGxm_stub
        ScePvf_stub
        SceCtrl_stub
        SceTouch_stub
        SceCommonDialog_stub
        SceAppUtil_stub
        SceAppMgr_stub
        SceRegistryMgr_stub
        SceSysmodule_stub
        jansson
        freetype
        png
        jpeg
        z
        m
        c
        SceNet_stub
        SceNetCtl_stub
        SceHttp_stub
        SceSsl_stub
        ${CURLPP_LDFLAGS}
        ${CURL_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        )

vita_create_self(eboot.bin ${PROJECT_NAME})
vita_create_vpk(${PROJECT_NAME}.vpk ${VITA_TITLEID} eboot.bin
        VERSION ${VITA_VERSION}
        NAME ${VITA_APP_NAME}
        FILE ${FILES_SCE_SYS} ${FILES_FONTS} ${FILES_LANGUAGES}
        )

#Send through the FTP
add_custom_target(send
        COMMAND curl -T eboot.bin ftp://${PSVITA_IP}:1337/ux0:/app/${VITA_TITLEID}/
        DEPENDS eboot.bin
        )

add_custom_target(send_vpk
        COMMAND curl -T ${PROJECT_NAME}.vpk ftp://${PSVITA_IP}:1337/ux0:/data/
        DEPENDS ${PROJECT_NAME}.vpk
        )

#Copy to the device
add_custom_target(copy
        COMMAND cp eboot.bin ${PSVITA_VOLUME}app/${VITA_TITLEID}/eboot.bin
        DEPENDS eboot.bin
        )

add_custom_target(copy_vpk
        COMMAND cp ${PROJECT_NAME}.vpk ${PSVITA_VOLUME}data/${VITA_TITLEID}/${PROJECT_NAME}.vpk
        DEPENDS ${PROJECT_NAME}.vpk
        )

#Vita3K
add_custom_target(emulate
        COMMAND cp eboot.bin ${VITA3K_FOLDER_PATH}/eboot.bin
        COMMAND ${VITA3K_APP_PATH} -r ${VITA_TITLEID}
        DEPENDS eboot.bin
        )

add_custom_target(emulate_vpk
        COMMAND ${VITA3K_APP_PATH} ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.vpk
        DEPENDS ${PROJECT_NAME}.vpk
        )

