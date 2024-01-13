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

