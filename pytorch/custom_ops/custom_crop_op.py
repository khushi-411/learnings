import torch
from torchvision.transforms.functional import to_pil_image, pil_to_tensor
import PIL
import IPython
import matplotlib.pyplot as plt
from typing import Sequence


# define new custom operator
# if operator mutates any input tensor, their names should
# be written in mutates_args argument
@torch.library.custom_op("mylib::crop", mutates_args=())
def crop(pic: torch.Tensor, box: Sequence[int]) -> torch.Tensor:
    img = to_pil_image(pic.cpu())
    cropped_img = img.crop(box)
    return (pil_to_tensor(cropped_img) / 255.).to(pic.device, pic.dtype)


# register fake tensor kernel
@crop.register_fake
def _(pic, box):
    channels = pic.shape[0]
    x0, y0, x1, y1 = box
    return pic.new_empty(channels, y1 - y0, x1 - x0)


@torch.compile(fullgraph=True)
def f(img):
    return crop(img, (10, 10, 50, 50))

cropped_img = f(img)
display(img)


display(cropped_img)
