import torch
import torchvision.models as models
from torch.profiler import profile, record_function, ProfilerActivity


model = models.resnet18()
inputs = torch.randn(5, 3, 224, 224)


with profile(activities=[
    ProfilerActivity.CPU, ProfilerActivity.CUDA],
    record_shapes=True,
    profile_memory=True) as prof:
    with record_function("model_inference"):
        model(inputs)


print(prof.key_averages().table(sort_by="cpu_memory_usage", row_limit=10))
