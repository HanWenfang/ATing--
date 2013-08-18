ATing--
=======

ATing-- is a cool C++ development framework. ATing-- is an implementation for your ordinary C++ development with a shell and an editor.Now it has 
three modules: a modularized Build System, a code generator and a unit test framework[will coming soon].

Goals & features:

* A build system, which could be dynamically extensible
* A code generator, which could generate C++ style source code
* A general unit test framework  
* An IDE like dynamic languages for C++

Installation
=======
* Build the code generator program
    
    Change the directory to ./code-gen and
    
    $ ./make
    
    The release version "code-gen" and debug version "code-gend" will be created in ./code-gen/output/bin.

Basic Usage
=======
* Copy the BuildSystem/ fold to your work directory
* Copy the build output "code-gen" to the same directory
* $ ./code-gen App hello 
  
    will create /include/hello.h and src/hello.cpp with a namespace of App.
    
    will create a Makefile for your configuration and a components file.
* See the wiki for more information


