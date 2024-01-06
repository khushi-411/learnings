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
- Grammar of ASDL:
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

#### Lexical Issues
- Lexical structure of tokens used in the ASDL grammar:
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

#### ASDL Fundamentals
- Consists of three fundamental constructs: ***types, constructors***, and ***productions***.
- **type**: productions that enumerate the constructors for that type.
    - Eg: *stm* type. It's value is created by one of three constructors (nodes) *Compound*, *Assign*, and *Print*.
    - *Compound* constructor has two fields whose values are of type *stm*, aka, it has two children that are subtrees.
    - *binop* type consists of only constructors which have no fields. These types are finite enumerations of values.
- ASDL does not provide an explicit enumeration type.
- There are three (int, indentifier, and string) primitive pre-defined types in ASDL.
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
- This shows it is easy to automatically generate data type declarations in target languages.

#### Generating Code from ASDL Descriptions
- Each ASDL type is represented as a pointer to a structure.
- Example to translate the *stm* type into C.
    ```asdl
    typedef struct_stm *stm_ty;
    struct_stm {
      enum {Compound kind=1, Assign kind=2,
            Print_kind=3} kind;
      union {
        struct { stm_ty stm1; stm_ty stm2; } Compound;
        struct { ... } Assign;
        struct { ... } Print;
      } v;
    };
    ...
    enum binop_ty {Plus=1, Minus=2, Times=3, Div=4};
    ...
    stm_ty Compound (stm_ty stm1, stm_ty stm2) f
        stm_ty p;

        p = malloc(sizeof(*p));
        p->kind = Compound kind;
        p->v.Compound.stm1 = stm1;
        p->v.Compound.stm2 = stm2;
        return p;
    }
    stm_ty Assign (identifier_ty identifier1, exp_ty exp1) { ... }
    stm_ty Print (exp_list_ty_exp_list1) { ... }
    ```
- Translation to a language to ML that has algebraic data type:
    ```asdl
    datatype stm = Compound of (stm * stm)
                 | Assign of (identifier * exp)
                 | Print of (exp list)
    ```

#### Field Names
- ASDL description allow the specification of a field name to access the values of constructor fields.
- Tools can easily create field names based on position and type of a constructor field.
- Providing names of the field improves redability of descriptions and code generated from those descriptions.
- ASDL description with field names:
    ```asdl
      stm    =  Compound(stm head, stm next)
             |  Assign(identifier lval, exp rval)
             |  Print(exp list args)
    exp list =  ExpList(exp head, exp list next)
             | Nil
    ```

#### Sequences

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
