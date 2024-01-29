# Recurrent Neural Network-based Language Model

> By ***Toma's Mikolov, Martin Karafiat, Luka's Burget, Jan "Honza" Cernock, Sanjeev Khudanpur***

[Research Paper Link](https://www.fit.vutbr.cz/research/groups/speech/publi/2010/mikolov_interspeech2010_IS100722.pdf)

### Abstract
- Paper presents an RNN-based language model with speech recognition application.
- Results show we can obtain around $50%$ reduction of perplexity.
- Speech recognition experiments show around $18%$ reduction in word error rate on the Wall Street Journal tasks and around $5%$ on NIST RT05 tasks.

### Introduction
- Problem: Sequential data prediction
- Goal: To predict the next word in textual data.
- How to better predict the sequential data? This was achieved by the introduction of cache models and class-based models.
- Experiments showed more data results in more accurate results (although recent papers are contradictory).
- Paper experiments RNN for modeling sequential data.

### Model Description
- Previous approaches:
    - Bengio approach: using a feed-forward neural network with fixed length context. The main deficiency is that the neural network can only see a few words before and after.
    - Goodman approach: a mixture of several models.
    - Schwenk approach: improvements in speech recognition model.
- RNNs are not limited to the size of context.
- Input layer ($x$), hidden layer ($s$), output layer ($y$), time ($t$), output ($y(t)$), and state of network ($s(t)$). They are computed as follows:

$$
x(t) = w(t) + s(t - 1)
$$

$$
s_j(t) = f(\sum_{i} x_i(t) u_{ji})
$$

$$
y_k(t) = g(\sum_{j} s_j(t) v_{kj})
$$

$$
f(z) = \frac{1}{1 + e^{-z}}
$$

$$
g(z_m) = e^{z_m} \frac{\sum_k e^{z_k}}{e^{z_k}}
$$

- According to experiments, the hidden layer's size reflects the training data amount.
- All data is sequentially processed.
- The output layer represents the probability distribution of the next word given the previous word and context size.
- Softmax ensures the probability distribution is valid.
- **Dynamic model**
    - Conventionally, we believe that the training and testing phases are two different phases, and the model needs to learn new features during the testing phase. But on the contrary, if the model gets any new words during the testing phase, it starts training on that testing phase.
    - Gets automatically updated to new domains.
- For RNN, only the size of the hidden layer needs to be selected, unlike feed-forward neural networks.

#### Optimization
- Merging all the words that occur less often than a threshold into a special rare token.
- All rare words are treated equally, i.e., probability is uniformly distributed between them.
- Word-probabilities are computed as:

$$
P(w_i(t+1)|w(t), s(t-1)) = \begin{cases}
y_{\text{rare}}(t) \cdot C_{\text{rare}} & \text{if } w_i(t + 1) \text{ is rare}, \\
y_i(t) & \text{otherwise}.
\end{cases}
$$

- $C_{rare}$: number of words in the vocabulary that occur less often than the threshold.

### Conclusion and Future Work
- RNNs outperformed previous models.
- Proved that there are multiple ways (not just n-gram) we can improve the performance of the model.
- RNNs can capture long context information as cache models.
