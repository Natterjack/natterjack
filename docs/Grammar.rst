Natterjack Lexical Grammar
==========================

This provides a simple overview of the grammar of the Natterjack
programming language.  It's not set in stone yet.  Most of this stuff
is just my current thoughts on the design and implementation.

Parsing Overview
----------------

Expressions will be parsed using a Pratt parser.  This should make it
super fast and flexible.  Hopefully new operators and stuff can be
added easily.

The remainder of the the language will be parsed by a standard
hand-written LL1 recursive decent parser.

Literals
--------

There are so far two kinds of literal values in Natterjack, Strings
and Numbers.  A Number literal represents a numeric value encoded in
either base 10, 16 (hexadecimal), 8 (octal) or 2 (binary).  Literals
are considered base 10 by default with the prefixes ``0x``, ``0o`` and
``0b`` being used to represent hexadecimal, octal and binary literals
respectively.

String literals can begin with either single or double quotes. Single
quoted strings are 'raw strings' and are interpreted as-is.  Double
quoted strings are 'processed strings' and can contain escape
sequences such as ``\n`` for newline.

Expressions
-----------

There are two kinds of expression: simple and complex.  A simple
expression is either a literal value or a reference to a named
variable:

 * ``10``
 * ``"tadpoles"``
 * ``pondweed``

Complex expressions represent the application of an operator to one or
more expressions.  This includes simple unary and binary operators as
well as function invocation, indexing and slicing:

 * ``!true``
 * ``6 * 7``
 * ``skin.wart_count``
 * ``toad.eat(fly)``
 * ``lilly_pads[2]``

It is interesting to note that while ``riverbank`` is a simple
epxression, the 'dotted' expression ``riverbank.bulrushes`` is actualy
a complex expression representing the application of the ``.``
'operator' to the two simple expressions ``riverbank`` and
``bulrushes``.  That's the theory anyhow.  How well this works out in
practice is yet to be seen.

Control Flow
------------

Natterjack has most of the common forms of control flow operators,
along with some syntactic sugar to make things a bit more readable.

``if``, ``elif``, ``else`` & ``unless``
  These define the standard conditional expressions.  Unless is just a
  negated if expression.

``while``, ``until``
  These represent simple looping.  While repeats a block if the
  condition is true, until repeats it while the condition is false.

``foreach`` (and maybe ``for``)
  Allows you to loop over values in a
  given range.  Might have an old-school ‘c-style' for loop.  We could
  just have some helpers to generate nice sequences like Python
  though.

``match`` & ``case``
  This will be a beefed-up version of the switch construct.  Values
  will be matched in a way similar to Ruby.  This allows you to match
  things against regular expressions and check which sets items belong
  to.  Might want to support pattern matching with this too similar to
  that in Magpie.

Exception Handling
------------------

The language will have a support for structured exception handling.
By default any block will be able to be used to catch and handle
exceptions, in a manner similar to Ruby.  This should reduce the need
for extra blocks and try statements where there already exists an
appropriate block. ::

    if foo.has_key? "bar"
      value = foo["bar"]
    catch KeyError as e
      Io.put e.message
    end

    // can just have a try block though
    try
      some_integer.to_string
    catch ConversionError
      // oh dear.. :-/
    end
    
There will be three kinds of ``catch`` statement:

``catch``
  which catches all exceptions.

``catch SomeType``
  which catches all exceptions of a given type.

``catch Type as var_name``

  which catches exceptions of a given type and binds them to a
  variable name so the error can be inspected.

Each block will also support a ``finally`` section that gets called
when exiting the block, regardless of whether an exception is thrown.
This can be used to perform cleanup operations.  A similar mechanism
for automatically disposing of objects with a ``using`` block will
also be supported. ::

    try
      could_throw_exception
    finally
      IO.put(“Finished”)
    end

    using Hash.new as hash
      hash[“foo”] = 1337
      do_something_with_hashes(hash)
    end

The Shaky Bit
-------------

These sections contain more unanswered questions than anything
else.  More thought is needed.

Functions and Methods
^^^^^^^^^^^^^^^^^^^^^

What type of function dispatch should we have?

 * *standard* single virtual dispatch, like so many languages.
 * *message passing* similar to Objective-C
 * *multi-methods* similar to Wren

If *multi-methods* or *message passing* is used how can we make it
fast? Caching at the call site maybe?

Should it be possible to have a ‘free-floating' function outside a class?

Classes
^^^^^^^

Single or multiple inheritance.  How do we implement interfaces? Can
we use structural typing along with static typing? Would an interface
be a way of making the structure you are expecting explicit? I quit
like that idea.  The more dynamic we can make the language feel
without loosing static types the better.

Object construction will be implemented with standard static method
calls as is done in Ruby.  All classes will inherit from a root class
which provides an implementation of ``allocate`` or similar which
creates a new instance of the given type with blank fields.  It is
then up to ``new`` to call the correct constructor and return the new
object.

If a class provides a constructor method (maybe named
``initiali(s|z)e`` then the compiler implicitly defines a new with a
matching argument list. Not sure what happens if a ``new`` with that
argument list exists already, or even if there is a custom ``new``
implemented for that class. Might need some messing-about-with to work
that one out.
