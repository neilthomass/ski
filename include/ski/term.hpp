#pragma once

#include <memory>
#include <string>

namespace ski {

enum class Kind : char {
    S,
    K,
    I,
    Var,
    App,
};

struct Term;
using TermPtr = std::shared_ptr<const Term>;

struct Term {
    Kind kind;
    std::string name;
    TermPtr fn;
    TermPtr arg;

    static TermPtr makeS();
    static TermPtr makeK();
    static TermPtr makeI();
    static TermPtr makeVar(const std::string& name);
    static TermPtr makeApp(TermPtr fn, TermPtr arg);
};

bool isCombinator(const TermPtr& t);
bool isApp(const TermPtr& t);
bool isLeaf(const TermPtr& t);

std::string toString(const TermPtr& t);
bool equals(const TermPtr& a, const TermPtr& b);

}  // namespace ski
