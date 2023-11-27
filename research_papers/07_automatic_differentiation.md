# Automatic Differentiation: Theory and Practice <sup>[link](https://arxiv.org/pdf/2207.06114.pdf)</sup>

> By Mario Lezcano-Casado

### Abstract
- Paper fouces on forward and backward mode AD in the real and complex numbers.

### Coordinate-free Linear Algebra
- Goals:
    - Define vector spaces, bases, and linear maps.
    - Linear map preserves the operations of a vector space than computing in matrix.

#### Vector Spaces
- Associativity, Identity, Inverse, Commutativity, Compatibility, Scalar identity, Distributivity

#### Vector Subspaces and Bases
- A subset $U$ of a vector space $V$ over $K$ is a **vector subspace** or **linear subspace**.
- **Vector span** is defined as a set of all possible linear combinations of these vectors.

$$
\text{{span}}(v_1, \ldots, v_n) = \sum_{i=1}^{n} a_i v_i
$$

$$
a_i \in K, \quad \forall i \subseteq V
$$

- Issues in vector representation as a linear combination of other vectors:
    - The set of vector may not span the entire vector space $V$.
    - There may be multiple ways to represent $v$ as a linear combination of vectors.
- **Basis of a vector space**: $span(B) = V$ .In other words:
    - Spans the whole $V$.
    - Has no redundancies: no vector can be expressed as a linear combination of others.

#### Linear Maps
- These are maps between vector spaces that respect the vector space structure.
- Mathematically, it's given by:

$T(u + v) = T(u) + T(v) \quad \forall u, v \in V$

$T(av) = aT(v) \quad \forall v \in V, \, a \in K$

- **Linear Isomorphism**

#### Differences between a real vector space and $R<sup>n</sup>


### Multivariable Calculas

