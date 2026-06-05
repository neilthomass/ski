#include "ski/parser.hpp"
#include "ski/term.hpp"
#include <cctype>
#include <string>

namespace ski {

void skipSpaces(std::string_view source, size_t &i) {
  while (i < source.size() && isspace(source.at(i)))
    ++i;
}

TermPtr parseAtom(std::string_view source, size_t &i);

TermPtr parseExpr(std::string_view source, size_t &i) {
  TermPtr left = parseAtom(source, i);
  while (true) {
    skipSpaces(source, i);
    if (i >= source.size() || source.at(i) == ')')
      break;
    left = Term::makeApp(left, parseAtom(source, i));
  }
  return left;
}

TermPtr parseAtom(std::string_view source, size_t &i) {
  skipSpaces(source, i);
  if (i >= source.size())
    throw ParseError("expected atom, got end of input");
  char c = source.at(i);

  if (c == '(') {
    ++i;
    TermPtr inner = parseExpr(source, i);
    skipSpaces(source, i);
    if (i >= source.size() || source.at(i) != ')')
      throw ParseError("expected ')'");
    ++i;
    return inner;
  }

  if (c == 'S') {
    ++i;
    return Term::makeS();
  }
  if (c == 'I') {
    ++i;
    return Term::makeI();
  }
  if (c == 'K') {
    ++i;
    return Term::makeK();
  }

  if (std::isalnum(static_cast<unsigned char>(c))) {
    std::string name;
    while (i < source.size() &&
           std::isalnum(static_cast<unsigned char>(source.at(i)))) {
      name += source.at(i);
      ++i;
    }
    return Term::makeVar(name);
  }

  throw ParseError("Unexpected char");
}

TermPtr Parser::parse(std::string_view source) {
  size_t i = 0;
  TermPtr result = parseExpr(source, i);
  skipSpaces(source, i);
  if (i != source.size())
    throw ParseError("Tailing input");
  return result;
}

} // namespace ski
