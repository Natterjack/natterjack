Compilation Pipeline
====================

Compiling takes place in four main phases. Initially source text is
parsed into a parse tree. This tree is then waked and semantic
information is extracted to create the abstract-syntax tree. This tree
is then passed to the compiler where it is considered for high-level
optimisations and converted into three-code instructions. Finally the
tree-code instructions are walked and final optimisations are
performed before lowering them to bytecode and writing the resulting
data to the output file.

Parsing
-------

Text enters the parser as a ``std::istream``. This stream is passed
tot he tokeniser; implemented in **Ragel** this is responsible for
emitting a stream of tokens based on a set of regular language
rules. These tokens are then buffered in the ``TokenStream`` object
until the parser is ready to consume them.

Parser objects will implement as simple interface containing the
single method ``Parse``. This method will be passed the
``TokenStream`` object and will produce a single ``ParseNode``
representing the entire contents of the source text.

Semantic Analysis
-----------------

Semantic analysis of the parse tree will be performed using the good
ol' visitor pattern. The semantic phase will visit each node in the
parse tree and build up a semantic representation of the source in
parallell.

This will consist of generating the symbol tables as we go and keeping
track of types and so on. Type inference will also be done here. The
output from this phase is a single ``SemNode`` which points to the
root of the semantic tree.

Translation
-----------

The translation phase will again walk the tree provided by the
semantic phase using the visitor pattern. It will build up a tree of
baisc blocks representing the program. Here wi will do things like
perform reeachability analysis and make sure that the return types
from different blocks match up. More type inference can take place
here too.

This phase will also be responsible for generating and patching up the
labels that will be used in the final assembly phase to calculate jump
targets and so on. The output from this phase will be a list of
definition objects containing the compiled basic blocks.

Assembly
--------

Finally the three-code tree will be blowered to virtual machine
bytecode. Jump patching will take place and things like constant
packing, where we minimise the amount of space taken up by constant
values used within the source by sharing them, may also take place
here too. The target of the assembly will be a section of a bytecode
file. The final task for the copiler is then to write this file out to
disk.
