# /// script
# requires-python = ">=3.13"
# dependencies = [
#     "kagglehub>=1.0.2",
#     "marimo>=0.23.3",
#     "matplotlib>=3.11.2",
#     "mcp>=2.0.0",
#     "numpy>=2.5.4",
#     "pandas>=3.0.6",
#     "python-lsp-ruff>=2.3.4",
#     "python-lsp-server>=1.15.0",
#     "ruff>=0.17.0",
#     "scikit-learn>=1.9.1",
#     "websockets>=17.2",
# ]
# ///

import marimo

__generated_with = "0.24.2"
app = marimo.App(width="medium", auto_download=["ipynb"])


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    # Unsupervised Learning Methods Basic+Manual
    """)


@app.cell
def _():
    import math

    import marimo as mo
    import matplotlib.pyplot as plt
    import numpy as np

    return math, mo, np, plt


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## K-means  Clustering
    """)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### Perform the k-means algorithm manually. $k=2$ and $dim(2)$ data
    Lets do for k=2,
    - choose two random point as center/centroid for two clusters.
    - calculate the euclidian distance between two centroid and each points.
    - unclude the the point with min distance into respective clusters/sets.
    - repeate the process until normalize.
    """)


@app.cell
def _(math):
    def euclidian_dist(p1, p2):
        return math.sqrt((p1[0] - p2[0]) ** 2 + (p1[1] - p2[1]) ** 2)

    return (euclidian_dist,)


@app.cell
def _(data, euclidian_dist):
    # Assignment of data points to clusters
    def cluster_seperation(c1, c2):
        set1 = []
        set2 = []
        for p in data:
            d1 = euclidian_dist(c1, p)
            d2 = euclidian_dist(c2, p)
            # print(d1, d2)
            if d1 <= d2:
                set1.append(p)
            else:
                set2.append(p)
        return set1, set2

    return (cluster_seperation,)


@app.function
# update centroid..
def calculate_new_centroid(l1):
    ln = len(l1)
    sum_x, sum_y = 0, 0
    for x, y in l1:
        sum_x = sum_x + x
        sum_y = sum_y + y
    c1, c2 = sum_x / ln, sum_y / ln
    return [c1, c2]


@app.cell
def _(cluster_seperation):
    ## K Means stapes............
    def kmeans2(data, c1, c2):
        # iterate
        for i in range(100):
            print(f"---iter {i}---")
            old_c1, old_c2 = c1, c2
            print("old centroid=", old_c1, old_c2)
            l1, l2 = cluster_seperation(c1=c1, c2=c2)
            print(l1, l2, sep="\n")
            c1 = calculate_new_centroid(l1)
            c2 = calculate_new_centroid(l2)
            print("new centroid=", c1, c2)
            if old_c1 == c1 and old_c2 == c2:
                print("converged")
                break

    return (kmeans2,)


@app.cell
def _(np):
    data = np.array(
        [
            [1.0, 1.0],
            [1.5, 2.0],
            [3.0, 4.0],
            [5.0, 7.0],
            [3.5, 5.0],
            [4.5, 5.0],
            [3.5, 4.5],
        ]
    )
    return (data,)


@app.cell
def _(data):
    print(data[:, 0])


@app.cell
def _(data, plt):
    plt.scatter(x=data[:, 0], y=data[:, 1])


@app.cell
def _(data, kmeans2):
    # choose cluster
    c1 = [1.0, 1.0]
    c2 = [5.0, 7.0]
    kmeans2(data, c1, c2)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### Compare Using sklearks implementation
    """)


@app.cell
def _(data, np):
    X = np.array(data)

    initial_centroids = np.array([[1.0, 1.0], [5.0, 7.0]])
    return X, initial_centroids


@app.cell
def _(X, initial_centroids):
    from sklearn.cluster import KMeans

    model = KMeans(n_clusters=2, init=initial_centroids, n_init=1, random_state=42)

    model.fit(X)

    print("Sklearn centroids:")
    print(model.cluster_centers_)

    print("Sklearn labels:")
    print(model.labels_)
    return (KMeans,)


@app.cell
def _():
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md("""
    ### More generalized manual k-means implemantation  extending $n$ dimension and $k$ clusters
    What to do when datapoints are $dim(n)$ and we need $k$ clusters
    """)


@app.cell
def _(np):
    a = np.random.randint(5, size=(4, 5))
    a
    return (a,)


@app.cell
def _(a, np):
    cl = np.array([1, 2, 2, 1])
    a[cl == 2]


@app.cell
def _(np):
    np.empty([2, 3])


