# Ref: https://triton-lang.org/main/getting-started/tutorials/03-matrix-multiplication.html

import torch

import triton
import triton.language as tl


torch.manual_seed(0)
a = torch.randn((512, 512), device='cuda', dtype=torch.float16)
