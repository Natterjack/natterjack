# Coding Style and Conventions

Project layout and source code formatting conventions.

## Layout

Code is separated into three main areas: documentation, libraries, and executables.

* On-line documentation is written in the [ronn](http://rtomayko.github.io/ronn/) format and is stored in the `man/` folder.
* Libraries are located in the `lib/` directory. Each library has it's own folder containing public header files, and a `src/` folder containing private header files and source code.
* Executables each have their own folder containing their private header files and source code.

## General Rules

1. Tabs not spaces
2. Braces share the line of the conditional statement or function definition. Final closing braces get their own line.
3. Use C style comments for function documentation and block comments and c++ style comments for single line comments.
4. Prefer `enum`s over `#define`.
