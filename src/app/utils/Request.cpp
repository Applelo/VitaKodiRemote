#include "Request.hh"

Request::Request(Config *config) {
    this->config = config;
    this->cleanUp();
}

void Request::initNet() {
    sceSysmoduleLoadModule(SCE_SYSMODULE_NET);
    SceNetInitParam netInitParam;
    int size = 4*1024*1024;
    netInitParam.memory = malloc(size);
    netInitParam.size = size;
    netInitParam.flags = 0;
    sceNetInit(&netInitParam);
    sceNetCtlInit();
    sceSysmoduleLoadModule(SCE_SYSMODULE_HTTP);
    sceHttpInit(4*1024*1024);
    cURLpp::initialize();
}

void Request::terminateNet() {
    sceHttpTerm();
    sceSysmoduleUnloadModule(SCE_SYSMODULE_HTTP);
    sceNetCtlTerm();
    sceNetTerm();
    this->cleanUp();
}

void Request::cleanUp() {
    method.clear();
    params = json_object();
    id = json_string("1");
}

bool Request::tryConnection() {
    this->method = "JSONRPC.Ping";
    responseJson = this->post();
    //return json_string_value(json_object_get(responseJson, "result")) == "pong";
    return false;
}

json_t *Request::post() {
    initNet();

    bodyJson = json_pack(
            "{"
            "s:s,"
            "s:s,"
            "s:o,"
            "s:o"
            "}",
            "jsonrpc", "2.0",
            "method", method.c_str(),
            "params", params,
            "id", id
    );
    bodyString = json_dumps(bodyJson, 0);

    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;

        request.setOpt(new curlpp::options::Url(this->config->getIp()));
        request.setOpt(new curlpp::options::Port(this->config->getPort()));

        std::list<std::string> header;
        header.emplace_back("Content-Type: application/json");

        request.setOpt(new curlpp::options::HttpHeader(header));

        request.setOpt(new curlpp::options::PostFields(bodyString));
        request.setOpt(new curlpp::options::PostFieldSize(bodyString.length()));

        if (config->isAuthentication())
            request.setOpt(new curlpp::options::UserPwd(config->getUsername() + ":" + config->getPassword()));

        request.setOpt(new curlpp::options::WriteStream(&response));

        request.perform();
    }
    catch ( curlpp::LogicError & e ) {
        std::cout << e.what() << std::endl;
    }
    catch ( curlpp::RuntimeError & e ) {
        std::cout << e.what() << std::endl;
    }

    terminateNet();

    return json_loads(std::string(response.str()).c_str(), 0, nullptr);
}

void Request::input(const char *method) {
    this->method = method;
    this->post();
}



