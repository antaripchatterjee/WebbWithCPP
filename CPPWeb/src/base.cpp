#include "../includes/base.hpp"

cppweb::Base::Base(string name) : name { name } {}

void cppweb::Base::addViewFunction(const char* url, HTTPMethod httpMethod, viewfunc_t viewFunc){
    views[url][httpMethod] = viewFunc;
}

void cppweb::Base::addEndpoint(const char* url, HTTPMethod httpMethod, string endpoint){
    string appName = this->getName();
    string endpointAlias = appName + "." + endpoint;
    endpoints[endpointAlias][httpMethod] = url;
}

void cppweb::Base::addGet(const char* url, viewfunc_t viewFunc, const char* endpoint) {
    addEndpoint(url, HTTPMethod::GET, endpoint);
    addViewFunction(url, HTTPMethod::GET, viewFunc);
}

void cppweb::Base::addPost(const char* url, viewfunc_t viewFunc, const char* endpoint){
    addEndpoint(url, HTTPMethod::POST, endpoint);
    addViewFunction(url, HTTPMethod::POST, viewFunc);
}

void cppweb::Base::addPut(const char* url, viewfunc_t viewFunc, const char* endpoint){
    addEndpoint(url, HTTPMethod::PUT, endpoint);
    addViewFunction(url, HTTPMethod::PUT, viewFunc);
}

void cppweb::Base::addPatch(const char* url, viewfunc_t viewFunc, const char* endpoint){
    addEndpoint(url, HTTPMethod::PATCH, endpoint);
    addViewFunction(url, HTTPMethod::PATCH, viewFunc);
}

void cppweb::Base::addDelete(const char* url, viewfunc_t viewFunc, const char* endpoint){
    addEndpoint(url, HTTPMethod::DELETE, endpoint);
    addViewFunction(url, HTTPMethod::DELETE, viewFunc);
}

void cppweb::Base::addOptions(const char* url, viewfunc_t viewFunc, const char* endpoint){
    addEndpoint(url, HTTPMethod::OPTIONS, endpoint);
    addViewFunction(url, HTTPMethod::OPTIONS, viewFunc);
}

void cppweb::Base::addHead(const char* url, viewfunc_t viewFunc, const char* endpoint){
    addEndpoint(url, HTTPMethod::HEAD, endpoint);
    addViewFunction(url, HTTPMethod::HEAD, viewFunc);
}
