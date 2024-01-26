# A Neural Probabilistic Language Model

> By ***Yoshua Bengio, Réjean Ducharme, Pascal Vincent, Christian Jauvin***

[Research Paper Link](https://www.jmlr.org/papers/volume3/bengio03a/bengio03a.pdf)

### Abstract
- Goal: LM to learn the joint probability function of sequences of words in a language.
- Challenge: many dimensions.
- Older approaches are n-gram.
- How to solve the problem of dimentionality?
    - A distributed representation for each word along with.
    - The probability function for word sequences, expressed in terms of these representations.
- The paper reports using neural networks for the probability functions and improves the state of art of the n-gram models.

### Introduction
- For continous variables generalization is easy while for discrete spaces, the generalization structure is not obvious. Any changes to this discrete variables may have a drastic impact on the function value to be estimates.
- In high dimensions, it is crucial to distribute probability mass where it matters rather than uniformly in all directions around each training point.
- Represenataion of a statistical model of language:

$$
\hat{P}(w_{T}^{1}) = \prod_{t=1}^{T} \hat{P}(w_{t} | w_{t-1}^{1})
$$

- Places where this can be used speech recognition, language translation, and information retrieval.
- Temporaly closer words in the word sequence are statistically more dependent.
- What happens if a new combination occurs that  is not seen in the training corpus.
    - We do not want to assign zero probability to it because new combinations are likely to occur and they will occur more frequently for larger context size.
    - Solutions are backoff models or smoothing models.
- How is generalization obtained in te new sequence of words?
- Focus of this paper:
    - Not taking into account contexts farther than 1 or 2 words.
    - Not taking into account the similarity between words.
- Contributions of this paper:
    - Implementating the ideas that relies on shared-parameter multi-layer neural networks.
    - Shows training large model is expensive but feasible, and yields good results.
-  Fighting the Curse of Dimensionality with Distributed Representations
    - Associate with each word in the vocabulary a distributed word feature vector.
    - Express the joint probability function of word sequences in terms of the feature vectors of these words in the sequence.
    - Learn simultaneously the word feature vectors and the parameters of that probability function.

### Relation to Previous Work
- The idea of using neural netwrok to high-dimensional discrete distributions model is useful to learn the joint probability.
    - The joint probability is decomposed as a product of conditional probabilities.  
