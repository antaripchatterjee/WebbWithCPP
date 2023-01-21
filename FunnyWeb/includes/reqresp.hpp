#ifndef __FUNNYWEB_REQRESP_H__
#define __FUNNYWEB_REQRESP_H__

#include "request.hpp"
#include "response.hpp"

namespace fw {
    typedef void(*t_viewfunc)(FunnyWebRequest*, FunnyWebResponse*);
}

#endif // __FUNNYWEB_REQRESP_H__