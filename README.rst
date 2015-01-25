Welcome
=======

Natterjack is a statically typed programming language inspired by the
power and flexibility of dynamically typed languages. ::

 class Hello
     // writes a greeting to the standard output
     void greet(String thing)
         IO.put("Hello #{thing}")
     end
 end

 Hello.new.greet("World!")

Pinches of Salt
---------------

The language is very young at the moment.  It is likely to radically
change direction as I work out what I want it to be and test out new
features.  Use at your own peril.

Getting Started
---------------

Natterjack lives `on Bitbucket
<http://bitbucket.org/iwillspeak/natterjack>`_.  To compile from source
you should just need a modern C++ compiler and Rake on a \*nix machine.

Once you have the source downloaded you should be able to compile the
main executable with ``rake``.  To run the unit tests as well run
``rake test``.

Download
--------

Natterjack is in the early stages of development at the moment and
only available as source distribution.  To get a copy of the code you
can clone the Git repository at
``http://bitbucket.org/iwillspeak/natterjack``.

Docs
----

Documentation is currently under development and can be found in the
``/docs`` directory at the root of the repository.
