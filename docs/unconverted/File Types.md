
# File Types

There are three main types of files that Natterjack works with:

* `.nat` files:  
Natterjack source code.
* `.croak` files:  
Compiled natterjack byte-code objects.
* `.tad` files:  
Natterjack assembly language files, containing a human-readable version of the natterjack byte code instructions.

Byte-code files will contain symbol information and metadata as well as the byte-code representation of the methods.  This includes things like constant values which are used within the code (such as string literals).  There should be enough type information to not only ensure that type safety is enforced at runtime but also to allow someone to compile against a library using just the byte-code files.