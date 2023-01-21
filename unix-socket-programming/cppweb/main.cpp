#include <iostream>

#include "includes/cppweb.hpp"

using namespace cppweb;

int main(int argc, char const *argv[])
{
    WebApp app("helloworld");
    try {
        app.run_forever(14500);
    } catch (WebException &except) {
        if(except.get_except_code() == WebException::Code::APPLICATION_ABORTED_BY_USER) {
            app.shutdown();
        } else {
            std::cerr << except.what() << std::endl;
        }
    }
    return 0;
}
