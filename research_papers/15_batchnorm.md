# Batch Normalization: Accelerating Deep Network Training by Reducing Internal Covariate Shift

> By ***Sergey Ioffe, Christian Szegedy***

[Research Paper Link](https://arxiv.org/abs/1502.03167)

### Abstract
- Problems while training deep neural networks:
    - Input layer changes during training, as the previous layers parameter changes.
    - Selection of learning rate.
    - Parameter initialization.
    - Staturating non-linearities.
- This problem is solved via normalizing layer inputs.
- Batch norm helps in selecting higher learning rates and caring less about initialization.
- It also acts as a regularizer.
- Model reaches same accuracy with 14 times fewer steps.

### Introduction
- SGD 
