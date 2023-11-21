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
- In encoder-decoder attention:
    - queries come from the previous decoder layer.
    - memory keys an values come from the output of the encoder.
 ![types of attention](images/attention.png)

1. **Scaled Dot-Product Attention**
- Inputs: queires, keys (*K*) of dimension (d_k), values (*V*) of dimension (d_v), matrix (*Q*).
- Scaling factor here is $\sqrt{\frac{1}{d_k}}$
- Two types of attention used:
    - Additive attention: computes the compatibility function using a feed-forward network with a single hidden layer.
    - Dot-product attention: faster and space-efficient practice.

$$
\text{Attention}(Q, K, V) = \text{softmax}\left(\frac{QK^T}{\sqrt{d_k}}\right) V
$$

2. **Multi-Head Attention**
- Attention in parallel, i.e., performs different representation subspaces at different positions.

$$
\text{MultiHead}(Q, K, V) = \text{Concat}(\text{head}_1, \ldots, \text{head}_h) \cdot W^O
$$

where

$$
\text{head}_i = \text{Attention}(QW_{Qi}, KW_{Ki}, V W_{Vi})
$$

3. **Applications of Attention in our Model**
- Every position in decoder attend all position of input sequence (mimics a typical encoder-decoder mechanisms).
- Each position in the encoder can attend to all position in the previous layer of the encoder.
    - Because encoder contains self-attention layers (keys, values, and queries comes from the same place).
- Similarly, self-attention layers in decoder allow each position in the decoder to attend to all the positions in decoder.
    - To prevent leftward information flow: implement masking all values in input of the softmax.

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
- Multiply embedding layers by \( \sqrt{d_{\text{model}}} \).

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
- Compare aspects of self-attention layers to recurrent and convolution layers.
- Why self-attention use?
    - Total computational complexity per layer.
    - Amount of computation that can be parallelized.
    - Path length between long-range dependencies in the network.
        - Learning long range dependencies is a key challenge affecting the ability to learn forward and backward passes. Shorter paths are easier to learn.
- Self-attention layer connects all position with a constant number of seqentially executed operations whereas recurrent layers requires O(n) operations. Self-attention are faster when the sequence lengths are smaller.
    - To improve the performance of larger sequence lenghts self-attention layers should just consider its neighbouring positions.
- Convolutional layers are even more expensive than the recurrent layers.
- Self-attention layer are more easier to interpret that the other two.

### Training
1. **Training Data and Batching**
    - WMT 2014 English-German dataset: 4.5 million sentences pairs. Sentence were encoded using byte-pair encoding.
    - WMT 2014 English-French dataset: 36 million sentences, 32000 word-piece vocabulary.
2. **Hardware and Schedule**
    - Trained on 8 NVIDIA P100 GPUs. 100,000 steps or 12 hours.
3. **Optimizer**: Adam Optimizer.
    - Hyperparameters are

$$
\beta_1 = 0.9, \beta_2 = 0.98, \epsilon = 10^{-9}, \text{ and } \text{warmup\_steps} = 4000.
$$

    - Variable learning rate is given by:

$$
\text{lrate} = d^{-0.5} \cdot \min(\text{step\_num}^{-0.5}, \text{step\_num} \cdot \text{warmup\_steps}^{-1.5})
$$

4. **Regularization**
    - Residual Dropout: Applied to the output of each sub-layer. And to the sum of the embeddngs and positional embeddings in both encoder and decoder stacks. Rate used 0.1.
    - Label Smoothing: Added value

$$
\epsilon_{\text{ls}} = 0.1
$$


### Results
1. **Machine Translation**
    - WMT 2014 English-to-German translation task: 28.4 BLEU score.
    - WMT 2014 English-to-French translation task: 41.0 BLEU score. Took 1/4 the training cost of previous model.
    - FLOPS used to train a model by multiplying the training time, no. of GPUs used, and an estimated GPU capacity.
2. **Model Variations**
    - To evaluate the importance of different components of the Transformer, they varied our base model in different ways.
    - Quality drops with too low and too many attention heads.
    - Reducing attention key size hurts model quality.
    - Dropout is very helpful in avoiding over-fitting.
    - After replacing the sinusoidal positional encoding with learned positional embeddings, they get nearly identical results to base model.
3. **English Constituency Parsing**
    - To evaluate if the transformer can generalize to other tasks.
    - Resutls showed that despite of lack of task specfic tuning the model performed well.

### Conclusion
- Introduced **Transformer**, based entirely on attention mechanism, no RNNs and no convolutions.
