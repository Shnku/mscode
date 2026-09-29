# /// script
# requires-python = ">=3.13"
# dependencies = [
#     "matplotlib>=3.11.2",
#     "numpy>=2.5.3",
# ]
# ///


import math

import matplotlib.pyplot as plt
import numpy as np

## transformation matrices...................


def get_rotation_matrix(degree_angle):
    """Rotate point around the origin by given degrees"""
    angle = math.radians(degree_angle)
    return np.array(
        [
            [np.cos(angle), -np.sin(angle), 0],
            [np.sin(angle), np.cos(angle), 0],
            [0, 0, 1],
        ]
    )


def get_translation_matrix(tx, ty):
    """Shift image by tx (horizontal) and ty (vertical)"""
    return np.array(
        [
            [1, 0, tx],
            [0, 1, ty],
            [0, 0, 1],
        ]
    )


def get_scaling_matrix(sx, sy):
    """Scale image by sx and sy relative to the origin"""
    return np.array(
        [
            [sx, 0, 0],
            [0, sy, 0],
            [0, 0, 1],
        ]
    )


def get_shearing_matrix(shx=0.0, shy=0.0):
    """Shear image along x and y axes"""
    return np.array(
        [
            [1, shx, 0],
            [shy, 1, 0],
            [0, 0, 1],
        ]
    )


def get_reflection_matrix(about="x"):
    """Reflect image across a specific axis or the origin"""
    if about == "x":
        # Flip across x-axis (invert Y)
        return np.array(
            [
                [1, 0, 0],
                [0, -1, 0],
                [0, 0, 1],
            ]
        )
    elif about == "y":
        # Flip across y-axis (invert X)
        return np.array(
            [
                [-1, 0, 0],
                [0, 1, 0],
                [0, 0, 1],
            ]
        )
    elif about == "y=x":
        # Flip across diagonal y=x (swap X and Y)
        return np.array(
            [
                [0, 1, 0],
                [1, 0, 0],
                [0, 0, 1],
            ]
        )
    elif about == "y=-x":
        # Flip across diagonal y=-x (swap and invert X and Y)
        return np.array(
            [
                [0, -1, 0],
                [-1, 0, 0],
                [0, 0, 1],
            ]
        )
    elif about == "origin":
        # Flip through origin (invert both X and Y)
        return np.array(
            [
                [-1, 0, 0],
                [0, -1, 0],
                [0, 0, 1],
            ]
        )
    else:
        return "choose x,y,y=x, y=-x"


## ========================================
# Helper functiones.........


def apply_transformation(points_matrix, transform_matrix):
    """Function to apply a given transformation matrix to a list of points...."""
    print("\nTransformation Matrix:------\n", transform_matrix)
    print("Original points:------\n", points_matrix)
    transformed_points = transform_matrix @ points_matrix.T
    print("Transformed points:------\n", transformed_points.T)
    return transformed_points.T


def visualize_transformation(old, new, title="transformed", save_img=False):
    """Function to visualize the transformation....."""
    plt.figure(figsize=(6, 6), dpi=90)

    before = np.append(old, [old[0]], axis=0)  # make closed point
    plt.plot(before[:, 0], before[:, 1], "--o")

    after = np.append(new, [new[0]], axis=0)
    plt.plot(after[:, 0], after[:, 1], "-o")

    plt.axhline(0, color="black", linewidth=1)
    plt.axvline(0, color="black", linewidth=1)
    plt.xlabel("X-axis")
    plt.ylabel("Y-axis")
    plt.title(title)
    plt.grid(True)
    plt.axis("equal")  # equal scaling for x and y axes
    plt.legend(["Original", title])
    if save_img:
        plt.savefig(f"{title}.png")
    plt.show()


def visualize_multiple_transformation(
    old,
    new_forms: list,
    labels: list,
    title="Multiple Transformation together",
    save_img=False,
):
    """Function to visualize the transformation....."""
    plt.figure(figsize=(6, 6), dpi=90)

    before = np.append(old, [old[0]], axis=0)  # make closed point
    plt.plot(before[:, 0], before[:, 1], "--o")

    for new, title_i in zip(new_forms, labels):
        after = np.append(new, [new[0]], axis=0)
        plt.plot(after[:, 0], after[:, 1], "-o")

    plt.axhline(0, color="black", linewidth=1)
    plt.axvline(0, color="black", linewidth=1)
    plt.xlabel("X-axis")
    plt.ylabel("Y-axis")
    plt.grid(True)
    plt.axis("equal")  # equal scaling for x and y axes
    plt.title(title)
    plt.legend(["original"] + labels)
    if save_img:
        plt.savefig(f"{title}.png")
    plt.show()
