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

    return mo, np, plt


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
    print(f"Line Points: {len(line[0])}\n", ",".join(str(p) for p in zip(line[0], line[1])))
    return


@app.cell
def _():
    circle1 = Midpoint_circle(centre=(90, 250), radius=35)
    circle2 = Midpoint_circle((205, 95), radius=25)
    return circle1, circle2


@app.cell
def _(circle1, circle2):
    print(f"Circle 1 Points: {len(circle1[0])}\n", ",".join(str(p) for p in zip(circle1[0], circle1[1])))
    print(f"Circle 2 Points: {len(circle2[0])}\n", ",".join(str(p) for p in zip(circle2[0], circle2[1])))
    return


@app.cell
def _():
    el1 = Midpoint_ellipse(centre=(90, 155), radius_a=45, radius_b=60)
    el2 = Midpoint_ellipse(centre=(150, 45), radius_a=45, radius_b=25)
    return el1, el2


@app.cell
def _(el1, el2):
    print(f"Ellipse 1 Points: {len(el1[0])}\n", ",".join(str(p) for p in zip(el1[0], el1[1])))
    print(f"Ellipse 2 Points: {len(el2[0])}\n", ",".join(str(p) for p in zip(el2[0], el2[1])))
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
    # shifted face
    circle1_s = Midpoint_circle(centre=(90, 250), radius=35 + 3)

    print(
        f"Circle 1 Points after radius change: {len(circle1_s[0])}\n",
        ",".join(str(p) for p in zip(circle1_s[0], circle1_s[1])),
    )

    return (circle1_s,)


@app.cell
def _(get_mirror_translate):
    ## Aditional decoration ...

    h1 = Bresenhams_line((25, 240), (50, 180))
    h2 = Bresenhams_line((0, 225), (50, 175))
    h3 = Bresenhams_line((-10, 200), (50, 170))
    h4 = Bresenhams_line((-15, 180), (50, 165))
    h5 = Bresenhams_line((-10, 150), (50, 160))

    h6 = Bresenhams_line((130, 190), (100, 150))
    h7 = get_mirror_translate(h2, shift=(180, 0))
    h8 = get_mirror_translate(h3, shift=(180, 0))
    h9 = get_mirror_translate(h4, shift=(180, 0))
    h10 = get_mirror_translate(h5, shift=(180, 0))

    mh1=Bresenhams_line((150,70),(175,100))
    mh2=Bresenhams_line((190,40),(230,25))
    return h1, h10, h2, h3, h4, h5, h6, h7, h8, h9, mh1, mh2


@app.cell
def _(
    circle1_s,
    circle2,
    el1,
    el2,
    h1,
    h10,
    h2,
    h3,
    h4,
    h5,
    h6,
    h7,
    h8,
    h9,
    line,
    mh1,
    mh2,
    plt,
):
    plt.scatter(circle1_s[0], circle1_s[1], s=0.2)
    plt.scatter(circle2[0], circle2[1], s=0.2)
    plt.scatter(line[0], line[1], s=0.2)
    plt.scatter(el1[0], el1[1], s=0.2)
    plt.scatter(el2[0], el2[1], s=0.2)
    plt.scatter(h1[0], h1[1], s=0.2)
    plt.scatter(h2[0], h2[1], s=0.2)
    plt.scatter(h3[0], h3[1], s=0.2)
    plt.scatter(h4[0], h4[1], s=0.2)
    plt.scatter(h5[0], h5[1], s=0.2)
    plt.scatter(h6[0], h6[1], s=0.2)
    plt.scatter(h7[0], h7[1], s=0.2)
    plt.scatter(h8[0], h8[1], s=0.2)
    plt.scatter(h9[0], h9[1], s=0.2)
    plt.scatter(h10[0], h10[1], s=0.2)

    plt.scatter(mh1[0], mh1[1], s=0.2)
    plt.scatter(mh2[0], mh2[1], s=0.2)

    plt.axis("equal")
    plt.savefig("out2.png")
    plt.show()
    return


@app.cell
def _(np):
    # transformation matrxix for reflct along y axis and shift position
    # points  are in xlist,ylist -> 2xn matrix
    # matrix multiplication 2x2,2xn => 2xn
    # for homogeneous (xlist,ylist,hlist) -> 3xn matrix ==> 3x3,3xn -> 3xn output ==> 2xn output


    def get_mirror_translate(points_matrix, shift):
        points_matrix = np.array(points_matrix)
        x, y = shift
        h_cord = np.vstack([points_matrix, np.ones(points_matrix.shape[1])])
        mat = np.array(
            [
                [-1, 0, x],
                [0, 1, y],
                [0, 0, 1],
            ]
        )
        return np.dot(mat, h_cord)

    return (get_mirror_translate,)


if __name__ == "__main__":
    app.run()
