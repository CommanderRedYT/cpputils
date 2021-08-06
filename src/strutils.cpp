#include "strutils.h"

// system includes
#include <algorithm>
#include <cctype>

namespace cpputils {
bool stringEqualsIgnoreCase(std::string_view a, std::string_view b)
{
    return a == b; // HACK for now...

    if (a.size() != b.size())
        return false;

    return std::equal(std::begin(a), std::end(a), std::begin(b),
                      [](char a, char b) {
                          return std::tolower(a) == std::tolower(b);
                      });
}

bool stringStartsWith(std::string_view fullString, std::string_view begin)
{
    return fullString.rfind(begin, 0) == 0;
}

bool stringEndsWith(std::string_view fullString, std::string_view ending)
{
    if (fullString.length() >= ending.length())
    {
        return (0 == fullString.compare(fullString.length() - ending.length(), ending.length(), ending));
    }
    else
    {
        return false;
    }
}
} // namespace cpputils
