Architecture
============

The natterjack compiler and runtime will use a library-based
architecture to maximise the ease of sharing code between
applications. Hopefully this will allow people writing editors and
syntax checkers to use the same parser that we use when compiling the
language.

The main components as I can see it at the moment are:

*The Parser Library*
  This comprises of a lexical analyser and recursive decent parser
  which can take either string or filestream inputs and return a parse
  tree.

*The Compiler Library*
  This library takes the parse tree provided by the parser library and
  performs semantic analysis on it. Once the program is verified as
  valid it then turns this into a bytecode representation of the code.

*Parse Tree Utilities*
  This library will contain definitions of all the node types that the
  parser and compiler libraies need to share data.

  It will also contain whatever utilities are rquired for seriaising
  the generated parse trees so that they can be viewed.

*Bytecode File Utilities*
  This library will be responsible for loading and storing bytecode
  images from disk. It should provide a simple key-value store
  interface to the clients where they can then store the required
  data.

*Runtime Library*
  This library will be responsible for taking an in-memory bytecode
  file and executing it.

*Standard Library*
  This will be a collection of both compiled native code and
  natterjack utility code that will be available by default to
  language users.

*The Natterjack Executable*
  This executable will be repsonsible for interpreting command line
  arguments and executing the appropriate compiler/runtime tasks.

  The executable should be able to:

   * Compile a piece of code and write it to a file.
   * Run a piece of compiled code from a file.
   * Compile a piece of code and run it directly.
   * Parse a piece of code and dump the parse tree to standard output.

  The executable will also be responsible for providing an
  implementation of the compiler's diagnostic consumer interface to
  print warnings and error messages to the standard error stream.
