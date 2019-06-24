#ifndef VITAKODIREMOTE_REQUEST_HH
#define VITAKODIREMOTE_REQUEST_HH


#include <jansson.h>
#include <string>

class Request {
private:
    json_t params;
    json_t id;
    std::string method;



};


#endif //VITAKODIREMOTE_REQUEST_HH
