#include "strutils.h"

// system includes
#include <cctype>

namespace cpputils {
bool stringEqualsIgnoreCase(std::string_view a, std::string_view b)
{
    if (a.size() != b.size())
        return false;

    return std::equal(std::begin(a), std::end(a), std::begin(b),
                      [](char a, char b) {
                          return std::tolower(a) == std::tolower(b);
                      });
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

std::optional<std::string_view> getStringBetween(std::string_view search, std::string_view prefix, std::string_view suffix)
{
    auto beginIndex = search.find(prefix);
    if (beginIndex == std::string_view::npos)
        return std::nullopt;

    auto restView = search.substr(beginIndex + prefix.size());

    auto endIndex = restView.find(suffix);
    if (endIndex == std::string_view::npos)
        return std::nullopt;

    return restView.substr(0, endIndex);
}

} // namespace cpputils
