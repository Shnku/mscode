import marimo

__generated_with = "0.25.2"
app = marimo.App()


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    # ID3(Iterative Dichtomiser v3) Decision Tree Classification Implementation
    """)
    return


@app.cell
def _():
    import marimo as mo
    import numpy as np
    import pandas as pd

    return mo, np, pd


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Implementation of ID3 Functionalities
    """)
    return


@app.cell
def _(np):
    # find probability
    P = lambda s, t: s / t


    def entropy(which_column):
        el, cnt = np.unique(which_column, return_counts=True)
        tot = which_column.size
        print(f"total: {which_column.size}, unique: {el}, {cnt}")
        pilog2pi = np.array(
            [P(cnt[i], tot) * np.log2(P(cnt[i], tot)) for i in range(el.size)]
        )
        print(pilog2pi)
        # Info(D)=-sum(p_i log_2(p_i))
        return -np.sum(pilog2pi)


    def weighted_entropy(data, which_column, class_label, log_print=False):
        el, cnt = np.unique(which_column, return_counts=True)
        tot = which_column.size
        p_f_info_da = []

        print(f"total: {which_column.size}, unique: {el}, {cnt}")
        # print(which_column, "\ntarget class", class_label)
        # weighted_entropy = Info(D|F)=SUM(P(D|F=target)*Info(D_target))
        for i, value in enumerate(el):
            new_df = data[which_column == value]
            print(f"{'=' * 10} Process (feature='{value}': target_calss='{class_label}')")
            p_f_info_da.append(P(cnt[i], tot) * entropy(new_df[class_label]))
            if log_print:
                print("splitted data:::::::::::::;\n", new_df)
                print(p_f_info_da)
        return np.sum(p_f_info_da)


    def info_gain(data, total_entropy, feature, target="Class"):
        if total_entropy is None:
            total_entropy = entropy(data[target])
        w_entropy = weighted_entropy(data, data[feature], target)
        return total_entropy - w_entropy


    def single_pass(data, feature_cols, target="Class"):
        info_for_features = []
        total_entropy = entropy(data[target])
        for features in feature_cols:
            print(f"\n{'-' * 30}PROCESSING FEATURE::'{features}'{'-' * 30}")
            info_for_features.append(info_gain(data, total_entropy, features, target))
        print(f"\nThe info for features: {feature_cols} \ninfos: {info_for_features}")
        return info_for_features


    def split(data, splitting_on):
        splitted_data = {}
        for feature_unique_value in data[splitting_on].unique():
            splitted_data[feature_unique_value] = data[
                data[splitting_on] == feature_unique_value
            ]
        return splitted_data


    # def run(data, features, max_depth):
    #     print(f"\n{'+' * 30} RUNNING ITER {max_depth} {'+' * 30}")
    #     if max_depth == 0:
    #         return
    #     info_gains = single_pass(data, features)
    #     max_info, max_info_feature = np.max(info_gains), features[np.argmax(info_gains)]
    #     print(f"max info gain: {max_info} for feature '{max_info_feature}'")
    #     if np.isclose(max_info, 0):
    #         return
    #     splitted_df = split(data, splitting_on=max_info_feature)
    #     remaining_features = [f for f in features if f != max_info_feature]
    #     for key, data_part in splitted_df.items():
    #         print("Processing part >>>> ", key, "\n", data_part)
    #         run(data_part, remaining_features, max_depth - 1)

    return single_pass, split


@app.cell
def _(np, single_pass, split):
    def run(data, features, max_depth, target="Play"):
        print(f"\n{'+' * 20} DEPTH {max_depth} {'+' * 20}")

        # 1. Pure node
        if data[target].nunique() == 1:
            return data[target].iloc[0]

        # 2. Depth limit or no features remaining
        if max_depth == 0 or len(features) == 0:
            return data[target].mode().iloc[0]

        # 3. Calculate information gain
        info_gains = single_pass(data, features, target)
        # 4. Select best feature
        max_idx = np.argmax(info_gains)
        max_info = info_gains[max_idx]
        max_info_feature = features[max_idx]
        print(f"Best feature: {max_info_feature}, Information gain: {max_info}")

        # 5. Stop if no useful information gain
        if np.isclose(max_info, 0):
            return data[target].mode().iloc[0]

        # 6. Split dataset
        splitted_df = split(data, max_info_feature)
        # 7. Remove selected feature
        remaining_features = [f for f in features if f != max_info_feature]
        print(f"Remaining Features to examine: {remaining_features}")

        # 8. Build subtree recursively
        tree = {
            "feature": max_info_feature,
            "branches": {},
            "default": data[target].mode().iloc[0],
        }

        for key, data_part in splitted_df.items():
            print(f"\nProcessing branch: {key}")
            subtree = run(data_part, remaining_features, max_depth - 1, target)
            tree["branches"][key] = subtree

        return tree


    return (run,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ## Test on Custom Playing Data
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### Define the Data
    """)
    return


@app.cell
def _(np, pd):
    # Create the data dictionary directly from the table
    data = np.array(
        [
            ["Sunny", "Hot", "High", False, "No"],
            ["Sunny", "Hot", "High", True, "No"],
            ["Overcast", "Hot", "High", False, "Yes"],
            ["Rainy", "Mild", "High", False, "Yes"],
            ["Rainy", "Cool", "Normal", False, "Yes"],
            ["Rainy", "Cool", "Normal", True, "No"],
            ["Overcast", "Cool", "Normal", True, "Yes"],
            ["Sunny", "Mild", "High", False, "No"],
            ["Sunny", "Cool", "Normal", False, "Yes"],
            ["Rainy", "Mild", "Normal", False, "Yes"],
            ["Sunny", "Mild", "Normal", True, "Yes"],
            ["Overcast", "Mild", "High", True, "Yes"],
            ["Overcast", "Hot", "Normal", False, "Yes"],
            ["Rainy", "Mild", "High", True, "No"],
        ],
        dtype=object,
    )

    df1 = pd.DataFrame(
        data, columns=["Outlook", "Temperature", "Humidity", "Windy", "Play"]
    )
    # Display the DataFrame
    df1
    return (df1,)


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### Running Passes
    """)
    return


@app.cell
def _(df1, single_pass):
    single_pass(df1, feature_cols=df1.columns[:-1], target="Play")
    return


@app.cell
def _(df1, run):
    run(df1, df1.columns[:-1], 4)
    return


@app.cell
def _():
    # we do split the df1 based on the max info gain
    # here split based on 'Outlook'
    return


@app.cell
def _(df1, split):
    sp = split(df1, "Outlook")
    sp

    for k, v in sp.items():
        print(k, "\n", v)
    return


@app.cell
def _():
    return


if __name__ == "__main__":
    app.run()
