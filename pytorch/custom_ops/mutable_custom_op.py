import torch
import numpy as np


@torch.library.custom_op("mylib::numpy_sin", mutates_args={"output"}, device_types="cpu")
def numpy_sin(input: torch.Tensor, output: torch.Tensor) -> None:
    assert input.device == output.device
    assert input.device.type == "cpu"
    input_np = input.numpy()
    output_np = output.numpy()
    np.sin(input_np, out=output_np)


# operator does not return anything,
# therefore we don't need to register a FakeTensor
@torch.compile(fullgraph=True)
def f(x):
    out = torch.empty(3)
    numpy_sin(x, out)
    return out


x = torch.randn(3)
y = f(x)
assert torch.allclose(y, x.sin())


# testing
example_inputs = [
    [torch.randn(3), torch.empty(3)],
    [torch.randn(0, 3), torch.empty(0, 3)],
    [torch.randn(1, 2, 3, 4, dtype=torch.double), torch.empty(1, 2, 3, 4, dtype=torch.double)],
]

for example in example_inputs:
    torch.library.opcheck(numpy_sin, example)
