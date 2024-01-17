#### Steps
1. Import all necessary libraries.
2. Instantiate a simple neural network model.
3. Using profiler to analyze **execution time**.
4. Using profiler to analyze **memory consumption**.
5. Using **tracing** functionality.
6. Examining **stack traces**.
7. Visualizing data as a **flame graph**.
8. Using profiler to analyze **long-running jobs**.


#### Tuning PyTorch Models
- Multi-process Data Loading 
- Memory Pinning
- Inference Mode
- Set grad to None
- Enable cuDNN auto-tuner
- Use DistributedDataParallel instead of DataParallel
- Fuse point-wise operators
- Use Fused Optimizers
- Checkpoint intermediate buffers
- Avoid unnecessary CPU-GPU synchronization
- Use mixed precision and AMP


#### References
- [PyTorch Doccumentation](https://pytorch.org/tutorials/recipes/recipes/profiler_recipe.html)
- [PyData Global 2021: Profiling and Tuning PyTorch Models - Shagun Sodhani](https://www.youtube.com/watch?v=-SNdvNdnEl8&t=249s)
