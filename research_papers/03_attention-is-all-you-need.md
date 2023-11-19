# Attention Is All You Need <sup>[link](https://arxiv.org/abs/1706.03762)</sup>

> By Ashish Vaswani, Noam Shazeer, Niki Parmar,
Jakob Uszkoreit, Llion Jones, Aidan N. Gomez, Lukasz Kaiser, Illia Polosukhin

### Abstract
- Best performing model until now: Encoder + Decoder + Attention mechanism
- Architecture proposed in this paper: Transformer
    - Only attention mechanism; with recurrence and convolutions
- English-to-German translation tasks: 28.4 BLEU on the WMT 2014
- English-to-French translation tasks: 41.8 BLEU on the WMT 2014

### Introduction
- Sequence modeling & transduction problems: RNNs, LSTM, Gated RNNs.
- Recurrent models: Sequential in nature.
    - Sequential nature prevents parallelization within training examples.
    - Therefore, becomes it critical for longer lengths because of memory.
- Hence, attention models became an integral part.
- This work propose **Transformer**, which relays on parallelization.

### Background
- Goal: reduce sequential computation.
- Earlier models found it difficult to learn dependencies between distant positions (linear or logarithmic distance)
    - In the transformer, reduce the number of operations.
    - Self-attention/Intra-attention: relate different positions of a single sequence to compute a representation of the sequence.
    - Does not use RNNs or convolution.
- Recurrent attention mechanism: end-to-end memory networks.

### Model Architecture
- Stacked self-attention and point-wise, and fully connected layers for both encoder and decoder.

 ![transformer architecture](images/transformer.png)

#### Encoder and Decoder Stacks
1. **ENCODER**
    - Stack of N = 6 identical layers. Each has 2 sub-layers (multi-head self-attention layers and feed-forward network).
    - After each sub layer they applied layer normalization.
    - All sub layers of model and embedding layers produce output dimension as 512.
2. **DECODER**
    - Stack of N = 6 identical layers. Each has 2 sub-layers as above, adds another sub-layer which performs multi-head attention over the output of encoder sack.
    - Same as encoder, adds a layer normalization operation.
    - To ensure prediction for position *i*, t depend on output of position less than *i*, apply masking.

#### Attention
- Mapping a query and a set of key-value pairs to an output.
- Total output = weighted sum of the values.
- Weight assigned is computed by a compatibility function of the query with their key.

 ![types of attention](images/attention.png)

1. **Scaled Dot-Product Attention**
- 
    $$
    \text{Attention}(Q, K, V) = \text{softmax}\left(\frac{QK^T}{\sqrt{d_k}}\right) V
    $$
2. ** Multi-Head Attention**

3. **Applications of Attention in our Mode**
- 

#### Position-wise Feed-Forward Networks
- Each encoder and decoder layer contains fully connected feed-forward network.
- Two linear transformation with a ReLU activation.

$$
\text{FFN}(x) = \max(0, xW_1 + b_1)W_2 + b_2
$$

#### Embeddings and Softmax
- Learned embeddings to convert the input tokens and output tokens to vector of dimension d<sub>model</sub>.
- To convert decoder output to predicted next-token probabilities: learned linear transformation and softmax function.
- Same weight matrix between two embedding layers and pre-softmax transformation.
- Multiply embedding layers by $$\sqrt{d<sub>{\text{model}}</sub>}$$

#### Positional Encoding
- Model contains no recurrence and no convolution.
- To add information about relative or absolute positin of tokens: add positional encoding.
- Added in the end of encoder and decoder stacks.
- Why sinusodal function used? Allows model to extend longer than the encountered sequence lenghts during training.

$$
P E(\text{pos}, 2i) = \sin\left(\frac{\text{pos}}{10000^{2i/d_{\text{model}}}}\right)
$$

$$
P E(\text{pos}, 2i+1) = \cos\left(\frac{\text{pos}}{10000^{(2i+1)/d_{\text{model}}}}\right)
$$

### Why Self-Attention
