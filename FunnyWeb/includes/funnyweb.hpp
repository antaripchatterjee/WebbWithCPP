#ifndef __FUNNYWEB_H__
#define __FUNNYWEB_H__
#include <string>
#include <unordered_map>
#include "base.hpp"
#include "reqresp.hpp"

namespace fw {
    class FunnyWebApp : public FunnyWebBase {
        std::unordered_map<std::string, std::string> routeToEndpointMap;
        void fn();
        public:
        void runForever(const char* host, int port);
        void addGet(const char* route, fw::t_viewfunc viewFunc);
        void addPost(const char* route, fw::t_viewfunc viewFunc);
        void addPut(const char* route, fw::t_viewfunc viewFunc);
        void addPatch(const char* route, fw::t_viewfunc viewFunc);
        void addDelete(const char* route, fw::t_viewfunc viewFunc);
        void addOptions(const char* route, fw::t_viewfunc viewFunc);
        void addHead(const char* route, fw::t_viewfunc viewFunc);
        FunnyWebApp(const char* appName);
    };
}

#endif // __FUNNYWEB_H__