#ifndef VITAKODIREMOTE_CONFIG_HH
#define VITAKODIREMOTE_CONFIG_HH

#include <string>
#include <jansson.h>
#include <string.h>
#include <psp2/io/stat.h>
#include <psp2/io/fcntl.h>

#define CONFIG_DIRECTORY_PATH "ux0:/data/VitaKodiRemote/"
#define CONFIG_FILE_NAME "config.json"
#define CONFIG_FILE_PATH CONFIG_DIRECTORY_PATH CONFIG_FILE_NAME

class Config {
private:
    std::string ip, username, password;
    bool authentication;
    unsigned int port;
    bool firstStart;
    json_t *configFile;
    void create();
    void load();
public:
    Config();
    void save();
    void setConnection(std::string ip, unsigned port, bool authentication, std::string username, std::string password);

    const std::string &getIp() const;
    unsigned int getPort() const;
    bool isAuthentication() const;
    const std::string &getUsername() const;
    const std::string &getPassword() const;

    bool isFirstStart() const;


};


#endif //VITAKODIREMOTE_CONFIG_HH
