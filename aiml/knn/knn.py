import marimo

__generated_with = "0.25.2"
app = marimo.App()


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    # KNN Classifier from Scratch
    """)
    return


@app.cell
def _():
    import marimo as mo

    return (mo,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Setup
    """)
    return


@app.cell
def _():
    # This Python 3 environment comes with many helpful analytics libraries installed
    # It is defined by the kaggle/python Docker image: https://github.com/kaggle/docker-python
    # For example, here's several helpful packages to load

    # Input data files are available in the read-only "../input/" directory
    # For example, running this (by clicking run or pressing Shift+Enter) will list all files under the input directory
    import os

    import matplotlib.pyplot as plt
    import numpy as np  # linear algebra
    import pandas as pd  # data processing, CSV file I/O (e.g. pd.read_csv)

    for dirname, _, filenames in os.walk("/kaggle/input"):
        for filename in filenames:
            print(os.path.join(dirname, filename))

    # You can write up to 20GB to the current directory (/kaggle/working/) that gets preserved as output when you create a version using "Save & Run All"
    # You can also write temporary files to /kaggle/temp/, but they won't be saved outside of the current session

    # Use the kagglehub client library to attach Kaggle resources like competitions, datasets, and models to your session
    # Learn more about kagglehub: https://github.com/Kaggle/kagglehub/blob/main/README.md

    import kagglehub

    PATH = kagglehub.dataset_download("nishtha711/wine-quality-uci-clean-csv-for-ml")
    print(PATH)
    return PATH, np, pd, plt


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## manual Train Test Split
    """)
    return


@app.cell
def _(np):
    def train_test_split_scratch(X, y, test_size=0.2, random_state=42):
        """
        Splits features (X) and labels (y) into train and test sets from scratch.

        Parameters:
        - X: Features (NumPy array, Pandas DataFrame, or list)
        - y: Target labels (NumPy array, Pandas Series, or list)
        - test_size: Proportion of the dataset to include in the test split (float)
        - random_state: Seed for random number generator for reproducibility
        """
        # Set random seed if provided
        if random_state is not None:
            np.random.seed(random_state)

        # Convert inputs to NumPy arrays for consistent indexing
        X_arr = np.array(X)
        y_arr = np.array(y)

        # Ensure X and y have the same number of rows
        assert len(X_arr) == len(y_arr), "X and y must have the same length"

        # Generate a shuffled array of indices
        indices = np.arange(len(X_arr))
        np.random.shuffle(indices)

        # Calculate the split index
        test_count = int(len(X_arr) * test_size)
        test_indices = indices[:test_count]
        train_indices = indices[test_count:]

        # Split X and y
        X_train, X_test = X_arr[train_indices], X_arr[test_indices]
        X_train_labels, X_test_labels = y_arr[train_indices], y_arr[test_indices]

        return X_train, X_test, X_train_labels.flatten(), X_test_labels.flatten()

    return (train_test_split_scratch,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Define the KNN Classifier Implementation from Scratch
    """)
    return


@app.cell
def _(np):
    class KNNclassifier:
        def __init__(self, k) -> None:
            self.k = k

        def euclidean_distance(self, vec1, vec2):
            return np.sqrt(np.sum((np.array(vec1) - np.array(vec2)) ** 2))

        def knn_predict(
            self, X: np.ndarray, X_classes: np.ndarray, y: np.ndarray, log_print=False
        ):
            pair_distances = np.array([self.euclidean_distance(d_pt, y) for d_pt in X])
            # calculate nearest labels
            sorted_index = np.argsort(pair_distances)
            sorted_labels = np.array(X_classes[sorted_index])
            # take k neighbours
            value, counts = np.unique(sorted_labels[: self.k], return_counts=True)
            common = value[np.argmax(counts)]
            if log_print:
                print(np.array([pair_distances, X_classes, sorted_index]).T)
                print(f"{self.k} neighbours are: {np.array(sorted_labels[: self.k])}")
            return common

        def knn_predict_all(self, X: np.ndarray, X_classes: np.ndarray, y_all: np.ndarray):
            return np.array([self.knn_predict(X, X_classes, y_point) for y_point in y_all])

        def validation(self, predicted_labels, original_labels):
            return predicted_labels == original_labels

    return (KNNclassifier,)


@app.cell
def _(np):
    arr = np.array([3, 3, 3, 1, 2, 1, 1, 3, 2, 1, 1])

    counts = np.unique(arr, return_counts=True)
    counts
    return (counts,)


@app.cell
def _(counts, np):
    print(np.argmax(counts[1]))
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Test on Custom Small Data
    """)
    return


@app.cell
def _(np):
    training_data = np.array([[1, 2], [1.5, 4], [3, 5], [6, 4], [6.5, 4.1], [7, 9], [9, 5]])
    training_labels = np.array(["A", "A", "A", "A", "B", "B", "B"])
    test_point = np.array([7, 4.6])
    k = 3
    return k, test_point, training_data, training_labels


@app.cell
def _(KNNclassifier, k, test_point, training_data, training_labels):
    model = KNNclassifier(k)
    model.knn_predict(training_data, training_labels, test_point)
    return


@app.cell
def _(plt, test_point, training_data):
    plt.scatter(training_data[:4, 0], training_data[:4, 1])
    plt.scatter(training_data[4:, 0], training_data[4:, 1])
    plt.scatter(test_point[0], test_point[1])
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Now on Wine DataSet
    """)
    return


@app.cell
def _(PATH, pd):
    # load the dataset using pandas
    data_all = pd.read_csv(PATH + "/wine_clean.csv")
    data_all
    return (data_all,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### check the dataset
    """)
    return


@app.cell
def _(data_all):
    data_all["Class"].unique()
    return


@app.cell
def _(data_all):
    data_all.columns
    return


@app.cell
def _(data_all):
    X = data_all.iloc[:, 1:]
    X_labels = data_all.iloc[:, :1]

    X.head(), X_labels.head()
    return X, X_labels


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### train test split
    """)
    return


@app.cell
def _(X, X_labels, train_test_split_scratch):
    X_train, y_test, X_train_labels, y_test_labels = train_test_split_scratch(X, X_labels)
    print(
        f"Shapes: train={X_train.shape},train label={X_train_labels.shape}, Test={y_test.shape},test_labels={y_test_labels.shape} "
    )
    X_train, y_test, X_train_labels, y_test_labels
    return X_train, X_train_labels, y_test, y_test_labels


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Instance classifier model & Test
    """)
    return


@app.cell
def _(KNNclassifier, X_train, X_train_labels, y_test):
    model2 = KNNclassifier(k=3)
    model2.knn_predict(X_train, X_train_labels, y_test[0], log_print=True)
    return (model2,)


@app.cell
def _(X_train, X_train_labels, model2, y_test):
    out_predict = model2.knn_predict_all(X_train, X_train_labels, y_test)
    out_predict
    return (out_predict,)


@app.cell
def _(y_test_labels):
    y_test_labels
    return


@app.cell
def _(model2, out_predict, y_test_labels):
    check = model2.validation(y_test_labels, out_predict)
    check
    return (check,)


@app.cell
def _(check, np):
    true_data = np.unique(check, return_counts=True)
    true_data
    return (true_data,)


@app.cell
def _(true_data):
    true_data[1][1]
    return


@app.cell
def _(true_data, y_test_labels):
    accuracy = true_data[1][1] / len(y_test_labels) * 100
    print(f"model accuract is : {accuracy:.2f}%")
    return


if __name__ == "__main__":
    app.run()
