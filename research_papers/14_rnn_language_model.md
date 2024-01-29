# Recurrent Neural Network based Language Model

> By ***Toma's Mikolov, Martin Karafiat, Luka's Burget, Jan "Honza" Cernock, Sanjeev Khudanpur***

[Research Paper Link](https://www.fit.vutbr.cz/research/groups/speech/publi/2010/mikolov_interspeech2010_IS100722.pdf)

### Abstract
- Paper presents an RNN based language model with speech recognition application.
- Results show we can obtain around $50%$ reduction of perplexity.
- Speech recognition experiments show around $18%$ reduction of word error rate on the Wall Street Journel tasks and around $5%$ on NIST RT05 tasks.

### Introduction
- Problem: Sequential data prediction
- Goal: To predict the next word in textual data.
- How to better predict the sequential data? Achieved by the introduction of cache models and class-based models.
- Experiments showed more data results in more accurate results (although recent papers are contradictoary).
- Paper experiments RNN for modeling sequential data.

### Model Description
- Previous approaches:
    - Bengio approach: using feed-forward neural network with fixed length context. Main deficiency is that neural network can only see few words before and after.
    - Goodman approach: mixture of several models.
    - Schwenk approach: improvements in speech recognition model.
- RNN's are not limited to size of context.
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

- According to experiments size of hidden layer reflect the amount of training data.
- All data is sequentially processed.
- Output layer represents probability distribution of next word given previous word and context size.
- Softmax ensures the probability distribution is valid.
- **Dynamic model**
    - Conventionally, we believe that the training and testing phase are two different phases and model does not learn any newfeatures during testing phase. But on the contray, if the model gets any new words during testing phase it starts training on that testing phase.
    - Gets automatically updated to new domains.
- For RNN's only size of hidden layer needs to be selected unlike feed-forward neural network.

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
- RNNs outperformed than previous models.
- Proved that their are multiple ways (not just n-gram) we can improve the perforance of the model.
- RNNs can capture long context information as cache models.
