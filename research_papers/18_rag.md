# Retrieval-Augmented Generation for Knowledge-Intensive NLP Tasks

> ***Patrick Lewis, Ethan Perez, Aleksandra Piktus, Fabio Petroni,
Vladimir Karpukhin, Naman Goyal, Heinrich Küttler, Mike Lewis,
Wen-tau Yih, Tim Rocktäschel, Sebastian Riedel, Douwe Kiela***

[Research Paper Link](https://arxiv.org/abs/2005.11401)

### Abstract
- Main limitations of LLMs are to access and manipulate knowledge; hence, performance lags behind.
- Method discussed in the paper: general purpose for fine-tuning recipe for retrieval-augmented generation (RAG).
- RAG: combine pre-trained parametric and non-parametric memory for language generation.
- In RAG models: parametric memory is a pre-trained seq2seq model and the non-parametric memory is a dense
vector index of Wikipedia, accessed with a pre-trained neural retriever.
- Compared two rags models: one on the same retrived passages accross the generated sequence, and another with different passages per token.
- Then they fine tuned and evaluated their models on three domain QA tasks, parametric seq2seq models and task-specific retrieve-and extract architecture.
- RAG models gave better results.

### Introduction
- 
