# To generate Triton kernel run:
# TORCH_LOGS="output_code" python compile_square.py

import torch

x = torch.tensor([1, 2, 3, 4, 5], dtype=torch.float32)

@torch.compile()
def func(x):
    return torch.square(x)

func(x)
