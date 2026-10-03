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
