#pragma once

#include <stdexcept>
#include <string>
#include <string_view>

#include "ski/term.hpp"

namespace ski {

class ParseError : public std::runtime_error {
public:
    explicit ParseError(const std::string& message) : std::runtime_error(message) {}
};

class Parser {
public:
    static TermPtr parse(std::string_view source);
};

}  // namespace ski
