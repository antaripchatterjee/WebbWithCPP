#include <iostream>
#include "includes/reqresp.hpp"
#include "includes/funnyweb.hpp"

#define APPNAME "FUNNYAPP"
#define HOST "0.0.0.0"
#define PORT 3000

using namespace fw;

void index(FunnyWebRequest* req, FunnyWebResponse* resp) {
    resp->setStatus(200);
    resp->writeData("Hello, World!");
    resp->send();
}

void add(FunnyWebRequest* req, FunnyWebResponse* resp) {
    int a, b;
    req->getPathParameter<int>("a", a);
    req->getPathParameter<int>("b", b);
    std::string result = "Result is " + (a+b); 
    resp->setStatus(200);
    resp->writeData(result.c_str());
    resp->send();
}

int main(int argc, const char* argv[]) {
    FunnyWebApp *app = new FunnyWebApp(APPNAME);
    app->addGet("/", index);
    app->addGet("/add/:a/:b", add);
    app->runForever(HOST, PORT);
    delete app; 
    return 0; 
}