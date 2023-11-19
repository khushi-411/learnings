# Attention Is All You Need <sup>[link](https://arxiv.org/abs/1706.03762)</sup>

> By Ashish Vaswani, Noam Shazeer, Niki Parmar,
Jakob Uszkoreit, Llion Jones, Aidan N. Gomez, Lukasz Kaiser, Illia Polosukhin

### Abstract
- Best performing model untill now: Encoder + Decoder + Attention mechanism
- Architecture proposed in this paper: Transformer
    - Only attention mechanism; with recurrence and convolutions
- English-to-German translation tasks: 28.4 BLEU on the WMT 2014
- English-to-French translation tasks: 41.8 BLEU on the WMT 2014

### Introduction
- Sequence modeling & transduction problems: RNNs, LSTM, Gated RNNs.
- Recurrent models: Sequential in nature.
    - Sequential nature prevents parallelization within training examples.
    - Therefore, becomes it critical for longer length because of memory.
- Hence, attention models became a integral part.
- This work propose **Transformer**, which relays on parallelization.

### Background
- Goal: reduce sequential computation.
- Earlier models found it difficult to learn dependencies between distant positions (linear or logarithmic distance)
    - In the transformer, reduce the number of operations.
    - Self-attention/Intra-attention: relate different positions of a single sequence to compute a representation of the sequence.
    - Does not use RNNs or convolution.
- Recurrent attention mechanism: end-to-end memory networks.

### Model Architecture
