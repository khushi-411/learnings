import torch
import torchvision.models as models
from torch.profiler import profile, ProfilerActivity, record_function


model = models.resnet18()
inputs = torch.randn(5, 3, 224, 224)


with profile(activities=[ProfilerActivity.CPU], record_shapes=True) as prof:
    with record_function("model_inference"):
        # additional context manager, puts the model in inference mode,
        # so gradient tracking, view traci=king & version counter are disabled
        # makes model faster
        with torch.inference_mode():
            model(inputs)


print(prof.key_averages().table(sort_by="cpu_time_total", row_limit=10))
