#ifndef __FUNNYWEB_REQUEST_H__
#define __FUNNYWEB_REQUEST_H__

namespace fw {
    class FunnyWebRequest {
        public:
        class Int {

        };
        class Double {

        };
        class Float {

        };
        class Boolean {

        };
        class String {

        };
        void readBody(std::string& body);
        template<typename T>
        void getPathParameter(const char* param, T& refInstance){
            refInstance = (T) nullptr;
        }
    };
}

#endif // __FUNNYWEB_REQUEST_H__