@app.cell
def _(np):
    class Kmeans:
        def __init__(self, k):
            self.k = k
            self.centroids = None
            self.cluster_labels = None

        def _euclidian_dist(self, p1: np.ndarray, p2: np.ndarray):
            return np.sqrt(np.sum(np.square(p1 - p2)))

        def _asign_dpoints_to_clusters(self, data: np.ndarray, centroids: np.ndarray):
            print("=" * 15, "assign datapoints to clusters", "=" * 15)
            cluster_labels = np.empty(len(data))
            for i, p in enumerate(data):
                distances = np.array([self._euclidian_dist(p, c) for c in centroids])
                closest_cluster_indx = np.argmin(distances)
                cluster_labels[i] = closest_cluster_indx
                # print(f"iter {i} datapoint {p} || distances:{distances} || closest_index:{closest_cluster_indx}")
                # print(f"cluster labels: {cluster_labels}")
                self.cluster_labels = cluster_labels
            return cluster_labels

        def _update_centroids(
            self,
            data: np.ndarray,
            centroids: np.ndarray,
            cluster_labels: np.ndarray,
        ):
            print("=" * 15, "update centroids using mean", "=" * 15)
            new_centroids = np.empty([len(centroids), data.shape[1]])
            for which_cluster in range(len(centroids)):
                cluster_set = data[cluster_labels == which_cluster]
                new_centroids[which_cluster] = np.mean(cluster_set)
                # print(f"cluster set:\n {cluster_set}")
                # print(f"updated centroids:\n {new_centroids}")
            return np.array(new_centroids)

        def fit(self, data, init_centroids):
            self.centroids = init_centroids
            for i in range(100):
                print("+" * 15, f"Starting iteration {i}", "+" * 15)
                old_centroids = self.centroids.copy()
                # Assign points to nearest centroid
                cluster_labels = self._asign_dpoints_to_clusters(data, old_centroids)
                # Update centroids based on mean of assigned points
                new_centroids = self._update_centroids(
                    data, old_centroids, cluster_labels
                )
                # Check for convergence
                print(
                    f"old centroid:\n{old_centroids},\nnew centroid:\n{new_centroids}"
                )
                self.centroids = new_centroids
                if np.allclose(new_centroids, old_centroids):
                    print(f"Converged at iteration {i}")
                    break
            return new_centroids, self.cluster_labels

    return (Kmeans,)


@app.cell
def _(Kmeans, np):
    # ==========================================
    # Testing with 5 Dimensions and 3 Clusters
    # ==========================================

    # 5D Data points
    data_5d = np.array(
        [
            [1, 2, 1, 0, 1],
            [1, 1, 1, 1, 0],
            [2, 1, 0, 1, 1],  # Group 1
            [10, 12, 11, 10, 11],
            [11, 11, 12, 11, 10],
            [12, 10, 11, 12, 11],  # Group 2
            [50, 5, 50, 5, 50],
            [52, 4, 51, 6, 49],
            [51, 6, 49, 4, 51],  # Group 3
        ]
    )

    # 3 Initial centroids (picking a point from each suspected group)
    initial_c = np.array(
        [
            [1, 1, 1, 1, 1],  # Near Group 1
            [10, 10, 10, 10, 10],  # Near Group 2
            [50, 5, 50, 5, 50],  # Near Group 3
        ]
    )

    # Initialize the class with k=3
    model1 = Kmeans(k=3)
    # c_labels = model1._asign_dpoints_to_clusters(data_5d, initial_c)
    # final_centroids = model1._update_centroids(data_5d, initial_c, c_labels)
    model1.fit(data_5d, initial_c)
    return data_5d, initial_c


@app.cell
def _(KMeans, data_5d, initial_c):
    model_o1 = KMeans(n_clusters=3, init=initial_c, n_init=1, random_state=42)

    model_o1.fit(data_5d)

    print("Sklearn centroids:")
    print(model_o1.cluster_centers_)

    print("Sklearn labels:")
    print(model_o1.labels_)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Testing with iris dataset
    """)


@app.cell
def _():
    import os

    import kagglehub
    import pandas as pd

    # Download latest version
    path = kagglehub.dataset_download("himanshunakrani/iris-dataset")

    print("Path to dataset files:", path)
    print(os.listdir(path))
    return path, pd


@app.cell
def _(path, pd):
    dfs = pd.read_csv(f"{path}/iris.csv")
    dfs.head()
    return (dfs,)


@app.cell
def _(dfs):
    df = dfs.iloc[:, :-1]
    df.head()
    return (df,)


@app.cell
def _(df, np):
    np.array(df.head())


@app.cell
def _(df, np):
    np.array(df.iloc[1, :])


@app.cell
def _(Kmeans, df, np):
    model2 = Kmeans(3)
    initial2_c = [
        np.array(df.iloc[1]),
        np.array(df.iloc[5]),
        np.array(df.iloc[10]),
    ]

    # Initialize the class with k=3
    model2 = Kmeans(k=3)
    out = model2.fit(np.array(df), initial2_c)
    print(f"centroids:\n{out[0]}\n\nlabels:{out[1]}")
    return initial2_c, out


@app.cell
def _(dfs, pd):
    pd.factorize(dfs.iloc[:, -1])


@app.cell
def _(out):
    out[1]


@app.cell
def _(dfs, np, out, pd):
    # verify with original
    np.isclose(out[1], np.array(pd.factorize(dfs.iloc[:, -1])[0]))


@app.cell
def _(KMeans, df, initial2_c):
    model_org = KMeans(n_clusters=3, init=initial2_c)

    model_org.fit(df)

    print("Sklearn centroids:")
    print(model_org.cluster_centers_)

    print("Sklearn labels:")
    print(model_org.labels_)
    return (model_org,)


@app.cell
def _(dfs, model_org, np, pd):
    # verify with original
    np.isclose(model_org.labels_, np.array(pd.factorize(dfs.iloc[:, -1])[0]))


@app.cell
def _():
    return


if __name__ == "__main__":
    app.run()
