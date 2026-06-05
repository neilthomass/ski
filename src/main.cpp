#include <iostream>
#include <string>
#include "ski/evaluator.hpp"
#include "ski/parser.hpp"
#include "ski/term.hpp"

namespace {

void printHelp() {
  std::cout
      << "SKI combinator calculus interpreter\n"
         "\n"
         "Enter an expression to reduce it to normal form. Application is\n"
         "left-associative, so `S K I` parses as `((S K) I)`; use parentheses\n"
         "to force right-nesting, e.g. `S (K I) S`.\n"
         "\n"
         "Reduction rules:\n"
         "  I x      = x\n"
         "  K x y    = x\n"
         "  S x y z  = x z (y z)\n"
         "\n"
         "Commands:\n"
         "  :help            show this help\n"
         "  :quit, :q        exit the interpreter\n"
         "  :step <expr>     show a single reduction step\n"
         "  :trace <expr>    show every intermediate term until normal form\n"
         "  :steps <n>       set the max-steps budget (guards against\n"
         "                   non-terminating terms; 0 = no limit)\n"
         "\n"
         "Anything not starting with ':' is treated as an expression.\n";
}

}  // namespace

int main(int argc, char **argv) {
  (void)argc;
  (void)argv;
  std::cout << "SKI combinator calculus interpreter\nMade by Neil Thomas\n";
  std::string line;
  size_t maxSteps = 100000;
  while (true) {
    std::cout << "> ";
    if (!std::getline(std::cin, line))
      break;
    if (line.empty())
      continue;
    if (line.empty())
      continue;
    if (line == ":quit" || line == ":q")
      break;
    if (line == ":help") {
      printHelp();
      continue;
    }
    try {
      ski::TermPtr t = ski::Parser::parse(line);
      ski::EvalResult r = ski::Evaluator::normalize(t, maxSteps);
      std::cout << ski::toString(r.term);
      if (!r.normalForm) {
        std::cout << " (stopped after " << r.steps << " steps)";
      }
      std::cout << "\n";
    } catch (const ski::ParseError &e) {
      std::cout << "parse error: " << e.what() << "\n";
    }
  }
  return 0;
}
