# LLVM playground

This is an LLVM playground. It should provide you a sandbox to play with your first functions generated by the LLVM JIT infrastructure.

## Getting up and running

    cmake .
    make
    ./warmup

## Getting started

In warmup.cpp you will find two functions:

1. makeLLVMModule
1. compile

The first one creates an LLVM module, which represents one compilation unit. In this module we use the C++ API of LLVM to construct the intermediate representation (IR) of a function called "aFun". This function takes one int argument and returns it. I.e. the function is equivalent to:

    int aFun(int n) { return n; }

The second one takes the module and uses the LLVM JIT infrastructure to compile the IR we created for "aFun" into an executable function pointer.

The main function evaluates the compiled function and prints the result.

# Suggested Exercises

## Manually modify the function

Change the construction of aFun to make something more interesting, e.g. return n + n, or even include a branch.

## Plug in some generated code

### From llvm assembly

In fib.ll you find the LLVM assembly implementation of fib. You can use:

    llc -march=cpp fib.ll

to convert it into C++ API calls. This will create a fib.cpp which contains a makeLLVMModule function constructing the IR as given in the .ll file. You can plug this function into warmup.cpp.

### From C(++) code

You can generate new .ll files from C(++) sources using clang:

    clang --emit-llvm -S someFile.c

## Plug in some optimization passes

Look at the LLVM legacy::PassManager infrastructure and try to run some optimization passes on the module before handing it to the JITEngine.
