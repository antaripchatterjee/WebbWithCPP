#if !defined(__CPPWEB_HPP__)
#define __CPPWEB_HPP__
#include "base.hpp"

namespace cppweb
{
    enum class AppStatus {
        CPPWEB_SUCCESS,
        CPPWEB_WSASTARTUP_ERROR,
        CPPWEB_INVALID_SOCKET_ERROR
    };

    class Application : public Base
    {
        string getName();
        public:
        Application(string name);
        AppStatus runForever(const char* hostname, int port);
    };
    
} // namespace cppweb



#endif // __CPPWEB_HPP__
