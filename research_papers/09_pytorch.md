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
- Earlier frameworks like Caffe, CNTK, TensorFlow, and Theano construct a static dataflow graph that represents computation and is applied repeatedly to batches of data.
- PyTorch performed all the computations ahead of time.
- Uses dynamic tensor computation with automatic differentiation and GPU acceleration.
    - Previous work: Chainer (performance is not good here), Torch. DyNet (these models have limited applicability).

### Background
Trends popular in deep learning:
1. **Domain specific languages**: turn multidimensional arrays into first-class objects.
    - Starting in the 1960s, languages like APL, MATLAB, R, and Julia.
    - These days languages like NumPy, Torch, Eigen, and Lush: are made array-based programming.
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
- PyTorch foregoes the benefits of a graph-metaprogramming based approach.
- It extends to all aspects of deep learning workflows.
    - Defining layers, composing models, loading data, running optimizers, and parallelizing the training process.
- PyTorch programs are executed eagerly.
    - Users do not have to wait for lengthy compilation before they can start running their program.
    - We also observe intermediate computations to analyze the model.
Some neural network examples:
```python
class LinearLayer(Module):
    def __init__(self, in_sz, out_sz):
        super().__init__()
        t1 = torch.randn(in_sz, out_sz)
        self.w = nn.Parameter(y1)
        t2 = torch.randn(out_sz)
        self.b = nn.Parameter(t2)

    def forward(self, activations):
        t = torch.mm(activations, self.w)
        return t + self.b
```

#### Interoperability and extensibility
- It allows for bidirectional exchange of data with external libraries.
    - Example converting between NumPy arrays and PyTorch tensors, or exchanging data stored using DLPack format. There's no data copying so the operation is very cheap.
- Automatic differentiation has allowed users to support custom differentiable functions.
    - Users have to define a new subclass of **`torch.autograd.Function`**. This implements `forward()` and `backward()` methods.
        - These perform their derivatives (vector-Jacobian product).
- New datasets can be added by subclassing **`torch.utils.data.Dataset`**. It implements two methods `__getitem__` (the indexing operator) and `__len__` (the length operator).
   - This makes datasets behave like lists (possibly lazy).

#### Automatic differentiation
- Automatically compute gradients (all in Python programs).
- It uses an operator overloading approach, which builds a representation of the computed function every time it is executed.
- Performs reverse-mode automatic differentiation.
- Differentiating functions with more outputs than inputs is more efficiently executed using forward-mode automatic differentiation.
    - Less common in ML applications.
    - Performs it using array-level dual numbers.
- Performs differentiation through code using mutation on tensors.
- Users can decide whether to copy while writing or not.

### Performance focused implementation

#### An efficient C++ core
- Written in C++
- `libtorch`: implements the tensor data structure, GPU and CPU operators, and basic parallel primitives.
- Provides automatic differentiation system.
    - Ensures computation is executed entirely in a multithreaded evaluator, not in Python global lock.
- Python bindings are generated using YAML meta-data files.
    - This allowed to creation of bindings to other languages too.
- We can also write code without Python using the TorchScript engine.

#### Separate control and data flow
- Strict separation between its control (program branches, loops) and data flow (tensors and operations performed on them).
    - Control is handled by Python and optimized C++ code is executed on the host CPU.
- It executes operators asynchronously on GPU.
    - It queues (FIFO) CUDA kernel invocations to the GPU hardware.
    - This allows the user to perform the overlap of the execution of Python code on the CPU with tensor operations on the GPU.

#### Custom caching tensor allocator
- Critical to optimize the speed of the dynamic memory allocators.
    - Because every operator must dynamically allocate output tensor.
- It relies on optimized libraries to perform tasks on the CPU.
- In GPU, it has `cudaFree`, which blocks its caller until the previous process is executed.
    - Therefore PyTorch has its own **custom allocator**. It builds up a cache of CUDA memory and reassigns it to later allocations without further use of CUDA APIs.
        - It's beneficial because taking all GPU memory ahead of time would prevent users from utilizing other GPU-enabled Python packages.
        - It was turned for specific memory usage patterns of DL.
- **One-pool-per-stream design** improves the performance of the allocator.
    - Because the CPU runs ahead of the GPU, memory is freed on the CPU before its last use on the GPU finishes.
    - Seems limiting because allocations end up fragmentation per stream, but in practice, PyTorch never uses multiple streams.
- Streams serialize execution
    - If the free precedes the reallocation on the CPU, the same order will occur on the GPU.
    - Allocator can reallocate memory freed on the CPU immediately as long as the new allocation is used on the same stream as the freed region.
- Data loading and distributed computing utilities are exceptions to the one-stream design.

#### Multiprocessing
- Due to global interpreter lock (GIL), python's default implementation does not allow concurrent threads to execute in parallel.
- To solve this program Python community has established a standard `multiprocessing` module.
    - Implementation is inefficient.
- Hence, PyTorch has **`torch.multiprocessing** module. It automatically moves the data of tensors to other processes to shared memory instead of sending it over a communication channel.
- Improves performance, makes process weaker.
- Transparently handles sharing of CUDA tensors.

#### Reference counting
- Garbage collection is a way to automatically manage tensor memory.
    - Runtime investigates the state of the system, enumerates used objects, and frees everything else.
    - While deallocation it causes the program to use more memory.
- PyTorch takes a different approach, it relies on **reference counting**.
    - Counts the number of uses of each tensor and free immediately once the count returns zero.
- Counts references of both the libtorch library and external references made by the PyTorch program.

### Evaluation
1. **Asynchronous dataflow**
2. **Memory management**
    - In experiments, initially, CUDA memory management functions like (cudaMalloc and cudaFree) slow down the execution by blocking the CPU thread, hence lowering the utilization of the GPU.
    - This effect disappears in further iterations as PyTorch caching memory allocator starts reusing previously allocated regions.
3. **Benchmarks**

<div align= "center">

| Framework      | AlexNet     | VGG-19     | ResNet-50   | MobileNet   | GNMTv2      | NCF         |
| -------------- | ----------- | ---------- | ----------- | ----------- | ----------- | ----------- |
| Chainer        | 778 ± 15    | N/A        | 219 ± 1     | N/A         | N/A         | N/A         |
| CNTK           | 845 ± 8     | 84 ± 3     | 210 ± 1     | N/A         | N/A         | N/A         |
| MXNet          | 1554 ± 22   | 113 ± 1    | 218 ± 2     | 444 ± 2     | N/A         | N/A         |
| PaddlePaddle   | 933 ± 123   | 112 ± 2    | 192 ± 4     | 557 ± 24    | N/A         | N/A         |
| TensorFlow     | 1422 ± 27   | 66 ± 2     | 200 ± 1     | 216 ± 15    | 9631 ± 1.3% | 4.8e6 ± 2.9%|
| PyTorch        | 1547 ± 316  | 119 ± 1    | 212 ± 2     | 463 ± 17    | 15512 ± 4.8%| 5.4e6 ± 3.4%|

</div>

### Conclusion
- Usable with careful performance considerations.
- Worked on PyTorch JIT.
- Improved support for distributed computation.
