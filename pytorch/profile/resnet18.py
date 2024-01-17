import torch
import torchvision.models as models
from torch.profiler import profile, record_function, ProfilerActivity


model = models.resnet18().cuda()
inputs = torch.randn(5, 3, 224, 224).cuda()


# record_shapes can slow down the run
# profiler shows the series of operations
with profile(activities=[ProfilerActivity.CPU, ProfilerActivity.CUDA], record_shapes=True) as prof:
    # record_function: context manager to label arbitrary code ranges with user provided names
    with record_function("model_inference"):
        model(inputs)


# print(prof.key_averages().table(sort_by="cpu_time_total", row_limit=10))


print(prof.key_averages().table(sort_by="cuda_time_total", row_limit=10))


# To get a finer granularity of results and include operator input shapes
# print(prof.key_averages(group_by_input_shape=True).table(sort_by="cpu_time_total", row_limit=10))
