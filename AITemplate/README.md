### Build Dependencies

#### Install AITemplate

```
git clone --recursive https://github.com/facebookincubator/AITemplate
cd python
python setup.py bdist_wheel
pip install dist/*.whl --force-reinstall
```

#### Install Libraries

```
pip install torch==1.12.1+cu116 torchvision==0.13.1+cu116 torchaudio==0.12.1 -f https://download.pytorch.org/whl/torch_stable.html
```

#### FAQs

1. If it shows `nvcc not found`, configure using:
```
export CUDA_HOME=/usr/local/cuda
export PATH=${CUDA_HOME}/bin:${PATH}
export LD_LIBRARY_PATH=${CUDA_HOME}/lib64:$LD_LIBRARY_PATH
``` 
