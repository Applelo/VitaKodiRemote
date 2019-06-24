#include <vitasdk.h>
#include "Config.hh"

Config::Config() {
    SceNetCtlInfo info;
    if (sceNetCtlInetGetInfo(SCE_NETCTL_INFO_GET_IP_ADDRESS, &info) < 0)
        ip = "127.0.0.1";
    else
        ip = info.ip_address;

    port = 8080;
    username = "kodi";
    password = "";
}
Config::Config(const std::string &ip, const std::string &username, const std::string &password, int port) : ip(ip),
                                                                                                            username(
                                                                                                                    username),
                                                                                                            password(
                                                                                                                    password),
                                                                                                            port(port) {}

const std::string &Config::getIp() const {
    return ip;
}

const std::string &Config::getUsername() const {
    return username;
}

const std::string &Config::getPassword() const {
    return password;
}

int Config::getPort() const {
    return port;
}


