#if !defined(__BASE_HPP__)
#define __BASE_HPP__
#include <string>
#include <map>

#include "http_methods.hpp"
#include "reqresp.hpp"

using std::string;
using std::map;
  

namespace cppweb
{
    typedef map<HTTPMethod, viewfunc_t> view_t; 
    typedef map<HTTPMethod, string> endpoint_t;

    class Base {
        void addViewFunction(const char* url, HTTPMethod httpMethod, viewfunc_t viewFunc);
        void addEndpoint(const char* url, HTTPMethod httpMethod, string endpoint);
        protected:
        string name;
        map<string, view_t> views;
        map<string, endpoint_t> endpoints;
        virtual string getName() = 0;
        public:
        Base(string name);
        void addGet(const char* url, viewfunc_t viewFunc, const char* endpoint);
        void addPost(const char* url, viewfunc_t viewFunc, const char* endpoint);
        void addPut(const char* url, viewfunc_t viewFunc, const char* endpoint);
        void addPatch(const char* url, viewfunc_t viewFunc, const char* endpoint);
        void addDelete(const char* url, viewfunc_t viewFunc, const char* endpoint);
        void addOptions(const char* url, viewfunc_t viewFunc, const char* endpoint);
        void addHead(const char* url, viewfunc_t viewFunc, const char* endpoint);
    };
} // namespace cppweb


#endif // __BASE_HPP__
