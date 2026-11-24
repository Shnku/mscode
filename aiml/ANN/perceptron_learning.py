import marimo

__generated_with = "0.25.2"
app = marimo.App(width="medium", auto_download=["html"])


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    # Visualizing Perceptron Learning
    """)
    return


@app.cell
def _():
    import marimo as mo
    import numpy as np
    import matplotlib.pyplot as plt

    return mo, np


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## The Algorithm of Perceptron Learning
    The step-by-step procedure for Perceptron Learning, as outlined in the provided document, is structured as follows:

    ### Step 1: Initialization

    - Initialize all weights.
    - Set the learning rate $\eta$ such that $0 < \eta \le 1$.
    - Set the activation function threshold $\theta$.

    -----

    ### Step 2: Training Loop (Steps 3–8)

    For each training pair $s:t$, perform **Steps 4 through 8**:

    1. **Activate Input Units (Step 4):**
        - Set $x_i = s_i$ for $i = 1$ to $m$.
    2. **Compute Net Input (Step 5):**
        - Calculate the total net input to the output unit:   $y_{in} = \sum_{i=0}^{n} w_i x_i$
    3. **Compute Output Activation (Step 6):**
        - Calculate the output unit activation $y_{out}$ using the activation function with threshold $\theta$:
            $y_{out} = \begin{cases}
            1, & \text{if } y_{in} > \theta \\
            0, & \text{if } -\theta \le y_{in} \le \theta \\
            -1, & \text{if } y_{in} < -\theta
            \end{cases}$
    4. **Adjust Weights (Step 7):**
        - **If an error occurs** $y_{out} \neq t$, update the weights using:  $w_i(\text{new}) = w_i(\text{old}) + \eta \times t \times x_i$
        - **If no error occurs** ($y_{out} = t$), keep the weights unchanged:  $w_i(\text{new}) = w_i(\text{old})$
    5. **Check Stopping Condition (Step 8):**
        - If no errors occurred ($y_{out} = t$) across all training pairs in the set, **stop**.
        - Otherwise, return to **Step 3** to begin a new epoch.
    """)
    return


@app.cell
def _(np):
    def activation_func(yin, theta):
        return 1 if yin > theta else 0 if -theta <= yin <= theta else -1

    def update_weights(
        weights: np.ndarray, p_i: np.ndarray, target, learning_rate
    ):
        print(f"calculating: {weights} + ({target} * {learning_rate * p_i})")
        # print(f"calculating: {weights} + ({target * learning_rate * p_i})")
        return np.array(
            np.array(weights) + (learning_rate * target * np.array(p_i))
        )

    return activation_func, update_weights


@app.cell
def _():
    # np.array([1, 0, 0, 0]) + (2 * 7 * np.array([1, 1, -1, -1])) # it works
    return


@app.cell
def _(activation_func, np, update_weights):
    def single_pass(P, target, init_weights, threshold=0):
        weights = init_weights
        y_pred = []
        for i, p_i in enumerate(P):
            print(f">>Processing datapoint p{i + 1} = {p_i}")
            y_in = np.dot(p_i, weights)
            y_out = activation_func(y_in, theta=threshold)
            y_pred.append(y_out)
            print(f"The output: {y_in} -> activation func -> {y_out}", end=" ")
            if y_out != target[i]:
                print(f"(y_out != t{i + 1}({target[i]}),")
                weights = update_weights(
                    weights, p_i, target[i], learning_rate=1
                )
                print(f"so, updated weights: {weights}\n\n")
            else:
                print(
                    f"(y_out == t{i + 1}({target[i]}), no weights update\n\n"
                )
        return np.array(weights), np.array(y_pred)

    return (single_pass,)


@app.cell
def _(P, np, single_pass, target):
    def fit(X, y, initial_wt, n_iter=10):
        updated_weights = initial_wt
        for i in range(n_iter):
            print(f"\n------iter----------{i + 1}")
            updated_weights, prediction = single_pass(
                P, target, updated_weights
            )
            print(f">>>>> {updated_weights}, {prediction}")
            if np.allclose(y, prediction):
                print("CONVERGES..............")
                break

    return (fit,)


@app.cell
def _(np):
    # sample data point
    P = np.array(
        [
            [1, -1, 1, 1],
            [1, 1, -1, 1],
            [1, 1, 1, -1],
            [1, 1, 1, 1],
        ]
    )

    target = np.array([-1, -1, -1, 1])
    return P, target


@app.cell
def _(P, fit, np, target):
    fit(P, target, np.zeros(4))
    return


@app.cell
def _():
    return


if __name__ == "__main__":
    app.run()
