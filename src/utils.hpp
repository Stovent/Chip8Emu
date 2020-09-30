#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

inline std::string toHex(const uint32_t value, const char* format = NULL)
{
    char c[10] = {0};
    sprintf(c, format ? format : "%02X", value);
    return c;
}

#endif // UTILS_HPP
