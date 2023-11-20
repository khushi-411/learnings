# Language Models are Unsupervised Multitask Learners <sup>[link](https://cdn.openai.com/better-language-models/language_models_are_unsupervised_multitask_learners.pdf)</sup>

> By Alec Radford, Jeffrey Wu, Rewon Child, David Luan,
Dario Amodei, Ilya Sutskever

### Abstract
- Demonstrate that the language model begain to learn the tasks without any explicit supervision.
- GPT-2: 1.5 billion parameter transformer (7/8 points), but this underfits WebText.
- WebText: New datasets of millions of webpages.

### Introduction
- Supervised learning models: brittke and sensitive to changes in the data distribution and task specification.
- Need a general system that can perform multiple tasks without the need of data training.
- Single task training (dominant approach): collect proper training data, which does what we want to do, then tests on unknown data.
    - Major shortcomings: captioning models, reading comprehension, image classifiers etc.
    - lack of generalization.
- Multitask training: promising feature for improving general performance.
    - This require many effective training pairs.
- Current best performing model: combination of pre-training and supervised fine-tuning.
- This paper connects them both.
    - Demonstrate language models can perform down-stream tasks in a zero-shot setting – without any parameter or architecture modification.
    - Demonstrates ability of language models to perform a wide range of tasks in a zero-shot setting.

### Approach


### Related Work
- *Jozefowicz et al. (2016)* scaled RNN based language models on the 1 Billion Word Benchmark.
- *Bajgar et al. (2016)* also previously improved
results on the Children’s Book Test by creating a much larger training dataset.
- *Hestness et al. (2017)* conducted
a thorough analysis of how the performance of various deep
learning models changes as a function of both model capacity and dataset size.
- Interesting learned functionality in generative models
has been documented before such as the cells in an
RNN language model performing line-width tracking and
quote/comment detection *Karpathy et al. (2015)*.
- *Liu et al. (2018)* that a model trained to generate Wikipedia articles
also learned to translate names between languages.
- GloVe, *Pennington et al., 2014* scaled word
vector representation learning to all of Common Crawl.
- *McCann et al. (2017)* explored the use of representations derived from
machine translation models.
- *Howard & Ruder (2018)* improved the RNN based fine-tuning approaches.
- *Conneau et al., 2017a* studied the transfer
performance of representations learned by natural language
inference models and *Subramanian et al., 2018* explored
large-scale multitask training.
- *Ramachandran et al., 2016* demonstrated that seq2seq models benefit from being initialized with pre-trained language models as encoders and decoders.
- LM pre-training is helpful when fine-tuned for
difficult generation tasks *Wolf et al., 2019*, *Dinan et al., 2018*.

### Discussion
- The paper's research suggested unsupervised learning tasks are promising area to explore.
- Performance of GPT-2: competitive with supervised baselines in a zero-shot setting.
- Still far from use-able.
- No clear details about finetuning.
- Next steps: investigate fine-tuning on decaNLP and GLUE benchmarks.
- Still not clear if the additional training data and capacity of GPT-2 is sufficient to overcome the inefficiencies.

### Conclusion
- When LLMs are trained on large and diverse datasets it is able to perform well.
- The diversity of tasks the model is able to perform in a zero-shot setting suggests
high-capacity models learn how to perform a surprising amount of tasks without
the need for explicit supervision.
