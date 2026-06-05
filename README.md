A C++23 interpreter for the [**SKI combinator calculus**](https://en.wikipedia.org/wiki/SKI_combinator_calculus) - a Turing-complete rewriting system built from just three primitive combinators. Written by hand.

An SKI term is a bianary tree. It's leaves are combinitors **S**, **K**, and **I** (and also free variables - any run of chars that do not include combinitors and '()'). It's non leaf nodes are Application fucntions that are nested in one another.

Application is written by juxtaposition and associates to the left. To force right nesting, parenthesize.

```
S K I == ((S K) I)
K S (S K) == (K S) (S K)
S (K I) S == ((S (K I)) S)
```

The three simple rules of this language are as follows:

```
I x = x # Identity
K x y = x # Constant function
S x y z = x z (y z) # Substitution
```

Here are some more reductions:

```
S K I (K I S) => K (K I S) (I ( K I S)) => K I (I (K I S)) => I

K S (I (S K S I)) => ... => S

S K I K => K K (I K) => K K K => K
```