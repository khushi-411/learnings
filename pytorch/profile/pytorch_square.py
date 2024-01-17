# Ref: https://github.com/msaroufim/cudamodelecture1/blob/main/pytorch_square.py

import torch

def time_pytorch_function(func, input):
    # CUDA is async so can't use python time module
    start = torch.cuda.Event(enable_timing=True)
    end = torch.cuda.Event(enable_timing=True)

    # Warmup
    for _ in range(5):
        func(input)

    start.record()
    func(input)
    end.record()
    torch.cuda.synchronize()
    return start.elapsed_time(end)

a = torch.tensor([1., 2., 3.])
b = torch.randn(10000, 10000).cuda()

def square_2(a):
    return a * a

def square_3(a):
    return a ** 2

time_pytorch_function(torch.square, b)
time_pytorch_function(square_2, b)
time_pytorch_function(square_3, b)

print("==========")
print("Profiling torch.square")
print("==========")

with torch.autograd.profiler.profile(use_cuda=True) as prof:
    torch.square(b)

print(prof.key_averages().table(sort_by="cuda_time_total", row_limit=10))

print("==========")
print("Profiling a * a")
print("==========")

with torch.autograd.profiler.profile(use_cuda=True) as prof:
    square_2(b)

print(prof.key_averages().table(sort_by="cuda_time_total", row_limit=10))

print("==========")
print("Profiling a ** 2")
print("==========")

with torch.autograd.profiler.profile(use_cuda=True) as prof:
    square_3(b)

print(prof.key_averages().table(sort_by="cuda_time_total", row_limit=10))
