import torch
import thunder


def foo(a, b):
    return a + b


jfoo = thunder.jit(foo)

a = torch.full((2, 2), 1)
b = torch.full((2, 2,), 3)

result = jfoo(a, b)

print(result)
