#include "strutils.h"

// system includes
#include <cctype>
#include <format>
#include <assert.h>


namespace cpputils {
namespace {
std::expected<char *, std::string> sodium_bin2hex(char * const hex, const size_t hex_maxlen,
                                                 const unsigned char * const bin, const size_t bin_len)
    __attribute__ ((nonnull(1)));
} // namespace

std::string toHexString(std::basic_string_view<unsigned char> buf)
{
    std::string hex(buf.size() * 2 + 1, {});
    assert(hex.size() == buf.size() * 2 + 1);

    if (const auto result = sodium_bin2hex(hex.data(), hex.size(), buf.data(), buf.size()); !result)
    {
//        auto msg = fmt::format("sodium_bin2hex() failed with {}", result.error());
//        ESP_LOGW(TAG, "%.*s", msg.size(), msg.data());
        return {};
    }

    hex.resize(hex.size() - 1);
    assert(hex.size() == buf.size() * 2);

    return hex;
}

std::expected<std::basic_string<unsigned char>, std::string> fromHexString(std::string_view hex)
{
    if (hex.size() % 2 != 0)
        return std::unexpected("hex length not even");

    std::basic_string<unsigned char> result;
    result.reserve(hex.size() / 2);

    for (auto iter = std::cbegin(hex); iter != std::cend(hex); )
    {
        union {
            unsigned char c;
            struct {
                unsigned char nibble1:4;
                unsigned char nibble0:4;
            } nibbles;
        };

        switch (const auto c = *iter)
        {
        case '0'...'9': nibbles.nibble0 = c - '0'; break;
        case 'A'...'F': nibbles.nibble0 = c - 'A' + 10; break;
        case 'a'...'f': nibbles.nibble0 = c - 'a' + 10; break;
        default:
            return std::unexpected(std::format("invalid character {} at pos {}", c, std::distance(std::begin(hex), iter)));
        }

        iter++;

        switch (const auto c = *iter)
        {
        case '0'...'9': nibbles.nibble1 = c - '0'; break;
        case 'A'...'F': nibbles.nibble1 = c - 'A' + 10; break;
        case 'a'...'f': nibbles.nibble1 = c - 'a' + 10; break;
        default:
            return std::unexpected(std::format("invalid character {} at pos {}", c, std::distance(std::begin(hex), iter)));
        }

        iter++;

        result.push_back(c);
    }

    return result;
}

std::string toBase64String(std::basic_string_view<unsigned char> buf)
{
    constexpr std::string_view base64_chars{"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"};

    std::string out;

    int val = 0;
    int valb = -6;
    for (unsigned char c : buf)
    {
        val = (val << 8) + c;
        valb += 8;

        while (valb >= 0)
        {
            out.push_back(base64_chars[(val>>valb)&0x3F]);
            valb -= 6;
        }
    }

    if (valb>-6)
        out.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);

    while (out.size() % 4)
        out.push_back('=');

    return out;
}

namespace {
constexpr std::string_view base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";
bool is_base64(char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}
}

std::string base64_decode(std::string const& encoded_string)
{
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
        char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
        char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

        for (i = 0; (i < 3); i++)
            ret.push_back(char_array_3[i]);
        i = 0;
      }
    }

    if (i) {
      for (j = i; j <4; j++)
        char_array_4[j] = 0;

      for (j = 0; j <4; j++)
        char_array_4[j] = base64_chars.find(char_array_4[j]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (j = 0; (j < i - 1); j++) ret.push_back(char_array_3[j]);
    }

    return ret;
  }

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

namespace {
/* Derived from original code by CodesInChaos */
std::expected<char *, std::string>
sodium_bin2hex(char *const hex, const size_t hex_maxlen,
               const unsigned char *const bin, const size_t bin_len)
{
    size_t       i = (size_t) 0U;
    unsigned int x;
    int          b;
    int          c;

    if (bin_len >= SIZE_MAX / 2 || hex_maxlen <= bin_len * 2U) {
        return std::unexpected("misuse because bin_len >= SIZE_MAX / 2 || hex_maxlen <= bin_len * 2U");
    }
    while (i < bin_len) {
        c = bin[i] & 0xf;
        b = bin[i] >> 4;
        x = (unsigned char) (87U + c + (((c - 10U) >> 8) & ~38U)) << 8 |
            (unsigned char) (87U + b + (((b - 10U) >> 8) & ~38U));
        hex[i * 2U] = (char) x;
        x >>= 8;
        hex[i * 2U + 1U] = (char) x;
        i++;
    }
    hex[i * 2U] = 0U;

    return hex;
}
} // namespace
} // namespace cpputils
