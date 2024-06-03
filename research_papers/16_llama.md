# LLaMA: Open and Efficient Foundation Language Models

> By ***Hugo Touvron, Thibaut Lavril, Gautier Izacard, Xavier Martinet,
Marie-Anne Lachaux, Timothee Lacroix, Baptiste Rozière, Naman Goyal,
Eric Hambro, Faisal Azhar, Aurelien Rodriguez, Armand Joulin,
Edouard Grave, Guillaume Lample***

[Research Paper Link](https://arxiv.org/abs/2302.13971)

### Abstract
- LLaMA: collection of foundation language models ranging from 7b to 65B parameters.
- Trained in trillions of tokens.
- Shows it is possible to train state-of-the-art models using publicaly available datasets.
- LLaMA-13B outperforms GPT-3 (1757B) despite being 10x times smaller.
- LLaMA-65B competitive with Chinchilla-70B and PaLM-540B.

### Introduction
- LLMs trained on large datasets have the ability to perform new tasks on their own.
- Few results show some models perform better on smaller models than the larger models.
- Objective of the scaling laws: to determine how to best scale the dataset and model sizes for a particular training compute budget.
    - This degrads the scaling budget.
- Focus: To train a series of language models that achieve the best possible performance at various inference budgets, by training on more tokens than what is used. The resulting model is called LLaMA.

### Approach

#### Pre-training Data
- **English CommonCrawl [67%]**: Perfomed deduplication, language identification with a fastText linear classifier to remove non-English pages and filters low quality content with an n-gram model.
- **C4 [15%]**: Pre-processing includes deduplication and language identification steps.
- **GitHub [4.5%]**: Filered low-quality files, removed boilerplate such as headers, with regular expressions.
- **Wikipedia [4.5%]**: Wiki dump covers 20 languages. Removed hyperlinks, comments, and other formatting boilerplate.
- **Gutenberg and Books3 [4.5%]**: To include book data.
- **ArXiv [2.5%]**: To add scientific data to the dataset. Removed everything before first section, comments, inline-expanded definitions and macros written by users.
- **Stack Exchange [2%]**: For high quality questions and answers that covers diverse set of domains. Kept the data from the HTML tags from text and sorted the ansers by score.
- **Tokenizer**: Tokenize data with the byte-pair encoding algorithm. Dataset contains 1.4T tokens after tokenization.

#### Architecture
The network presented on this paper is based on the transformer achitecture. The main differences from the original architecture are:
- **Pre-normalization [GPT3]**: To improve the training stability, they normalized the input of each transformer sub-layer, instead of normalizing the output. They used ***RMSNorm*** normalizing function.
- **SwiGLU activation function [PaLM]**: Replace the ReLU non-linearity by the SwiGLU activation function.
- **Rotary Embeddings [GPTNeo]**: Removed the absolute positional embeddings and add rotary positional embeddings (RoPE).

#### Optimizer
- Trained using AdamW optimizer.
- Hyper-parameters: β1 = 0.9, β2 = 0.95
- Cosine learning rate; weight decay = 0.1; gradiend clipping: 1.0.

#### Efficient Implementation
To improve the training speed of the network:
- Use an efficient implementation of the multi-head attention to reduce memory usage and runtime.
- Reduce the amount of activations that are recomputed during the backward pass with checkpointing.
- To reduce the memory usage of the model they used model and sequence parallelism.

### Main Results
- **Zero-shot**: The model provides an answer using open-ended generation, or ranks the proposed answer.
- **Few-shot**: The model takes the tasks as input and generates the answer or ranks different options.
- Also, compared LLaMA with other non-publically available datasets.
- Evaluated LLaMA on free-form generation tasks and multiple choice tasks.
- Performed zero-shot training in common sense reasoning benchmarks.
- Also, compared LLaMA on closed-book question answering benchmarks.
- Evaluate on the RACE reading comprehension benchmarks.
- Evaluated the models on two mathematical reasoning benchmarks: maths and GSM8k.
- Evaluated on natural language description on HumanEval and MBPP benchmarks.
- Also, evaluated on massive multitask language understanding, which consists of multiple choice questions on various domains.

### Instruction Finetuning
- Very small amount of finetuning improves the performance of MMLU and further improves the ability of the model.

###  Bias, Toxicity and Misinformation
