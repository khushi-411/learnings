# N-gram Language Models

> By ***Daniel Jurafsky, James H. Martin***

[Research Paper Link](https://web.stanford.edu/~jurafsky/slp3/3.pdf)

### Abstract & Introduction
- Assign a probability to each possible next word and sentences.
- Probabilities are important for speech recognition, grammatical error correction, machine translation, augmentative and alternative communication systems.
- Models that assign probabilities to sequences of words are called **Language Models**.
- n-gram: a sequence of n words; therefore, 2-gram is called bigram.

### N-Grams
- Probability of word `w` given some history `h` is given by `P(w|h)`.
- One way to estimate this is from relative frequency counts, i.e., take a large datasets and count the number of times that word occured.
- Better approach than the above method, **chain rule of probability**, given by:

$$
P(X_1 \ldots X_n) = P(X_1)P(X_2|X_1)P(X_3|X_1:X_2) \ldots P(X_n|X_1:X_{n-1})
 = \prod_{k=1}^{n} P(X_k | X_1:X_{k-1})
$$

- Using this does not really seems helps to us, we need to compute the exact probability of next words.
- The intuition of the n-gram model is that instead of computing the probability of
a word given its entire history, we can approximate the history by just the last few
words.
- The intiution of the **bigram** model: approximates the probability of a word given all the previous words.
- Uses conditional probability.
- **Markov Assumption**: The assumption that the probability of a word depends on the previous word.
    - bigram: looks only the previous words.
    - trigram: looks the previous two words.
    - n-gram: looks the previous n-1 words.
- Probabilities are estimated using **Maximum likelihood estimation**.
- Steps:
    1. Add a special symbol at the start and end of the statement.
- **Log Probabilities**: Probabilities in log format. To save from numerical underflow.

### Evaluating Language Models
- **Extrinsic Evaluation** (best way): embed it in an application and measure how much the application improves.
- **Intrinsic Evaluation**: measures the quality of a model independent of any application.
- Training test is used to learn new things in the model and the testing set is used to check the quality of the data on some unseen data.
- **Training on test data**: When an unseen data comes in test data, the model will start traning on that unseen test data.
    - Makes probabilities look high, inaccuracies in perplexity, etc.
- **development set**: To tune the hyper-parameters.
- In practice, the dataset is divided into 80% training, 10% development, and 10% testing.

### Perplexity
- It is the inverse probability of the test set, normalized by the number of words.

$$
\text{{perplexity}}(W) = \left( \prod_{i=1}^{N} \frac{1}{P(w_i | w_1 \ldots w_{i-1})} \right)^{\frac{1}{N}}
$$

- Minimizing perplexity is equivalent to maximizing the test set probability.
- Since a sequence will cross many sentence boundries make sure to include the begin and end sentence makers `<s>` and `</s>`, and also, only end (`</s>`) sentence makers not beginning.
- It is a function of both the text and the language model.
- The more information the n-gram gives us about the word sequence, the higher the probability the n-gram will assign to the string.
- A lower perplexity can tell us that a language model is a better predictor of the words in the test set.

### Sampling sentences from a language model
- **Sampling** from a distribution means to choose random points according to their likelihood.
- To generate sentence choose sentence according to its likelihood as defined by the model. Therefore we are morelikely to generate some sentences that have a high probability and those which have low probability.

### Generalization and Zeros
- Dependent on the training corpus.
- Implications:
    - Probabilities encode specific facts about a given training corpus.
    - n-grams do a better job modeling the training corpus as we increase the value of N.
- General observation: the longer the context on which we train the model, the more coherent the sentences.
- What if the training set and tests sets are of different genre?
    - The model won't have a good result.
    - Therefore, make sure both the training and tests sets are from the same genre.
    - The other problem is: ***sparsity***. There will be many cases of zero probability n-grams.
- The ***zeros*** that don't occur in the training set but do occur in the test set are problem for the two reasons:
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
        - Estimate the probabilities for `<UNK>`, and perform same steps as normal model.
    - The other method is we don't have any such vocabulary, we create it implicitly by replacing words in training data by `<UNK>` based on there frequency.

### Smoothing
- To save models from having zero probability, we shave off a bit of probability mass from some frequent events and give it to the events we've never seen. The following are the ways of smoothing:

#### Laplace smoothing
- It's the simplest way; adding one to all the n-gram counts, before we normalize them into probabilities.
- This algoritm does not perform well enough to be used in modern n-gram models.
- The unigram probability of a word w_i, its count c_i normalized by the total number of word tokens *N*:

$$
P(w_i) = \frac{c_i}{N}
$$

After applying laplace smoothing:

$$
P_{\text{Laplace}}(w_i) = \frac{c_i + 1}{N + V}
$$

- How smoothing algorithm affects the numerator. by defining an adjusted count `c^*`

$$
c^*_i = \frac{c_i + 1}{N + V}
$$

- **Discounting**: Some non-zero counts in order to get the probability mass that will be assigned to the zero counts. Ratio of the discount counts to the original counts is given by:

$$
d_c = \frac{c^*}{c}
$$

#### Add-k smoothing
- This algorithm adds a fractional count *k*.
- How to choose *k*?
   - One way is optimizing devset.

$$
P^*_{\text{Add-k}}(w_n|w_{n-1}) = \frac{C(w_{n-1}w_n) + k}{C(w_{n-1}) + kV}
$$

#### Backoff and Interpolation  
