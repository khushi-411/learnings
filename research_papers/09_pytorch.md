# PyTorch: An Imperative Style, High-Performance Deep Learning Library

> By ***Adam Paszke, Sam Gross, Francisco Massa, Adam Lerer,
James Bradbury, Gregory Chanan, Trevor Killeen, Zeming Lin, Natalia Gimelshein,
Luca Antiga, Alban Desmaison, Andreas Köpf, Edward Yang, Zach DeVito, Martin Raison, Alykhan Tejani,
Sasank Chilamkurthy, Benoit Steiner, Lu Fang, Junjie Bai, Soumith Chintala***

[Research Paper Link](https://arxiv.org/abs/1912.01703)

### Abstract
- Pythonic programming style (easy to use), speed, support multiple hardware architectures.
- Paper presents the internal implementation of PyTorch.
- Also, presents how its runtime enables a compelling performance.

### Introduction
- Earlier frameworks like Caffe, CNTK, TensorFlow, and Theano constructs a static dataflow graph that represents computation and applied repeatedly to batches of data.
- PyTorch performed all the computation ahead of time.
- Uses dynamic tensor computation with automatic differetiation and GPU acceleration.
    - Previous work: Chainer (performance is not good here), Torch. DyNet (these models have limited applicability).

### Background
Trends popular in deep learning:
1. **Domain specific languages**: turn multidimensional arrays into first-class objects.
    - Starting in 1960s, languages like APL, MATLAB, R, and Julia.
    - These days languages like NumPy, Torch, Eigen, Lush: made array-based programming.
2. **Development of automatic differentiation**: Allows gradient based optimization.
    - Other autograd packages: Chainer, DyNet, Lush, Torch, Jax, Flux.jl
3. **Movement to open-source Python ecosystem**:
    - Communities that started this: NumPy, SciPy, and Pandas.
    - Other softwares: Lush in Lisp, Torch in C++, Objective-C and Lua, EBLearn in C++, Caffe in C++.
4. **Take advantage of hardware accelerators**.
    - Frameworks: Caffe, Torch7, TensorFlow.

### Design principles
Main ideas:
1. Be Pythonic
2. Put researchers first
3. Provide pragmatic performance
4. Worse is better

### Usability centric design

#### Deep learning models are just Python programs
 

### Conclusion
- Usable with careful performance considerations.
- Worked on PyTorch JIT.
- Improved support for distributed computation.
