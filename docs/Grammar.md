# Natterjack Lexical Grammar

## Literals

There are so far two kinds of literal values in Natterjack, Strings
and Numbers. A Number literal represents a numeric value encoded in
either base 10, 16 (hexadecimal), 8 (octal) or 2 (binary). Literals
are considered base 10 by default with the prefixes `0x`, `0o` and
`0b` being used to represent hexadecimal, octal and binary literals
respectively.

## Expressions

There are two kinds of expression: simple and complex. A simple
expression is either a literal value or a reference to a named
variable:

 * `10`
 * `"tadpoles"`
 * `pondweed`

Complex expressions represent the application of an operator to one or
more expressions. This includes simple unary and binary opreators as
well as function invocation, indexing and slicing:

 * `!true`
 * `6 * 7`
 * `skin.wart_count`
 * `toad.eat(fly)`
 * `lilly_pads[2]`

It is interesting to note that while `riverbank` is a simple
epxression, the 'dotted' expression `riverbank.bulrushes` is actualy a
complex expression representing the application of the `.` 'operator'
to the two simple expressions `riverbank` and `bulrushes`. That's the
theory anyhow. How well this works out in practice is yet to be seen.
