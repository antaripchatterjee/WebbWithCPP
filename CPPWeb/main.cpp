#include <iostream>
#include "includes/cppweb.hpp"
#include "includes/reqresp.hpp"

using namespace cppweb;

void index(const HTTPRequest& req, HTTPResponse& resp) {

}

int main(int argc, char const *argv[])
{
    Application app("helloworld");
    app.addGet("/", static_cast<viewfunc_t>(&index), "index");
    
    if(app.runForever("127.0.0.1", 8000) != AppStatus::CPPWEB_SUCCESS) {
        std::cout << "Failed!" << std::endl;
    }
    return 0;
}
