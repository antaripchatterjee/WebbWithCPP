#if !defined(__REQRESP_HPP__)
#define __REQRESP_HPP__
#include <functional>
#include "request.hpp"
#include "response.hpp"

namespace cppweb
{
    // typedef void(*viewfunc_t)(HTTPRequest*, HTTPResponse*);
    typedef std::function<void(const HTTPRequest&, HTTPResponse&)> viewfunc_t;
} // namespace cppweb



#endif // __REQRESP_HPP__
