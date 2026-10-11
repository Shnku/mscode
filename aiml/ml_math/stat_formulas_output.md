# Mathematical Computation Using NumPy

## Statistical formulas

Mean Formula
$$
\bar{x} = \dfrac{1}{n}\sum_{i=1}^{n}{x_i}
$$

Standard Deviation
$$
\sigma = \sqrt{\dfrac{1}{n}\sum_{i=1}^{n}{(x_i-\bar{x})^2}}
$$

Euclidian Distance
$$
d(\vec X,\vec Y)=\sqrt{\sum_{i=1}^{n}{(x_i-y_i)^2}}
$$

Covarience
$$
Cov(\vec A,\vec B)=\dfrac{1}{n}\sum_{i=1}^{n}{(a_i-\bar{a})(b_i-\bar{b})}
$$

Matrix Multiplication
$$C=A\cdot B $$

---

## Source Code

~~~~python
import numpy as np

# mean
mean = lambda X: np.sum(X) / len(X)

# standard deviation
def std_dev(X):
    count = len(X)
    mean_x = mean(X)
    sq_sum = 0
    for x_i in X:
        sq_sum += np.square(x_i - mean_x)
    return np.sqrt(sq_sum / count)

# euclidean distance
def Euclid_dist(X, Y):
    sq_sum = 0
    for x_i, y_i in zip(X, Y):
        sq_sum += np.square(x_i - y_i)
    return np.sqrt(sq_sum)

# covariance
def covar(X, Y):
    mean_x = mean(X)
    mean_y = mean(Y)
    sum_c = 0
    for x_i, y_i in zip(X, Y):
        sum_c += (x_i - mean_x) * (y_i - mean_y)
    return sum_c / len(X)

# matrix dot product
def matrix_dot_product(A, B):
    C = np.zeros((A.shape[0], B.shape[1]))
    for i in range(A.shape[0]):
        for j in range(B.shape[1]):
            for k in range(A.shape[1]):
                C[i, j] += A[i, k] * B[k, j]
    return C


if __name__ == "__main__":
    np.random.seed(42)

    count = 6
    X = np.random.randint(1, 100, count)
    Y = np.random.randint(1, 100, count)
    A = np.random.randint(1, 10, (2, 3))
    B = np.random.randint(1, 10, (3, 2))

    print("X:", X)
    print("Y:", Y)
    print("A:")
    print(A)
    print("B:")
    print(B)
    print("Mean of X:", mean(X))
    print("Standard deviation of X:", std_dev(X))
    print("Euclidean distance between X and Y:", Euclid_dist(X, Y))
    print("Covariance of X and Y:", covar(X, Y))
    print("Matrix dot product C = AB:")
    print(matrix_dot_product(A, B))
~~~~

---

## Generated inputs

All input vectors and matrices below are generated with NumPy's random number
generator using seed `42`.

Vector `X`:

~~~~text
[52 93 15 72 61 21]
~~~~

Vector `Y`:

~~~~text
[83 87 75 75 88 24]
~~~~

Matrix `A`:

~~~~text
[[3 6 5]
 [2 8 6]]
~~~~

Matrix `B`:

~~~~text
[[2 5]
 [1 6]
 [9 1]]
~~~~

---

## Outputs

| Formula | Output |
| --- | ---: |
| Mean of `X` | 52.333333 |
| standard deviation of `X` | 27.359743 |
| Euclidean distance between `X` and `Y` | 73.102668 |
| covariance of `X` and `Y` | 366.000000 |

Matrix dot product `C = AB`:

~~~~text
[[57. 56.]
 [66. 64.]]
~~~~

---
