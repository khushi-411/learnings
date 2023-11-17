## FinGPT: Large Generative Models for a Small Language <sup>[Link](https://arxiv.org/pdf/2311.05640.pdf)</sup>

> By ***Risto Luukkonen, Ville Komulainen, Jouni Luoma, Anni Eskelinen,
Jenna Kanerva, Hanna-Mari Kupari, Filip Ginter, Veronika Laippala,
Niklas Muennighoff, Aleksandra Piktus, Thomas Wang, Nouamane Tazi,
Teven Le Scao, Thomas Wolf, Osma Suominen, Samuli Sairanen,
Mikko Merioksa, Jyrki Heinonen, Aija Vahtola, Samuel Antao, Sampo Pyysalo***

### Abstract
- Study of challenges of creating LLMs for the Finnish language (spoken by less than 1% of people).
- Train seven monolingual models from scratch.
- **BLUUMI**: Pre-train the multilingual BLOOM model (176-billion parameter) on original training data and Finnish.
- **Eval Model**: Fin-bench.
- Also, assess model qualities like toxicity and bias.

### Introduction
- Transformer architecture tasks: text classification to text generation
- Unsupervised learning: learn to perform tasks by themselves
- Datasets collected from: Wikipedia and Common Crawl
- Train (monolingual Finnish models): 13 billion parameters for 300 billion tokens
- Pre-train: 176 billion parameter

### Model Architecture
- Follows GPT architecture for the number of layers, dimensionality, and number of attention heads
- Pre-training: same approach as BLOOM family, i.e., position embeddings, layer normalization, or any other software implementation.
- Continue pre-training called BLUUMI.

### Data
Details about training data, preprocessing steps, data statistics, and analysis.

1. **Data Sources**
    - *Parsebank*: 6 billion tokens collected from the internet.
    - *mC4*: cleaned version of Common Crawl’s web crawl corpus.
    - *CC-Fi*: manually extracted using Trafilatura to maximize coverage of Finnish text.
    - *Fiwiki*: wikipedia's free encyclopedia.
    - *Lönnrot*: project digitizing out-of-copyright Finnish and Swedish literature.
    - *Yle*: archives of the national public broadcasting company.
    - *STT*: archives of the Finnish News agency.
    - *ePub*: electronically published books in Finland.
    - *Lehdet*: includes daily, weekly, monthly, and yearly crawls of newspaper internet sites.
    - *Suomi24*: largest social networking site in Finland.
    - *Reddit-Fi*: details in discussion forums.
    - *ROOTS*: used for continued pretraining of the BLOOM model, but not for monolingual Finnish models.
2. **Preprocessing**
    - *Deduplication*: performed approximate Ngram overlap-based deduplication using Onion. Then, trim the duplicate lines from the beginning and end of each document.
    - *Heuristic filtering*: filter out text that are not finnish, e.g., punctuation, digits, alphabets, etc.
    - *N-gram model filtering*: remove text with surface characteristics.
    - *Toxicity filtering*: to remove abusive contents.
    - *Masking personal data*: e.g., mask email addresses, phone numbers, etc.
    - *Tokenization*: followed BLOOM recipe.
3. **Register Analysis**
    - In the end, apply register identification model.
    - It presents text in different categories as narrative, interactive discussion and lyrical.

### Pretraining
- For monolingual model: trained from scratch.
- BLUMMI model: pretraining.
- **Pretraining hyperparameters**
    | Batch Size | Model Samples | Tokens  | Learning Rate   |
    |------------|---------------|---------|------------------|
    | Small      | 256           | 524288  | 6.0 × 10^(-4)   |
    | Medium     | 256           | 524288  | 3.0 × 10^(-4)   |
    | Large      | 256           | 524288  | 2.5 × 10^(-4)   |
    | XL         | 512           | 1048576 | 2.0 × 10^(-4)   |
    | 3B         | 512           | 1048576 | 1.6 × 10^(-4)   |
    | 8B         | 1024          | 2097152 | 1.2 × 10^(-4)   |
    | 13B        | 1024          | 2097152 | 1.0 × 10^(-4)   |
    | BLUUMI     | 2048          | 4194304 | 6.0 × 10^(-5)   |

### Evaluation
Present evaluation dataset and compare the capability of the models using data.

1. **FIN-bench dataset**
    - Contains data of the following tasks: Analogy, Arithmetic, Cause and effect, Emotions, Empirical judgments, General knowledge, Intent recognition, Misconceptions, Paraphrase, Sentence ambiguity, and Similarities abstraction.
2. **Few-shot results**
    -
3. **Alignment**
    - Model alignment categories: harmlessness, honesty, helpfulness, and other.
4. **Bias**
    -
5. **Toxicity**
    -

###  Discussion and Conclusions
- Created dataset of Finnish
- Created eight new large language models: seven monolingual Finnish models (from 185 million to 13 billion params) and a multilingual (176-billion param) model, BLUUMI.
- Introduced evaluation dataset: FIN-bench.

### Limitations
- Limitations on model alignment, bias, and toxicity.
- Does not match the GPT-3 pretraining process.
- Repetition of data collected from the web will reduce the model's capability.
