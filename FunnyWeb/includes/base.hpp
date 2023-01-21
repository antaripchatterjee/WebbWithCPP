#ifndef __FUNNYWEB_BASE_H__
#define __FUNNYWEB_BASE_H__
#include <string>
#include "reqresp.hpp"

namespace fw {
    class FunnyWebBase {
        protected:
        std::string name;
        virtual void fn() = 0;
        public:
        virtual void addGet(const char* route, fw::t_viewfunc viewFunc);
        virtual void addPost(const char* route, fw::t_viewfunc viewFunc);
        virtual void addPut(const char* route, fw::t_viewfunc viewFunc);
        virtual void addPatch(const char* route, fw::t_viewfunc viewFunc);
        virtual void addDelete(const char* route, fw::t_viewfunc viewFunc);
        virtual void addOptions(const char* route, fw::t_viewfunc viewFunc);
        virtual void addHead(const char* route, fw::t_viewfunc viewFunc);
        FunnyWebBase(const char* name);
    };
}

#endif // __FUNNYWEB_BASE_H__