# /// script
# requires-python = ">=3.13"
# dependencies = [
#     "marimo>=0.23.3",
#     "numpy>=2.5.4",
# ]
# ///

import marimo

__generated_with = "0.24.2"
app = marimo.App(auto_download=["ipynb", "html"])


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    # Using Numpy to calcullate distance matrix
    """)
    return


@app.cell
def _():
    import marimo as mo
    import numpy as np

    return mo, np


@app.cell
def _(np):
    # how to calculate the diatance?
    def euclid_dist(v1, v2):
        v1 = np.array(v1)
        v2 = np.array(v2)
        return np.sqrt(np.sum(np.square(v1 - v2)))


    # euclid_dist(np.array([1, 1]), np.array([2, 2]))
    euclid_dist([1, 1], [2, 2])  # converts list to np.appay automatically
    return (euclid_dist,)


@app.cell
def _(mo, np):
    data_5d = mo.ui.matrix(
        np.random.randint(1, 10, size=(10, 5)),
        row_labels=[f"p{i}" for i in range(10)],
        column_labels=[f"f{i}" for i in range(5)],
    )
    data_5d
    return (data_5d,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### Preparing the distance matrix..
    """)
    return


@app.cell
def _(data_5d, euclid_dist, np):
    dist_matrix = np.array(
        [[euclid_dist(pi, pj) for pj in data_5d.value] for pi in data_5d.value],
    )
    return (dist_matrix,)


@app.cell
def _(dist_matrix, mo):
    mo.ui.matrix(
        dist_matrix,
        precision=2,
        disabled=True,
        row_labels=[f"d-p{i}" for i in range(10)],
        column_labels=[f"d-p{i}" for i in range(10)],
    )
    return


@app.cell
def _():
    return


if __name__ == "__main__":
    app.run()
