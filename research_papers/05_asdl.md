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
- The components of compiler comminicate with each other through an IR.
- If compiler components can exchange compatible IRs they can ineroperate.
- To do this, we have to implement and transmit IR accross different components.
- To written files are called pickles and conversion to pickles is called pickling or marshaling.
- IRs need to be written in more than one programming language other wise compiler components written in different languages cannot interperate.
- IRs are usually tree-like data structure.
- A parser implementation is a poor way to describe the syntax of a programming language.
- This article describes ASDL, a simple declarative language for describing the abstract structures of IRs.
- IRs described with ASDL are converted into an implementation automatically by tools.
- Tools generate the data-structure definitions for a target language as well as the pickling functions and other supporting code.
- ASDL descriptions are more consise than data-structure definitions in languages.
- Summary on design goals of ASDL:
    - The language must be simple and concise.
    - The language must be able to encode existing IR's.
    - Tools that use the language must initially be able to produce code for C, C++, Java, and ML.
    - Tools must be able to produce code designed to be understood by programmers, not just other tools.
    - Language features must have a natural encoding in all the target languages.

### ASDL by example
Grammar of ASDL:
```asdl
definitions  =  {typ_id "=" type}
    type     =  sum_type | product_type
product type =  fields
  sum type   =  constructor f"|" constructorg
                ["attributes" fields]
constructor  =  con_id [fields]
    fields   = "(" {field ","} field ")"
    field    =  typ_id ["?" | "*"] [id]
```
- ASDL description consists of a sequence of productions, which defines the structure of tree-like data structures.
- ASDL description of trivial programming language:
    ```asdl
      stm    =  Compound(stm, stm)
             |  Assign(identifier, exp)
             |  Print(exp list)
    exp list =  ExpList(exp, exp list) | Nil
       exp   =  Id(identifier)
             |  Num(int)
             |  Op(exp, binop, exp)
      binop  =  Plus | Minus | Times | Div
    ```

#### Lexical Issues
Lexical structure of tokens used in the ASDL grammar:
```asdl
   upper  =  "A" | ... | "Z"
  lower   =  "a" | ... | "z"
  alpha   =  "_" | upper | lower
alpha_num =  alpha | "0" | ... | "9"
  typ_id  =  lower {alpha_num}
  con_id  =  upper {alpha_num}
    id    =  typ_id | con_id
```
- It contains formal semantic information that should be preserved by a tool when translating descriptions into implementations.
- The names of types and constructors are restricted to the intersection of valid identifiers in the initial set of target languages.
- To help user to understand between constructors and type names:
    - `types` are required to begin with a lower case.
    - `constructor names` must begin with an upper case.

### ASDL Fundamentals
- Consists of three fundamental constructs: ***types, constructors***, and ***productions***.

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
