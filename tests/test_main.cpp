#include <iostream>
#include <string>

#include "ski/evaluator.hpp"
#include "ski/parser.hpp"
#include "ski/term.hpp"

namespace {

int g_failures = 0;

void check(bool cond, const std::string& what) {
    if (!cond) {
        std::cerr << "FAIL: " << what << "\n";
        ++g_failures;
    }
}

std::string eval(const std::string& src) {
    ski::TermPtr t = ski::Parser::parse(src);
    ski::EvalResult r = ski::Evaluator::normalize(t, /*maxSteps=*/100000);
    return ski::toString(r.term);
}

void testParserRoundTrip() {
    check(ski::toString(ski::Parser::parse("SKI")) == "S K I", "round-trip SKI");
    check(ski::toString(ski::Parser::parse("S(KI)S")) == "S (K I) S", "round-trip S(KI)S");
}

void testPrimitiveReductions() {
    // I x   = x
    // K x y = x
    // S x y z = x z (y z)
    check(eval("I x") == "x", "I rule");
    check(eval("K x y") == "x", "K rule");
    check(eval("S x y z") == "x z (y z)", "S rule");
}

void testWikipediaExamples() {
    // SKI(KIS)  -> I
    // KS(I(SKSI)) -> S
    // SKIK      -> K
    check(eval("SKI(KIS)") == "I", "wiki example 1");
    check(eval("KS(I(SKSI))") == "S", "wiki example 2");
    check(eval("SKIK") == "K", "wiki example 3");
}

void testBooleans() {
    // T = K, F = SK ; T x y = x, F x y = y
    check(eval("K x y") == "x", "true picks first");
    check(eval("SK x y") == "y", "false picks second");
}

}  // namespace

int main() {
    testParserRoundTrip();
    testPrimitiveReductions();
    testWikipediaExamples();
    testBooleans();

    if (g_failures == 0) {
        std::cout << "All tests passed.\n";
        return 0;
    }
    std::cerr << g_failures << " test(s) failed.\n";
    return 1;
}
