# Coding Style and Conventions

Project layout and source code formatting conventions.

## Layout

Code is separated into three main areas: documentation, libraries, and
executables.

 * On-line (man-style) documentation is written in the
   [ronn](http://rtomayko.github.io/ronn/) format and is stored in the
   `man/` folder.

 * Html documentation is written in Re-Structured Text and compiled
   using Sphinx. It is stored in the `docs/` folder.

 * Libraries are located in the `lib/` directory. Each library has
   it's own folder containing public header files, and a `src/` folder
   containing private header files and source code.

 * Executables each have their own folder containing their private
   header files and source code.

 * Functional tests live in the `spec/` folder.

 * Unit tests for libraries and executables live in the `test/` folder
   next to the source files they are testing.

## Coding Rules

 1. Tabs not spaces

 2. Braces share the line of the conditional statement or function
 definition. Final closing braces get their own line.

 3. Use C style comments for function documentation and block comments
 and c++ style comments for single line comments.

 4. Prefer `enum`s over `#define`.

 5. Identifier names should follow these rules:

   * Namespace names should be `lower_case`, with underscores if
     needed.

   * Type names should be `PascalCase`.

   * Function and method names should be `camelCased`.

   * Accronyms and abbreviations in identifiers should be capilaised
     as if they were normal words. Prefer `HttpRequestObject` and
     `VmThread`
