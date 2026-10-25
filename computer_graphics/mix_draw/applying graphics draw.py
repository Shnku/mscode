# /// script
# requires-python = ">=3.13"
# dependencies = [
#     "marimo>=0.23.3",
#     "matplotlib>=3.11.2",
#     "numpy>=2.5.4",
# ]
# ///

import marimo

__generated_with = "0.25.1"
app = marimo.App(width="medium", auto_download=["html"])


@app.cell
def _():
    import marimo as mo
    import numpy as np
    import matplotlib.pyplot as plt

    return mo, plt


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    # Drawing combinations of circle ellipse lines
    """)
    return


@app.cell(hide_code=True)
def _(mo):
    mo.md(r"""
    ### Needed algorithms

    - Bresenhams Linedraw
    - Midpoint Ellipse
    - Midpoint Circle
    """)
    return


@app.function
def Bresenhams_line(start, end):
    x1, y1 = start
    x2, y2 = end
    dx = abs(x2 - x1)
    dy = abs(y2 - y1)

    # Direction steps (+1 or -1) needed for negative slope
    sx = 1 if x2 >= x1 else -1
    sy = 1 if y2 >= y1 else -1
    # List to store results............
    x_list = [x1]
    y_list = [y1]

    # for (m <= 1) x++, y to be determine
    # for negative slope m <= -1
    if dx >= dy:
        pk = 2 * dy - dx
        for _ in range(dx):
            x1 += sx
            if pk >= 0:
                y1 += sy
                pk += 2 * dy - 2 * dx
            else:
                pk += 2 * dy
            x_list.append(x1)
            y_list.append(y1)
    # for (m > 1) y++, x to be determine...
    # for negative slope m > -1
    else:
        pk = 2 * dx - dy
        for _ in range(dy):
            y1 += sy
            if pk >= 0:
                x1 += sx
                pk += 2 * dx - 2 * dy
            else:
                pk += 2 * dx
            x_list.append(x1)
            y_list.append(y1)

    return x_list, y_list


@app.function
def Midpoint_circle(centre, radius):
    cx, cy = centre
    x = 0
    y = radius
    d = 1 - radius

    xl, yl = [], []

    while x <= y:
        # All 8 symmetric octants centered strictly at (cx, cy)
        xl.extend(
            [
                cx + x,
                cx - x,
                cx + x,
                cx - x,
                cx + y,
                cx - y,
                cx + y,
                cx - y,
            ]
        )
        yl.extend(
            [
                cy + y,
                cy + y,
                cy - y,
                cy - y,
                cy + x,
                cy + x,
                cy - x,
                cy - x,
            ]
        )

        x += 1
        if d < 0:
            d += 2 * x + 1
        else:
            y -= 1
            d += 2 * (x - y) + 1

    return xl, yl


@app.function
def Midpoint_ellipse(centre, radius_a, radius_b):
    cx, cy = centre
    a, b = radius_a, radius_b
    a_sq = a**2
    b_sq = b**2

    x, y = 0, b
    x_list, y_list = [], []

    dx = 2 * b_sq * x
    dy = 2 * a_sq * y

    # ----------------- REGION 1 -----------------
    d1 = b_sq - (a_sq * b) + (a_sq / 4)

    while dx < dy:
        x_list.extend([cx + x, cx - x, cx + x, cx - x])
        y_list.extend([cy + y, cy + y, cy - y, cy - y])

        x += 1
        dx += 2 * b_sq
        if d1 < 0:
            d1 += dx + b_sq
        else:
            y -= 1
            dy -= 2 * a_sq
            d1 += dx - dy + b_sq

    # ----------------- REGION 2 -----------------
    d2 = (b_sq * (x + 1 / 2) ** 2) + (a_sq * (y - 1) ** 2) - (a_sq * b_sq)

    while y >= 0:
        x_list.extend([cx + x, cx - x, cx + x, cx - x])
        y_list.extend([cy + y, cy + y, cy - y, cy - y])

        y -= 1
        dy -= 2 * a_sq
        if d2 > 0:
            d2 += a_sq - dy
        else:
            x += 1
            dx += 2 * b_sq
            d2 += dx - dy + a_sq

    return x_list, y_list


@app.cell
def _():
    line = Bresenhams_line((30, 230), (190, 70))
    return (line,)


@app.cell
def _(line):
    # print the points
    print(line[0], line[1], sep="\n")
    return


@app.cell
def _():
    circle1 = Midpoint_circle(centre=(90, 250), radius=35)
    circle2 = Midpoint_circle((205, 95), radius=25)
    return circle1, circle2


@app.cell
def _(circle1, circle2):
    print(circle1[0], circle1[1], sep="\n")
    print(circle2[0], circle2[1], sep="\n")
    return


@app.cell
def _():
    el1 = Midpoint_ellipse(centre=(90, 155), radius_a=45, radius_b=60)
    el2 = Midpoint_ellipse(centre=(150, 45), radius_a=45, radius_b=25)
    return el1, el2


@app.cell
def _(el1, el2):
    print(el1[0], el1[1], sep="\n")
    print(el2[0], el2[1], sep="\n")
    return


@app.cell
def _(circle1, circle2, el1, el2, line, plt):
    plt.scatter(circle1[0], circle1[1], s=0.2)
    plt.scatter(circle2[0], circle2[1], s=0.2)
    plt.scatter(line[0], line[1], s=0.2)
    plt.scatter(el1[0], el1[1], s=0.2)
    plt.scatter(el2[0], el2[1], s=0.2)

    plt.axis("equal")
    plt.savefig("out.png")
    plt.show()
    return


@app.cell
def _():
    return


if __name__ == "__main__":
    app.run()
