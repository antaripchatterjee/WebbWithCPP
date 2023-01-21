#if !defined(__HTTP_METHODS_HPP__)
#define __HTTP_METHODS_HPP__

#include <map>

namespace cppweb
{
    enum class HTTPMethod {
        GET, POST, PUT, PATCH,
        DELETE, OPTIONS, HEAD
    };
    const std::map<string, HTTPMethod> httpMethod({
        {"GET", HTTPMethod::GET},
        {"POST", HTTPMethod::POST},
        {"PUT", HTTPMethod::PUT},
        {"PATCH", HTTPMethod::PATCH},
        {"DELETE", HTTPMethod::DELETE},
        {"OPTIONS", HTTPMethod::OPTIONS},
        {"HEAD", HTTPMethod::HEAD}
    });
} // namespace cppweb



#endif // __HTTP_METHODS_HPP__
