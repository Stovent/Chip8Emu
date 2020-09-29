#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

inline std::string toHex(const uint32_t value)
{
    char c[10] = {0};
    sprintf(c, "%02X", value);
    return c;
}

#endif // UTILS_HPP
