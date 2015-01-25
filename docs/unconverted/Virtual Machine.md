# Virtual Machine

The VM will be a multi-threaded risk-like register VM.  Global VM structure will be stored in an `NatterjackVM` structure.  Each VM will have a collection of `NatterjackVMThread` structures containing the thread-local data.  This will include the values of the registers and as much data as possible.  Data or execution state in a given thread will not be available from outside the thread to allow for minimal locking.

Global structure will mainly consist of the loaded binaries and the global configuration options.  At a later date this may also include a JIT cache to allow threads to share compiled traces.

Each thread will then run one or more "*Fibres*".  These Fibres contain the state of execution of a portion of a program.  Fibres can be suspended and re-scheduled co-operatively.  This is somewhat similar to the C# asynchronous task model.

## VM Structure
The `NatterjackVM` object will consist of:

 * Array of `NatterjackVMThread` structures
 * Hash table of `NatterjackVMImage` structures representing the currently loaded images.  Images can either be compiled byte code or dynamic libraries with metadata.