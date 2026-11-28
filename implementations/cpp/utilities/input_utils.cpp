#include "input_utils.h"

#include <string>
#include <charconv>
#include <system_error>

bool read_integer(std::istream& input, int& value)
{
    std::string line;

    if (!std::getline(input, line))
    {
        return false;
    }

    const char* begin = line.data();
    const char* end = begin + line.size();

    auto result = std::from_chars(begin, end, value);

    return result.ec == std::errc{}
    && result.ptr == end;
}