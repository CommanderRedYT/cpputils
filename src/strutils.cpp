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

//void stringReplaceAll(char search, char replace, std::string &subject)
//{
//    size_t start_pos{};
//    while ((start_pos = subject.find(search, start_pos)) != std::string::npos)
//    {
//        subject.replace(start_pos, 1, replace);
//        start_pos++; // Handles case where 'replace' is a substring of 'search'
//    }
//}

void stringReplaceAll(char search, std::string_view replace, std::string &subject)
{
    size_t start_pos{};
    while ((start_pos = subject.find(search, start_pos)) != std::string::npos)
    {
        subject.replace(start_pos, 1, replace);
        start_pos += replace.size(); // Handles case where 'replace' is a substring of 'search'
    }
}

//void stringReplaceAll(std::string_view search, char replace, std::string &subject)
//{
//    size_t start_pos{};
//    while ((start_pos = subject.find(search, start_pos)) != std::string::npos)
//    {
//        subject.replace(start_pos, search.size(), replace);
//        start_pos++; // Handles case where 'replace' is a substring of 'search'
//    }
//}

void stringReplaceAll(std::string_view search, std::string_view replace, std::string &subject)
{
    size_t start_pos{};
    while ((start_pos = subject.find(search, start_pos)) != std::string::npos)
    {
        subject.replace(start_pos, search.size(), replace);
        start_pos += replace.size(); // Handles case where 'replace' is a substring of 'search'
    }
}

//std::string stringReplaceAll(char search, char replace, std::string_view subject)
//{
//    std::string str{subject};
//    size_t start_pos{};
//    while ((start_pos = str.find(search, start_pos)) != std::string::npos)
//    {
//        str.replace(start_pos, 1, replace);
//        start_pos++; // Handles case where 'replace' is a substring of 'search'
//    }
//    return str;
//}

std::string stringReplaceAll(char search, std::string_view replace, std::string_view subject)
{
    std::string str{subject};
    size_t start_pos{};
    while ((start_pos = str.find(search, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, 1, replace);
        start_pos += replace.size(); // Handles case where 'replace' is a substring of 'search'
    }
    return str;
}

//std::string stringReplaceAll(std::string_view search, char replace, std::string_view subject)
//{
//    std::string str{subject};
//    size_t start_pos{};
//    while ((start_pos = str.find(search, start_pos)) != std::string::npos)
//    {
//        str.replace(start_pos, search.size(), replace);
//        start_pos++; // Handles case where 'replace' is a substring of 'search'
//    }
//    return str;
//}

std::string stringReplaceAll(std::string_view search, std::string_view replace, std::string_view subject)
{
    std::string str{subject};
    size_t start_pos{};
    while ((start_pos = str.find(search, start_pos)) != std::string::npos)
    {
        str.replace(start_pos, search.size(), replace);
        start_pos += replace.size(); // Handles case where 'replace' is a substring of 'search'
    }
    return str;
}
} // namespace cpputils
