# NOTE: use chrome://tracing to view the generated traces
# shows when, which opeartor was invoked
# in the trace, you'll see some gaps, it usually happens when
# the operator is waiting for another call, or if any opearator is initiated but not yet run


import torch
import torchvision.models as models
from torch.profiler import profile, record_function, ProfilerActivity


model = models.resnet18()
inputs = torch.randn(5, 3, 224, 224)


with profile(activities=[
        ProfilerActivity.CPU, ProfilerActivity.CUDA], record_shapes=True) as prof:
    with record_function("model_inference"):
        model(inputs)


prof.export_chrome_trace("trace.json")


print(prof.key_averages().table(sort_by="cuda_time_total", row_limit=10))
