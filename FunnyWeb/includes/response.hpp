#ifndef __FUNNYWEB_RESPONSE_H__
#define __FUNNYWEB_RESPONSE_H__

namespace fw {
    class FunnyWebResponse {
        public:
        void setStatus(int status);
        void writeData(const char* data);
        void send();
    };
}

#endif // __FUNNYWEB_RESPONSE_H__