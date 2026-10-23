# /// script
# requires-python = ">=3.13"
# dependencies = [
#     "kagglehub>=1.0.2",
#     "marimo>=0.23.3",
#     "numpy>=2.5.4",
#     "pandas>=3.0.6",
# ]
# ///

import marimo

__generated_with = "0.24.2"
app = marimo.App()


@app.cell
def _():
    import kagglehub
    import marimo as mo
    import numpy as np
    import pandas as pd

    return (np,)


@app.cell
def _():
    return


@app.cell
def _(np):
    class Kmedoids:
        def __init__(self, k):
            self.k = k
            self.centroids = None
            self.cluster_labels = None
            self._distance_matrix = None

        def _euclidian_dist(self, p1: np.ndarray, p2: np.ndarray):
            p1 = np.asarray(p1)
            p2 = np.asarray(p2)
            return np.sqrt(np.sum(np.square(p1 - p2)))

        def _calculate_pairwise_distance_matrix(self, data: np.ndarray):
            self._distance_matrix = np.array(
                [[self._euclidian_dist(p1=pi, p2=pj) for pj in data] for pi in data],
            )

        def _asign_dpoints_to_clusters(self, data: np.ndarray, centroids: np.ndarray):
            print("=" * 15, "assign datapoints to clusters", "=" * 15)
            cluster_labels = np.empty(len(data))
            for i, p in enumerate(data):
                distances = np.array([self._euclidian_dist(p, c) for c in centroids])
                closest_cluster_indx = np.argmin(distances)
                cluster_labels[i] = closest_cluster_indx
                # print(
                # f"iter {i} datapoint {p} || distances:{distances} || closest_index:{closest_cluster_indx}"
                # )
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
            if self._distance_matrix is None:
                dist_mat = self._calculate_pairwise_distance_matrix(data)
                self._distance_matrix = np.array(dist_mat.copy())

            new_centroids = np.empty([len(centroids), data.shape[1]])

            for which_cluster in range(len(centroids)):
                set_c = np.where(cluster_labels == which_cluster)
                print(f"cluster set index{set_c}")
                # sum the distances from each set points
                sum_c = [
                    np.sum(self._distance_matrix[point_indx]) for point_indx in set_c[0]
                ]
                print("each sums", sum_c)
                # min which
                min_c = np.argmin(sum_c)
                print(f"arg min:{min_c}, which set: {set_c[0][min_c]}")
                # update new centroid ..
                new_centroids[which_cluster] = data[set_c[0][min_c]]
                print(f"updated centroids:\n {new_centroids}")
            return np.array(new_centroids)

        def fit(self, data, init_centroids):
            self.centroids = init_centroids
            for i in range(100):
                print("+" * 15, f"Starting iteration {i}", "+" * 15)
                old_centroids = self.centroids.copy()
                # Assign points to nearest centroid
                cluster_labels = self._asign_dpoints_to_clusters(data, old_centroids)
                # Update centroids based on mean of assigned points
                new_centroids = self._update_centroids(data, old_centroids, cluster_labels)
                # Check for convergence
                print(f"old centroid:\n{old_centroids},\nnew centroid:\n{new_centroids}")
                self.centroids = new_centroids
                if np.allclose(new_centroids, old_centroids):
                    print(f"Converged at iteration {i}")
                    break
            return new_centroids, self.cluster_labels

    return (Kmedoids,)


@app.cell
def _(Kmedoids, np):
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
    model1 = Kmedoids(k=3)
    c_labels = model1._asign_dpoints_to_clusters(data_5d, initial_c)
    print(model1._calculate_pairwise_distance_matrix(data_5d))
    final_centroids = model1._update_centroids(data_5d, initial_c, c_labels)
    # model1.fit(data_5d, initial_c)

    return data_5d, model1


@app.cell
def _(np):
    lab = np.array([0, 0, 0, 1, 1, 1, 2, 2, 2])
    np.where(lab == 0)
    return


@app.cell
def _(data_5d, model1, np):
    a = np.array(
        [[model1._euclidian_dist(p1=pi, p2=pj) for pj in data_5d] for pi in data_5d],
    )
    print(a[0])
    np.sum(a[0])
    return


@app.cell
def _():
    return


@app.cell
def _():
    return


if __name__ == "__main__":
    app.run()
