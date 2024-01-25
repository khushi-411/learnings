# N-gram Language Models

> By ***Daniel Jurafsky, James H. Martin***

[Research Paper Link](https://web.stanford.edu/~jurafsky/slp3/3.pdf)

### Abstract & Introduction
- Assign a probability to each possible next word and sentence.
- Probabilities are important for speech recognition, grammatical error correction, machine translation, and augmentative and alternative communication systems.
- Models that assign probabilities to sequences of words are called **Language Models**.
- n-gram: a sequence of n words; therefore, 2-gram is called bigram.

### N-Grams
- Probability of word `w` given some history `h` is given by `P(w|h)`.
- One way to estimate this is from relative frequency counts, i.e., take a large dataset and count the number of times that word occurred.
- Better approach than the above method, **chain rule of probability**, given by:

$$
P(X_1 \ldots X_n) = P(X_1)P(X_2|X_1)P(X_3|X_1:X_2) \ldots P(X_n|X_1:X_{n-1})
 = \prod_{k=1}^{n} P(X_k | X_1:X_{k-1})
$$

- Using this does not really seem helps to us; we need to compute the exact probability of the next words.
- The intuition of the n-gram model is that instead of computing the probability of
a word given its entire history, we can approximate the history by just the last few
words.
- The intuition of the **bigram** model approximates the probability of a word given all the previous words.
- Uses conditional probability.
- **Markov Assumption**: The assumption that the probability of a word depends on the previous word.
    - bigram: looks only at the previous words.
    - trigram: looks at the previous two words.
    - n-gram: looks at the previous n-1 words.
- Probabilities are estimated using **Maximum likelihood estimation**.
- Steps:
    1. Add a special symbol at the start and end of the statement.
- **Log Probabilities**: Probabilities in log format. To save from numerical underflow.

### Evaluating Language Models
- **Extrinsic Evaluation** (best way): embed it in an application and measure how much the application improves.
- **Intrinsic Evaluation**: measures the quality of a model-independent of any application.
- The training test is used to learn new things in the model, and the testing set is used to check the quality of some unseen data.
- **Training on test data**: When unseen data comes in test data, the model will start training on that unseen test data.
    - Makes probabilities look high, inaccuracies in perplexity, etc.
- **development set**: To tune the hyper-parameters.
- In practice, the dataset is divided into 80% training, 10% development, and 10% testing.

### Perplexity
- It is the inverse probability of the test set, normalized by the number of words.

$$
\text{{perplexity}}(W) = \left( \prod_{i=1}^{N} \frac{1}{P(w_i | w_1 \ldots w_{i-1})} \right)^{\frac{1}{N}}
$$

- Minimizing perplexity is equivalent to maximizing the test set probability.
- Since a sequence will cross many sentence boundaries, make sure to include the beginning and end sentence makers `<s>` and `</s>`, and also, only end (`</s>`) sentence makers not beginning.
- It is a function of both the text and the language model.
- The more information the n-gram gives us about the word sequence, the higher the probability the n-gram will assign to the string.
- A lower perplexity can tell us that a language model better predicts the words in the test set.

### Sampling sentences from a language model
- **Sampling** from a distribution means to choose random points according to their likelihood.
- To generate a sentence, choose a sentence according to its likelihood as defined by the model. Therefore, we are more likely to generate some sentences that have a high probability and those that have a low probability.

### Generalization and Zeros
- Dependent on the training corpus.
- Implications:
    - Probabilities encode specific facts about a given training corpus.
    - n-grams do a better job modeling the training corpus as we increase the value of N.
- General observation: the longer the context on which we train the model, the more coherent the sentences.
- What if the training set and test sets are of different genres?
    - The model won't have a good result.
    - Therefore, make sure both the training and test sets are from the same genre.
    - The other problem is: ***sparsity***. There will be many cases of zero probability n-grams.
- The ***zeros*** that don't occur in the training set but do occur in the test set are a problem for two reasons:
    - there presence means we are undereslimating the probability of all sorts of words that might occur, this will have performance effects.
    - If the probability of any word in the test test is 0, the entire probability of the test set is 0.
    - We can't calculate perplexity, because we can't divide by 0.
- **How to deal will zeros?**
    - Smoothing or discounting.
    - Unknown words.
- **Unknown words**: words that you have never seen before.
    - ***closed vocabulary***: disallow the situation from occurring, and tell the system that we know all the words that can occur.
    - ***out of vocabulary***: If any such words occur, we can call unknown words and create an open vocabulary system, and add these words in a test set by adding a pseudo-word called `<UNK>`. Ways to train it:
        - Choose a vocabulary (word list) that is fixed in advance.
	- Convert in the training set any word that is not in this set to the unknown word token `<UNK>` in a test normalization step.
        - Estimate the probabilities for `<UNK>`, and perform the same steps as the normal model.
    - The other method is we don't have any such vocabulary; we create it implicitly by replacing words in training data with `<UNK>` based on their frequency.

### Smoothing
- To save models from having zero probability, we shave off a bit of probability mass from some frequent events and give it to the events we've never seen. The following are the ways of smoothing:

#### Laplace smoothing
- It's the simplest way: adding one to all the n-gram counts before we normalize them into probabilities.
- This algorithm does not perform well enough to be used in modern n-gram models.
- The unigram probability of a word w_i, its count c_i normalized by the total number of word tokens *N*:

$$
P(w_i) = \frac{c_i}{N}
$$

After applying laplace smoothing:

$$
P_{\text{Laplace}}(w_i) = \frac{c_i + 1}{N + V}
$$

- How smoothing algorithm affect the numerator? by defining an adjusted count $c^\ast$

$$
c^*_i = \frac{c_i + 1}{N + V}
$$

- **Discounting**: Some non-zero counts in order to get the probability mass that will be assigned to the zero counts. The ratio of the discount counts to the original counts is given by:

$$
d_c = \frac{c^*}{c}
$$

#### Add-k smoothing
- This algorithm adds a fractional count *k*.
- How to choose *k*?
   - One way is optimizing the dev set.

$$
P^\ast_{\text{Add-k}}(w_n|w_{n-1}) = \frac{C(w_{n-1}w_n) + k}{C(w_{n-1}) + kV}
$$

#### Backoff and Interpolation
- Two ways to use n-gram hierarchy:
    - **backoff**: we only "back off" to a lower-order n-gram if we have zero evidence for a higher-order n-gram, i.e., first, we use trigram; if it doesn't work, we try bigram, then unigram.
    - **interpolation**: Mixing the probability estimates from all the n-gram estimators, weighting and combining the trigram, bigram, and unigram counts. Linear interpolation is given by, here, for example, for trigram (here, the sum of $\lambda_1, \lambda_2, \lambda_3$ is 1.

$$
\hat{P}(w_n|w_{n-2}w_{n-1}) = \lambda_1 P(w_n) + \lambda_2 P(w_n|w_{n-1}) + \lambda_3 P(w_n|w_{n-2}w_{n-1})
$$

- How are these $\lambda$ values set?
    - Learned from a held-out corpus.
    - Held-out corpus is an additional training corpus that we use to set hyperparameters.
    - We choose the value of $\lambda$ that maximizes the likelihood of the held-out corpus.
    - Ways to set $\lambda$:
        - fix the n-gram probability and then search for $\lambda$ values.
        - Use EM algorithm, an iterative ML algorithm that converges to locally optimal $\lambda$.
- To give the backoff model correct probability distribution, we have to **discount** the higher-order n-grams to save some probability mass for the lower-order n-grams.
- **Katz backoff**: We rely on discounted probability if we’ve seen this n-gram before (i.e. if we have non-zero counts). Otherwise, we recursively back off to the Katz probability for the shorter-history (n-1)-gram.
    - It is often combined with the smoothing method called **Good-Turning**.

### Huge Language Models and Stupid Backoff
- How to shrink the n-gram model?
    - Pruning: for example, only storing n-grams with counts greater than some threshold or using entropy to prune less important n-grams.
    - Using bloom filters
- **Stupid backoff**: Trying to make a language model a true probability distribution. There's no discounting of the higher-order probabilities.


### Advanced: Kneser-Ney Smoothing
- Advance smoothing method.
- **Absolute discounting**: For example, we have an n-gram model with n=4; we'll look at a held-out corpus and see what the count is for all those bigrams that had count 4 in the training set. We then subtract an absolute value from the count in the training set.
    - Absolute discounting formalizes this intuition by subtracting a fixed (absolute) discount d from each count. Here, $0 \leq d \leq 1$

$$
P_{\text{AbsoluteDiscounting}}(w_i|w_{i-1}) = \frac{C(w_{i-1}w_i) - d}{\sum_{v} C(w_{i-1} v) + \lambda(w_{i-1})} P(w_i)
$$

#### Kneser-Ney Discounting
- Presents a more sophisticated way to handle lower-order unigram distribution.
- It predicts how likely the word will appear as a novel continuation.
- It is given by:

$$
P_{\text{CONTINUATION}}(w) = \frac{| \{ v : C(vw) > 0 \} |}{| \{ (u_0, w_0) : C(u_0w_0) > 0 \} |}
$$

- **Interpolated Kneser-Ney smoothing** for bigrams:

$$
P_{\text{KN}}(w_i|w_{i-1}) = \max \left( \frac{C(w_{i-1}w_i) - d}{C(w_{i-1}) + \lambda(w_{i-1})} P_{\text{CONTINUATION}}(w_i), 0 \right)
$$

Here, $\lambda$ is the normalizing constant given by:

$$
\lambda(w_{i-1}) = \frac{d}{\frac{\sum_{v} C(w_{i-1}v)}{|\{w : C(w_{i-1}w) > 0\}|}}
$$

- Here, $C_{KN}$ depends on whether we count the highest-order n-gram being interpolated or one of the lower-order n-grams.
- **Modifie Kneser-Ney smoothing**: rather than using a single fixed discount *d*, this algorithm uses three different discount $d_1$, $d_2$, and $d_3$.

### Advanced: Perplexity’s Relation to Entropy
(TBD)

### Summary
- We studied how language models predict the next words from preceding words.
- Studied Markov model.
- We can evaluate the model both extrinsically and intrinsically.
- The perplexity of a test set according to a language model is the geometric mean of the inverse test set probability computed by the model.
- We studied the smoothing algorithm. And commonly used smoothing algorithms (backoff and interpolation).
- They require discounting to create a probability distribution.
- We discussed the Kneser-Ney smoothing algorithm.
