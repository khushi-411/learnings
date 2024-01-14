# Triton: An Intermediate Language and Compiler for Tiled Neural Network Computations

> By ***Philippe Tillet, H. T. Kung, David Cox***

[Research Paper Link](https://www.eecs.harvard.edu/~htk/publication/2019-mapl-tillet-kung-cox.pdf)

### Abstract
- Persent senario often limited by the availability of efficient kernels.
- Another limitation is its very hard to write the efficient kernels.
- Paper present Triton language and compiler, centered around the concept of *tile*.
- Approach:
    - C-based language and an LLVM-based intermediate representation (IR) for expressing tensor programs in terms of operations on parametric tile variables.
    - A set of novel tile-level optimization passes for compiling these programs into efficient GPU code.
- Paper demonstrate how we can use Triton to present portable implementation of matrix multiplication and convolution giving equivalent performance of of cuBLAS / cuDNN.

### Introduction
- With the development of DNNs in recent days, GPUs plays a fundamental role. This lead to huge popularity of libraries like cuBLAS, cuDNN etc. These libraries brought hardware support but writing an efficient code was a challenging tasks.
- Other libraries developed to solve this problem: Halide, TVM, PlaidML, etc. These perform well in certain types of problems but are not widely accepted.
- Main contributions of the paper:
    - **Triton-C**: C-like language for expressing tensor programs in terms of parametric tile variables.
    - **Triton-IR**: LLVM-based intermediate representation (IR). It provides an environment suitable for tile-level program analysis, transformation and optimization.
    - **Triton-JIT**: A JIT compiler and code generation backend for compiling Triton-IR programs into efficient LLVM bitcode. It includes:
        - Set of tile-level, machine-independent passes aimed at simplifying input compute kernels independently of any compilation target.
        - Set of machine-dependent passes for generating efficient GPU-ready LLVM-IR.
        - An auto-tuner that optimize any meta-parameter associated with the above passes.
    - **Numerical Experiments**: Numerical expression of triton demonstrating matrix multiplication implementation, re-implement cuDNN's IMPLICIT_GEMM algorithm, efficient implementation of shift-conv modules.

<p align="center">
  <img src="images/triton.png" alt="Overview of Triton">
</p>

### Related Work
Triton relies on tile-level operations and optimizations into traditional compilation pipelines. Previous approachers include:
- **Tensor-level IRs**: Used by XLA and Glow. Transform tensor programs into LLVM-IR and CUDA-C operation.
- **Polyhedral model**: Used by Tensor Comprehensions (TC) and Diesel. To parameterize and automate the compilation of DNN layers into LLVM-IR and CUDA-C programs.
- **Loop synthesizers**: Used by Halide and TVM. To transform tensor compulations into loop nests that can be manually optimized using user-defined schedules.

### Triton-C Language

#### Syntax
Based on ANSI C (i.e., CUDA-C), but was modified as follows:
- **Tile declarations**: Special syntax for multi-dimentional arrays (`int tile[16, 16]`). Tile shapes are constant but can also be made parametric with the `tunable` keyword.
- **Built-in functions**: Common elementwise array-operations (+, -, &&, * , etc) and built-in functions like dot, trans, etc were added.
- **Broadcasting**: Can be done along any axis using `newaxis` keyword and using slicing syntax.
- **Prediction**: Basic control-flow withing tile operations.

#### Semantics
It has a NumPy-like semantics. Triton-C is strongly typed and they have to obey strict shape constraints.
1. **Tile Semantics**: Built-in tile types main benefits:
    - Simplifies the structure of tensor programs by hiding performance details intra-tile memory coalescing, cache management and hardware utilization.
    - Opens door for compilers to perform optimizations automatically.
2. **Broadcasting Semantics**: Set of rules to perform these conversions:
    - *Padding*: the shape of the shortest operand is left-padded with ones until both operands have the same dimensionality.
    - *Broadcasting*
3. **Programming Model**: Content of both operands are replicated until their shape is identical.

#### Programming Model
- Similar to CUDA-C, but each kernel is ***single-threaded***, automatically parallelized.
- Global ranges associated with a kernel can be queried using `get_global_range(axis)`.

<p align="center">
  <img src="images/triton_model.png" alt="Difference between the CUDA and the Triton programming model">
</p>

### Triton IR
- LLVM-based IR which provide an environment suitable for tile-level program analysis, transformation and optimization.
- Triton IR programs are constructed directly from Triton-C during parsing.
- Triton-IR and LLVM-IR programs share the same high-level structure. But Triton-IR also includes number of extensions necessary for tile-level data-flow and control-flow analysis.

#### Structure
1. **Modules**
    - Highest level
    - These are one or more basic units of compilation.
    - These are compiled independently and then aggregated by the linker.
    - Consists of functions, global variables, constants, etc.
2. **Functions**
    - Consists of a return type, a name, and an empty arguments lists.
    - Function attributes and parameter attributes can also be specified and optimizations can be performed.
3. **Basic Blocks**
    - Straight-line code sequences that may contain terminator instructions.
    - Use Static Single Assignment (SSA) form i.e., each variable in each basic block is assigned only once and defined before being used.
    - Defines Data-Flow Graph (DFG) whose different path corresponds to use-def chains in the programs SSA's representation.
    - This form can directly created from ASTs.

#### Support for Tile-Level Data-Flow Analysis
1. **Types**
    - Declared similary as in LLVM-IR.
    - No `tunable` keyword in Triton-IR, hence parametric shape values must be resolved before programs are generated.
2. **Instructions**
    - Produced by Triton-IR, it's purpose is to support broadcasting semantics.
        - ***reshape instruction***: creates a tile of the specified shape using data from its input argument.
        - ***broadcast instruction***: creayes a tile of specified shapes by replicating its input argument as needed.
        - ***arithmetic instruction***: for transpositions (*trans*) and matrix multiplication (*dot*).
3. **Support for Tile-Level Control-Flow Analysis**
    - Problem: it's very divergent control flow within the tiles.
    - Proposed solutions: use of Predicted SSA. Requires addition of two instructions:
        - ***cmp instructions***: similar to comparision instructions, but just return two opposite predicates instead of one.
        - ***psi instructions***: merges instructions from different streams of predicted instructions.

### The Triton-JIT compiler
Goal: simplify and compile Triton-IR programs into efficient machine code via the following passes:

#### Machine-Independent Passes
1. **Pre-Fetching**: Triton-IR detects loops and adds adequate prefetching code to avoid latency problem.
2. **Tile-Level Peephole Optimization**: Means simplifying the chain of transpositions using some identity.

#### Machine-Dependent Passes
Triton-IR consists of hierarchical tiling, memory coalescing, shared memory allocation and shared memory synchronization.
1. **Hierarchical Tiling**
    - Aim to decompose tiles into micro-tiles and nano-tiles to fit a machine's compute capabilities and memory hierarchy as tightly as possible.
    - The structure is possible to automatically enumerate and optimize valid nested tiling configurations for any expressible program.
<p align="center">
  <img src="images/hierarchical_tiling.png" alt="Hierarchical Tiling in the Triton-IR Machine Model">
</p>

2. **Memory Coalescing**
    - Memory is said to be coalesced when adjacent threads simultaneously access nearby memory locations.
    - How to reduce the number of memory transactions? Triton-IR programs are single-threaded and automatically parallelized, the compiler backend is able to order threads internally within each micro-tile to avoid uncoalesced.
<p align="center">
  <img src="images/coalescing.png" alt="Uncoalesced (a) and coalesced (b)">
</p>

3. **Shared Memory Allocation**
    - Benefit from temporarily storing the operands in fast shared memory.
    - Goal: determine when and where a tile should be stashed to this space.
<p align="center">
  <img src="images/shared_memory_alloc.png" alt="Shared Memory Allocation">
</p>

4. **Shared Memory Synchronization**
    - Read and write to shared memory are asynchronous in their machine model.
    - Goal: automatically inserts barriers in the generated GPU source code.
    - This is done by read-after-writes (RAW) and write-after-read (WAR) as follows:
<p align="center">
  <img src="images/shared_memory_sync.png" alt="Shared Memory Synchronization">
</p>

5. **Auto-tuner**
    - Automatically extract optimization spaces from IR programs.
    - In this work, only hierarchical tiling process is considered to no more than 3 tiling parameters per dimension per tile.
    - These parameters are then optimized using power of two.
        - tile size: 32 and 128
        - micro-tile size: 8 and 32
        - nano-tile size: 1 and 4

### Numerical Experiments
1. Matrix Multiplication
2. Convolutions
    - Dense Convolutions
    - Shift Convolutions

### Conclusions
- Introduced language and compiler for expressing and compiling tile neural network computations into efficient machine code.
- Showed that addition of various data-flow and control-flow extentions to LLVM-IR can enable various tile-level optimization passes which lead to performance.
- Proposed Triton-C language which are able to implement efficient kernels.
