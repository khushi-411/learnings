# Automatic differentiation in PyTorch

> By ***Adam Paszke, Sam Gross, Soumith Chintala, Gregory Chanan,
Edward Yang, Zachary DeVito, Zeming Lin,
Alban Desmaison, Luca Antiga, Adam Lerer***

[Research Paper Link](https://openreview.net/pdf?id=BJJsrmfCZ)

### Abstract
- Describe automatic differentiation module in PyTorch.
- Provides a high performance environment on different devices.
- Does not follow symbolic approach.

### Background
- **Dynamic, define-by-run execution**
    - Function can be differentiated by running desired computation.
    - As oppose to static graph structure (differentiated symbolically ahead of time).
- **Immediate, eager execution**
    - Runs tensor computations as it encounters them.
    - Records only things that are necessary to differentiate the computation.
- **In-place operations**
    - Hazard for automatic differentiation, because it can invalidate data needed in the differentiation phase.
    - Also, they require nontrivial tape transformations to be performed.
- **No tape**
    - This optimization allows to avoid the implementation of topological sort.
    - PyTorch skips this tape, hence allow to record the computaion graph that was needed for computation.
- **Core logic in C++**
    - Because it gets comparitively lower overhead compared to when written in Python.

### Interface
1. **Variable flags**: If we don't want to compute gradients, PyTorch provides two flags **requires grad** and **volatile**. If any input variable "requires grad" or is "volatile", the output is also "requires grad" or is "volatile".
2. **Hooks**: To allow users to inspect gradients.
3. **Extensions**: Users can create custom differentiable operations.

### Implementation
- A variable is simply a wrapper around a Tensor that also holds a reference to a graph of Function objects.
- Graph: immutable and functional representation of derivative.
- Variable is a mutable pointer to its graph.
- **Memory management**
    - PyTorch frees up intermidiate values as soon as they are not needed.
    - Python is well suited for this purpose. As it uses reference counting by default.
    - Challenge **avoiding reference cycles**.
        - PyTorch records only "saved variable" (omits a pointer to the Function) instead of full fledged variable.
- **C++ operators**
    - To reduce overhead and lowers the latency, lowers latency.
    - We can execute multiple threads in parallel (in Python we cannot use it because of GIL).

#### Supporting in-place operations
- **In-place operations**: To avoid allocating a new tensor when its known to be unnecessary.
- Here, variables are modified, instead in out-place a new variable is created and operations are performed on newly created variable.
- How inplace operations interact with gradients? By default, it raises an error.
- **Invalidation**: It can invalidate data needed to compute derivatives.
- **Aliasing**: require nontrivial transformations on computation histories of many variables.
    - Aliasing between variables, operations like transpose, narrow produce new tensors with new size and strides which share storage with the original tensors.
