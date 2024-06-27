import torch
from torchvision.transforms.functional import to_pil_image, pil_to_tensor
import PIL
import IPython
import matplotlib.pyplot as plt


# graph break on function, if we use torch.compile()
# @torch.compile(fullgraph=True)
def crop(pic, box):
    img = to_pil_image(pic.cpu())
    cropped_img = img.crop(box)
    return pil_to_tensor(cropped_img).to(pic.device) / 255.


def display(img):
    plt.imshow(img.numpy().transpose((1, 2, 0)))


img = torch.ones(3, 64, 64)
img *= torch.linspace(0, 1, steps=64) * torch.linspace(0, 1, steps=64).unsqueeze(-1)
display(img)


cropped_img = crop(img, (10, 10, 50, 50))
display(cropped_img)

