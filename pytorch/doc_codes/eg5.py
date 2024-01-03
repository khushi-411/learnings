import torch


from torchvision.models import resnet18
def init_model():
    return resnet18().to(torch.float32).cuda()


model = init_model()
opt = torch.optim.Adam(model.parameters())



