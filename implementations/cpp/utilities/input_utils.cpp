#include "input_utils.h"

#include <charconv>
#include <cctype>
#include <system_error>

bool read_integer(
    std::istream& input,
    int& value)
{
    std::string line;

    if (!std::getline(input, line))
    {
        return false;
    }

    const char* begin = line.data();
    const char* end = begin + line.size();

    while (begin != end &&
           std::isspace(static_cast<unsigned char>(*begin)))
    {
        ++begin;
    }

    while (end != begin &&
           std::isspace(static_cast<unsigned char>(*(end - 1))))
    {
        --end;
    }

    auto result = std::from_chars(begin, end, value);

    return result.ec == std::errc{} &&
           result.ptr == end;
}

bool read_integer(
    std::istream& input,
    std::ostream& output,
    const std::string& prompt,
    int& value)
{
    output << prompt;

    return read_integer(input, value);
}