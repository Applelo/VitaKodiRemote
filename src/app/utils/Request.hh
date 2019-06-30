#ifndef VITAKODIREMOTE_REQUEST_HH
#define VITAKODIREMOTE_REQUEST_HH

#include <psp2/sysmodule.h>
#include <psp2/net/net.h>
#include <psp2/net/netctl.h>
#include <psp2/libssl.h>
#include <psp2/net/http.h>
#include <psp2/io/fcntl.h>
#include <psp2/io/stat.h>
#include <psp2/kernel/threadmgr.h>

#include <jansson.h>
#include <sstream>
#include <cstring>
#include <string>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

#include "kodi/Input.hh"
#include "Config.hh"

class Request {
private:
    json_t *bodyJson;
    std::string bodyString;

    std::ostringstream response;
    json_t *responseJson;


    json_t *params;
    json_t *id;
    std::string method;


    Config *config;

    json_t *post();
    void initNet();
    void terminateNet();
    void cleanUp();
public:
    Request(Config *config);


    bool tryConnection();
    void input(const char *method);


};


#endif //VITAKODIREMOTE_REQUEST_HH
