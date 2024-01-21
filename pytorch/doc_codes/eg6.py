# Ref: https://pytorch.org/tutorials/intermediate/inductor_debug_cpu.html
# Run: TORCHDYNAMO_REPRO_AFTER="aot" TORCHDYNAMO_REPRO_LEVEL=4 python eg6.py


import torch
from torch._dynamo.utils import same

def foo2(x1, x2):
    a = torch.neg(x1)
    b = torch.maximum(x2, a)
    y = torch.cat([b], dim=0)
    return y

x1 = torch.randn((1, 8), dtype=torch.float32)
x2 = torch.randn((8390, 8), dtype=torch.float32)

expected_result = foo2(x1, x2)

compiled_foo2 = torch.compile(foo2)
actual_result = compiled_foo2(x1, x2)

assert same(expected_result, actual_result) == True
