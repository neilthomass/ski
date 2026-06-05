#include "ski/term.hpp"
#include <cstddef>
#include <memory>

namespace ski {

TermPtr Term::makeS() { return TermPtr(new Term(Kind::S)); }

TermPtr Term::makeK() { return TermPtr(new Term(Kind::K)); }

TermPtr Term::makeI() { return TermPtr(new Term(Kind::I)); }

TermPtr Term::makeVar(const std::string &name) {
  return TermPtr(new Term{Kind::Var, name, nullptr, nullptr});
}

TermPtr Term::makeApp(TermPtr fn, TermPtr arg) {
  return TermPtr(new Term{Kind::App, "", fn, arg});
}

bool isCombinator(const TermPtr &t) {
  Kind kind = t->kind;
  return kind == Kind::I || kind == Kind::K || kind == Kind::S;
}

bool isApp(const TermPtr &t) { return t->kind == Kind::App; }
// true if t is S, K, I, or a Var
bool isLeaf(const TermPtr &t) { return isCombinator(t) || !isApp(t); }

std::string toString(const TermPtr &t) {
  if (!t)
    return "?";

  switch (t->kind) {
  case Kind::S:
    return "S";
  case Kind::I:
    return "I";
  case Kind::K:
    return "K";
  case Kind::Var:
    return t->name;

  case Kind::App: {
    std::string left = toString(t->fn);
    std::string right = toString(t->arg);

    if (t->arg && t->arg->kind == Kind::App) {
      right = "(" + right + ")";
    }
    return left + " " + right;
  }
  }
  return "?";
}

// NOT reduced equality, structural
bool equals(const TermPtr &a, const TermPtr &b) {
  if (!a && !b)
    return true;
  if (a->kind != b->kind)
    return false;
  if (a->kind == Kind::App)
    return equals(a->fn, b->fn) && equals(a->arg, b->arg);
  if (a->kind == Kind::Var)
    return a->name == b->name;
  return true;
}

} // namespace ski
