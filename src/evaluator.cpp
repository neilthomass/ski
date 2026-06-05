#include "ski/evaluator.hpp"
#include "ski/term.hpp"
#include <optional>
#include <vector>

namespace ski {

std::optional<TermPtr> Evaluator::step(const TermPtr &t) {

  if (isLeaf(t))
    return std::nullopt;
  
  TermPtr head = t->fn;
  std::vector<TermPtr> stack;
  stack.push_back(t->arg);

  
  while (head->kind == Kind::App) {
    stack.push_back(head->arg);
    head = head->fn;
  }

  auto rebuild = [&](TermPtr result) {
    while (!stack.empty()) {
      result = Term::makeApp(result, stack.back());
      stack.pop_back();
    }
    return result;
  };

  if (head->kind == Kind::I && stack.size() >= 1) {
    TermPtr x = stack.back();
    stack.pop_back();
    return rebuild(x);
  }

  if (head->kind == Kind::K && stack.size() >= 2) {
    TermPtr x = stack.back();
    stack.pop_back();
    stack.pop_back();
    return rebuild(x);
  }

  if (head->kind == Kind::S && stack.size() >= 3) {
    TermPtr x = stack.back();
    stack.pop_back();
    TermPtr y = stack.back();
    stack.pop_back();
    TermPtr z = stack.back();
    stack.pop_back();

    TermPtr res = Term::makeApp(Term::makeApp(x, z), Term::makeApp(y, z));
    return rebuild(res);
  }

  if (auto r = step(t->fn))
    return Term::makeApp(*r, t->arg);
  if (auto r = step(t->arg))
    return Term::makeApp(t->fn, *r);

  return std::nullopt;
}

EvalResult Evaluator::normalize(const TermPtr &t, std::size_t maxSteps) {
  TermPtr current = t;
  std::size_t steps = 0;

  while (maxSteps == 0 || steps < maxSteps) {
    std::optional<TermPtr> next = step(current);
    if (!next)
      return EvalResult{current, steps, true};
    current = *next;
    ++steps;
  }

  return EvalResult{current, steps, false};
}

} // namespace ski
