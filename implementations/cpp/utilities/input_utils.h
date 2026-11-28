#ifndef INPUT_UTILS_H
#define INPUT_UTILS_H

#include <istream>
#include <ostream>
#include <string>

bool read_integer(
    std::istream& input,
    int& value);

bool read_integer(
    std::istream& input,
    std::ostream& output,
    const std::string& prompt,
    int& value);

#endif