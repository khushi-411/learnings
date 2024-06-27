### Python Custom Operators

[Reference Link](https://pytorch.org/tutorials/advanced/python_custom_ops.html#python-custom-ops-tutorial)

- **Goal**: Introduce a method to use a new customized operator with PyTorch such that they behave like PyTorch native operator.
- Why we need?
    - To treat that function as an opaque callable with respect to torch.compile.
    - Add training support to an arbitrary Python function.

In order to black-box the function, we need to do two things:
- wrap the function into a PyTorch custom operator.
- Add a `FakeTensor kernel` to the operator. Given function should have meta data of input tensors, to compute meta data of output tensors.

#### Adding training support
- Use `torch.library.register_autograd`.

#### Testing Python Custom operators
- Use `torch.library.opcheck`: to test that the custom operator was registered correctly.
- This does not check that the gradients are mathemathically correct.

#### Mutable Python Custom operators
- We can add function that mutates its inputs. Many low-level kernels are written like this.
