# Expressions

Expressions are the main way that things get done in Natterjack. An expression represents taking one or more values; optionally performing operations on those values, each of which may produce side effects; and produces a single value as a result.

Expressions can be split into two main groups: simple expressions and complex expressions.

## Simple Expressions

Simple expressions represent a reference to either a constant value or a value stored in a variable. Examples of expressions include number and string literals, references to compile-time constant values, and variable references. :

## Complex Expressions

Complex expressions represent the result of applying an operator to one or more expressions. Examples of complex expressions include unary operators such as `!` and `++`, binary operators such as `+` and `*`, and nary operators such as the "call" operator `(` and the index operator `[`.

