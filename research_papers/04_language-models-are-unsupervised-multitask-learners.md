# Language Models are Unsupervised Multitask Learners

> By ***Alec Radford, Jeffrey Wu, Rewon Child, David Luan,
Dario Amodei, Ilya Sutskever***

[Research Paper Link](https://cdn.openai.com/better-language-models/language_models_are_unsupervised_multitask_learners.pdf)

### Abstract
- Demonstrate that the language model begins learning the tasks without explicit supervision.
- GPT-2: $1.5$ billion parameter transformer ($7/8$ points), which underfits WebText.
- WebText: New datasets of millions of webpages.

### Introduction
- Supervised learning models: brittle and sensitive to data distribution and task specification changes.
- Need a general system that can perform multiple tasks without the need for data training.
- Single task training (dominant approach): collect proper training data, which does what we want to do, then tests on unknown data.
    - Major shortcomings: captioning models, reading comprehension, image classifiers, etc.
    - lack of generalization.
- Multitask training: promising feature for improving general performance.
    - This requires many effective training pairs.
- Current best-performing model: a combination of pre-training and supervised fine-tuning.
- This paper connects them both.
    - Demonstrate language models can perform downstream tasks in a zero-shot setting, i.e., without any parameter or architecture modification.
    - Demonstrates the ability of language models to perform a wide range of tasks in a zero-shot setting.

### Approach
- Set of examples (sequence of variable length): $(x_1, x_2, ..., x_n)$.
- Symbols: $(s_1, s_2, ..., s_n)$.
- Joint probability: product of conditional probabilities.

$$
p(x) = \prod_{i=1}^{n} p(s_i | s_1, \ldots, s_{i-1})
$$

- Learning to perform a specific task is given by $p\(output|input\)$
- For a general system performing many tasks, it is given by $p\(output|input, task\)$
- Language model learns without the need for any explicit supervision.
- Experiments confirmed that large language models can perform multitask learning but are slower than the supervised approaches.
- LLMs with sufficient capacity will begin to learn to infer and perform the tasks demonstrated in natural language sequence to predict them.
    - implies it can perform unsupervised multitask learning.

#### Training Dataset
- Approach large and diverse datasets.
- Dataset created: web scrape.
    - These datasets are filtered by humans, like Reddit, a social media platform.
- The resulting dataset, WebText, contains $40$ million links.
    - The text was extracted from these links using Dragnet and newspaper content extractors.
- Then, clean and apply the de-duplication technique.
- Removed all Wikipedia documents from WebText, since it's a common data source for other data sources.

#### Input Representation
- LM model should be able to compute the probability of any string.
- Pre-processing steps: lower-casing, tokenization, and out-of-vocabulary tokens.
- Byte Pair Encoding (BPE): a middle ground between character and word level language modeling.
    - It operates on Unicode code points and not byte sequences.
    - Using this results in sub-optimal merges since it uses greedy frequency for building a vocabulary.
- Add an exception for space in BPE to avoid merging across characters, like dog, dog!, dog? etc.
- This approach allows to generate the probability of any string.

#### Model
- Architecture: Transformer.
- Few modifications to the GPT model:
    - Layer normalization was moved to the input of each sub-block.
    - Additional layer normalization was added after the final self-attention block.
    - Initialization was modified with model depth.
    - Scale the weights of residual layers at initialization by a factor of 1/ $\sqrt{N}$.
    - Vocabulary size = $50,257$.
    - Context size increased from $512$ to $1024$.
    - Batch size = $512$.

### Experiments

<div align="center">

|  Name  |  Parameters  |  Layers  |  dmodel  |
|:--------:|:--------------:|:----------:|:----------:|
| Equi. Original GPT | $117$ M       | $12$     | $768$    |
| Largest BERT model | $345$ M       | $24$     | $1024$   |
|        | $762$ M       | $36$     | $1280$   |
| GPT-2  | $1542$ M      | $48$     | $1600$   |

</div>

1. **Language Model**
    - Our model does not require any pre-processing or tokenization steps; therefore, we can evaluate it in any language model.
    - To test how WebText LM performs on zero-shot training. Score $7/8$.
    - Large improvements are noticed on small datasets (Penn Treebank & WikiText-2), and datasets are created to measure long-term dependencies.
    - Bad performance: very large datasets.
2. **Children's Book Test**
    - To check the performance of different categories of words: named entities, nouns, verbs, and prepositions.
    - Performance improves as the model size increases.
    - GPT-2 achieves $93.3%$ on common nouns and $89.1%$ on named entities.
3. **LAMBADA**
    - To test the long-range dependencies in the text. For example, to complete the incomplete statements by humman.
    - Prediction: showed valid continuations of the sentence but are not valid final words.
    - The above prediction shows LMs are not using the additional useful constraint that the word must be the final of the sentence.
    - Therefore, they added a stopword filter, which increased their accuracy.
4. **Winograd Schema Challenge**
    - To measure the system's capability to perform commonsense reasoning by measuring its ability to resolve ambiguities in text.
    - Here, they used same method as *Trinh & Le (2018)*.
    - Accuracy improvement from $7%$ to $70.70%$.
5. **Reading Comprehension**
    - Used  Conversation Question Answering dataset (CoQA).
    - GPT-2 achieved exciting performance without any supervised training.
    - Greedy decoding.
6. **Summarization**
    - Dataset to test: CNN and Dialy Mail dataset.
    - Result: Usually focus on recent data and get confused about specific details.
7. **Translation**
    - To test how to translate from one language to another language.
    - Used greedy decoding and use the first generated sentence as a translation.
    - On the WMT-14 English-French test set, worse performance than word-by-word substitution with a bilingual lexicon. $5$ BLEU score.
    - On the WMT-14 French-English test set, GPT-2 is better, with $11.5$ BLEU score.
    - Still worse than the current best unsupervised machine translation approach ($33.5$ BLEU score).
8. **Question Answering**
    - Used Natural Questions dataset.
    - GPT-2 answers $4.1%$ of questions correctly for datasets like SQUAD.
    - The performance of GPT-2 is still much, much worse than the $30$ to $50%$ range of open domain question answering systems.

### Generalization vs Memorization
- Overlap in training and testing datasets results in an over-reporting of generalization performance. This increases with the increase in the datasets. Therefore, it is important to analyze how much data is repeated in testing data.
- To study this, they created Bloom filters.
    - To improve recall, strings are normalized to lower-case.
    - False positive is upper bounded by $1/10^8$.
    - Help us calculate the percentage of 8-grams from the dataset that can also be found in the Webtext training set.
    - Found that common LM dataset has $1-6%$ overlap, Webtext has $3.2%$ overlap, and many others have an average of $5.9%$ overlap.
    - For CoQA, about $15%$ of documents in the news domain are already in WebText, and the model performs about $3$ F1 better on these.
        - Gain was measured between $0.1-1.0$ F1 due to overlap.
    - LAMBADA has an average overlap of $1.2%$.
        - GPT-2 performs better in our experiment.
- Overall analysis, overlap between WebText and other eval datasets provides efficiency.
- How do we understand how similar text datasets impact performance?
    - De-duplication techniques like scalable fuzzy matching.
    - Recommendation: use n-gram overlap based on de-duplication as a verification check.
- Is performance an attribute of memorization?
    - Performance increased as the model size increased, but GPT-2 is underfitted on the Webtext dataset.

### Related Work
- *Jozefowicz et al. (2016)* scaled RNN-based language models on the $1$ Billion Word Benchmark.
- *Bajgar et al. (2016)* also previously improved
results on the Children's Book Test by creating a much larger training dataset.
- *Hestness et al. (2017)* conducted
a thorough analysis of how the performance of various deep
learning models change as a function of both model capacity and dataset size.
- Interesting, learned functionality in generative models
has been documented before, such as the cells in an
RNN language model performing line-width tracking and
quote/comment detection *Karpathy et al. (2015)*.
- *Liu et al. (2018)* that a model trained to generate Wikipedia articles
also learned to translate names between languages.
- GloVe, *Pennington et al., 2014* scaled word
vector representation learning to all of Common Crawl.
- *McCann et al. (2017)* explored the use of representations derived from
machine translation models.
- *Howard & Ruder (2018)* improved the RNN based fine-tuning approaches.
- *Conneau et al., 2017a* studied the transfer
performance of representations learned by natural language
inference models and *Subramanian et al., 2018* explored
large-scale multitask training.
- *Ramachandran et al., 2016* demonstrated that seq2seq models benefit from being initialized with pre-trained language models as encoders and decoders.
- LM pre-training is helpful when fine-tuned for
difficult generation tasks *Wolf et al., 2019*, *Dinan et al., 2018*.

### Discussion
- The paper's research suggested unsupervised learning tasks are promising areas to explore.
- Performance of GPT-2: competitive with supervised baselines in a zero-shot setting.
- Still far from usable.
- No clear details about finetuning.
- Next steps: investigate fine-tuning on decaNLP and GLUE benchmarks.
- Still not clear if the additional training data and capacity of GPT-2 is sufficient to overcome the inefficiencies.

### Conclusion
- When LLMs are trained on large and diverse datasets, they are able to perform well.
- The diversity of tasks the model is able to perform in a zero-shot setting suggests
high-capacity models learn how to perform a surprising amount of tasks without
the need for explicit supervision.
