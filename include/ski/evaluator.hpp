#pragma once

#include <cstddef>
#include <optional>

#include "ski/term.hpp"

namespace ski {

struct EvalResult {
    TermPtr term;
    std::size_t steps;
    bool normalForm;
};

class Evaluator {
public:
    static std::optional<TermPtr> step(const TermPtr& t);
    static EvalResult normalize(const TermPtr& t, std::size_t maxSteps = 0);
};

}  // namespace ski
