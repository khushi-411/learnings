# The Zephyr Abstract Syntax Description Language

> By Daniel C. Wang, Andrew W. Appel, Jeff L. Korn, Christopher S. Serra

[Research Paper Link](https://www.usenix.org/legacy/publications/library/proceedings/dsl97/full_papers/wang/wang.pdf)

### Abstract
- ASDL: Abstract Syntax Description Language
- It describes the abstract syntax of compiler IRs and other tree-like data structures.
- How to convert ASDL description into appropriate data structure?
- Lacks subtyping and inheritance but is simple and powerful.
- How to convert ASDL to C, C++, Java etc?
- This paper describes details about ASDL!

### Introduction


### Future Work
- It should support modularized descriptions.
    - For this, we'll be required to check how modular descriptions are translated into the target language.
    - Should they allow cyclic modular description?
- We need to work on tools for building ASDL definitions.
- The current system directly transforms ASDL to the target language; we need some hook to control how descriptions are translated.
- Approach can be extended into a tool that generates code generators for ASDL data types.

### Conclusions
- ASDL (description language): depicts the notion for describing the abstract syntax of the programming language or IRs of the compilers.
- ASN.1: a reinvention of ASDL, it provides support for cross-language interpretation.
