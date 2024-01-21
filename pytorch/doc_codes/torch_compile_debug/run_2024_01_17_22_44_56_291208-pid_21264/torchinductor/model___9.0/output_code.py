
from ctypes import c_void_p, c_long
import torch
import math
import random
import os
import tempfile
from math import inf, nan
from torch._inductor.hooks import run_intermediate_hooks
from torch._inductor.utils import maybe_profile
from torch._inductor.codegen.memory_planning import _align as align

from torch import device, empty, empty_strided
from torch._inductor.codecache import AsyncCompile
from torch._inductor.select_algorithm import extern_kernels

aten = torch.ops.aten
inductor_ops = torch.ops.inductor
assert_size_stride = torch._C._dynamo.guards.assert_size_stride
alloc_from_pool = torch.ops.inductor._alloc_from_pool
reinterpret_tensor = torch.ops.inductor._reinterpret_tensor
async_compile = AsyncCompile()


cpp_fused_maximum_neg_0 = async_compile.cpp('''
#include "/tmp/torchinductor_khushi/gb/cgbau5vlj6cetmcjbjbtw6x4rrivaln6f45s5d72gy2bfx5foz3k.h"
extern "C" void kernel(const unsigned char* in_ptr0,
                       const unsigned char* in_ptr1,
                       unsigned char* out_ptr0)
{
    {
        #pragma GCC ivdep
        for(long x0=static_cast<long>(0L); x0<static_cast<long>(8390L); x0+=static_cast<long>(1L))
        {
            #pragma GCC ivdep
            for(long x1=static_cast<long>(0L); x1<static_cast<long>(8L); x1+=static_cast<long>(1L))
            {
                auto tmp0 = in_ptr0[static_cast<long>(x1 + (8L*x0))];
                auto tmp1 = in_ptr1[static_cast<long>(x1)];
                auto tmp2 = decltype(tmp1)(-tmp1);
                auto tmp3 = max_propagate_nan(tmp0, tmp2);
                out_ptr0[static_cast<long>(x1 + (8L*x0))] = tmp3;
            }
        }
    }
}
''')


async_compile.wait(globals())
del async_compile

def call(args):
    arg0_1, arg1_1 = args
    args.clear()
    assert_size_stride(arg0_1, (1, 8), (8, 1))
    assert_size_stride(arg1_1, (8390, 8), (8, 1))
    buf0 = empty((8390, 8), device='cpu', dtype=torch.uint8)
    cpp_fused_maximum_neg_0(c_void_p(arg1_1.data_ptr()), c_void_p(arg0_1.data_ptr()), c_void_p(buf0.data_ptr()))
    del arg0_1
    del arg1_1
    return (buf0, )


def benchmark_compiled_module(times=10, repeat=10):
    from torch._dynamo.testing import rand_strided
    from torch._inductor.utils import print_performance
    arg0_1 = rand_strided((1, 8), (8, 1), device='cpu', dtype=torch.uint8)
    arg1_1 = rand_strided((8390, 8), (8, 1), device='cpu', dtype=torch.uint8)
    fn = lambda: call([arg0_1, arg1_1])
    return print_performance(fn, times=times, repeat=repeat)


if __name__ == "__main__":
    from torch._inductor.wrapper_benchmark import compiled_module_main
    compiled_module_main('None', benchmark_compiled_module)
