## FinGPT: Large Generative Models for a Small Language

> By ***Risto Luukkonen, Ville Komulainen, Jouni Luoma, Anni Eskelinen,
Jenna Kanerva, Hanna-Mari Kupari, Filip Ginter, Veronika Laippala,
Niklas Muennighoff, Aleksandra Piktus, Thomas Wang, Nouamane Tazi,
Teven Le Scao, Thomas Wolf, Osma Suominen, Samuli Sairanen,
Mikko Merioksa, Jyrki Heinonen, Aija Vahtola, Samuel Antao, Sampo Pyysalo***

PAPER: [Link](https://arxiv.org/pdf/2311.05640.pdf)

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

### Models
- Follows GPT architecture for the number of layers, dimensionality, and number of attention heads
- Pre-training: same approach as BLOOM family, i.e., position embeddings, layer normalization, or any other software implementation.
- Continue pre-training called BLUUMI.

### Data
Details about training data, preprocessing steps, data statistics, and analysis.

#### Data Sources
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

#### Preprocessing
- *Deduplication*: performed approximate Ngram overlap-based deduplication using Onion. Then, trim the duplicate lines from the beginning and end of each document.
- *Heuristic filtering*: filter out text that are not finnish, e.g., punctuation, digits, alphabets, etc.
- *N-gram model filtering*: remove text with surface characteristics.
- *Toxicity filtering*: to remove abusive contents.
- *Masking personal data*: e.g., mask email addresses, phone numbers, etc.
- *Tokenization*: followed BLOOM recipe.

#### Register Analysis
- In the end, apply register identification model.
- It presents text in different categories as narrative, interactive discussion and lyrical.

### Pretraining
