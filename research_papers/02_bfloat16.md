# A Study of BFLOAT16 for Deep Learning Training <sup>[link](https://arxiv.org/pdf/1905.12322.pdf)</sup>

> By Dhiraj Kalamkar, Dheevatsa Mudigere, Naveen Mellempudi, Dipankar Das,
Kunal Banerjee, Sasikanth Avancha, Dharma Teja Vooturi, Nataraj Jammalamadaka,
Jianyu Huang, Hector Yuen, Jiyan Yang, Jongsoo Park, Alexander Heinecke,
Evangelos Georganas, Sudarshan Srinivasan, Abhisek Kundu,
Misha Smelyanskiy, Bharat Kaul, and Pradeep Dubey

### Abstract
- Paper demonstrates the efficacy of BFloat16 for deep learning training.
- Why BFloat16? Because the value ranges the same as fp32, and conversion to/from fp32 is simple.
- Why compare with the fp32 range? No hyperparameter tuning is required for convergence.
- Experiments with: Tensorflow, Caffe2, IntelCaffe, and Neon.

### Introduction
- Recent developments on architectures for GEMM and computing on low precision.
- For inference and training: mixed precision technique.
- Dtypes for computing in lower precision: fp16, 16b int, bf16.
- All these dtypes have 16-bit input operands and 32-bit accumulators for the computations.
- **BFloat16**:
    - low precision storage format to reduce communication volumes of weights and activations.
- **Quantlib**: Library developed by the researchers to implement multiple deep learning frameworks.
- Zeros out the lower 16 bits of the fp32 and performs rounding nearest to those bits.
- Observations:
    - **fp16 training**: requires hyper-parameter tuning for loss scaling.
    - **int16 training**:  requires fine-grained block-quantization and maintaining block-level scaling factors.
    - **bf16 training**: no other hyperparameter changes to achieve the desired results.

### Related Work
