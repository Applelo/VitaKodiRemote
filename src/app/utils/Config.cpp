#include "Config.hh"

Config::Config() {
    sceIoMkdir(CONFIG_DIRECTORY_PATH, 0777);

    SceUID fileHandle = sceIoOpen(CONFIG_FILE_PATH, SCE_O_RDONLY, 0777);
    if (fileHandle < 0) {
        this->create();
    }
    else {
        this->load();
    }
    sceIoClose(fileHandle);

}


void Config::create() {
    ip = "127.0.0.1";
    port = 8080;
    authentication = false;
    username = "kodi";
    password = "";
    firstStart = true;

    configFile = json_pack(
            "{"
            "s:b,"
            "s:{s:s, s:i, s:b, s:s, s:s},"
            "}",
            "firstStart", firstStart,
            "connection",
                    "ip", ip.c_str(), "port", port,
                    "authentication", authentication, "username", username.c_str(), "password", password.c_str()
    );
    json_dump_file(configFile, CONFIG_FILE_PATH, 0);
}

void Config::load() {
    configFile = json_load_file(CONFIG_FILE_PATH, 0, nullptr);
    json_t *connection = json_object_get(configFile, "connection");
    ip = json_string_value(json_object_get(connection, "ip"));
    port = (unsigned int) json_number_value(json_object_get(connection, "ip"));
    authentication = json_boolean_value(json_object_get(connection, "authentication"));
    username = json_string_value(json_object_get(connection, "username"));
    password = json_string_value(json_object_get(connection, "password"));

    firstStart = json_boolean_value(json_object_get(configFile, "firstStart"));
}


void Config::save() {
    firstStart = false;
    configFile = json_pack(
            "{"
            "s:b,"
            "s:{s:s, s:i, s:b, s:s, s:s},"
            "}",
            "firstStart", firstStart,
            "connection",
            "ip", ip.c_str(), "port", port,
            "authentication", authentication, "username", username.c_str(), "password", password.c_str()
    );

    sceIoRemove(CONFIG_FILE_PATH);
    json_dump_file(configFile, CONFIG_FILE_PATH, 0);
}

void Config::setConnection(std::string ip, unsigned port, bool authentication, std::string username, std::string password) {
    this->ip = std::move(ip);
    this->port = port;
    this->authentication = authentication;
    this->username = std::move(username);
    this->password = std::move(password);
}




const std::string &Config::getIp() const {
    return ip;
}

unsigned int Config::getPort() const {
    return port;
}

bool Config::isAuthentication() const {
    return authentication;
}

const std::string &Config::getUsername() const {
    return username;
}

const std::string &Config::getPassword() const {
    return password;
}

bool Config::isFirstStart() const {
    return firstStart;
}

