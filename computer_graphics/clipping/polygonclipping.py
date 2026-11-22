# /// script
# requires-python = ">=3.14"
# dependencies = [
#     "marimo>=0.23.3",
#     "matplotlib>=3.11.2",
#     "numpy>=2.5.5",
# ]
# ///

import marimo

__generated_with = "0.25.2"
app = marimo.App()


@app.cell
def _():
    import numpy as np
    import matplotlib.pyplot as plt

    return (plt,)


@app.cell
def _():
    # define the sides / window edges
    class WindowEdges:
        # static class for defining  region bits
        TOP = 0b1000
        BOTTOM = 0b0100
        RIGHT = 0b0010
        LEFT = 0b0001


    class Point:
        def __init__(self, x, y):
            self.x = x
            self.y = y

        def __repr__(self):
            return f"({self.x:g},{self.y:g})"


    class Line:
        def __init__(self, start: Point, end: Point):
            self.start = start
            self.end = end

        def __repr__(self):
            return f"Edge:{self.start}->{self.end}"


    class Polygon:
        def __init__(self, vertices: list[Point]):
            self.vertices = vertices
            self.edges = [
                Line(vertices[i], vertices[(i + 1) % len(vertices)])
                for i in range(len(vertices))
            ]

        def __repr__(self):
            return f"Polygon(\n\tvertices = {self.vertices}, \n\tedges = {self.edges}\n)"


    class ViewWindow:
        def __init__(self, lower, higher):
            self.Xmin, self.Ymin = lower
            self.Xmax, self.Ymax = higher

        def __repr__(self):
            return f"ViewWindow (Xmin={self.Xmin}, Ymin={self.Ymin}, Xmax={self.Xmax}, Ymax={self.Ymax})"

    return Line, Point, Polygon, ViewWindow, WindowEdges


@app.cell
def _(Polygon, ViewWindow, plt):
    def draw_polygon(pol: Polygon, window: ViewWindow, ax=None, title=""):
        if ax is None:
            ax = plt.gca()

        ax.fill(
            [window.Xmin, window.Xmin, window.Xmax, window.Xmax, window.Xmin],
            [window.Ymin, window.Ymax, window.Ymax, window.Ymin, window.Ymin],
            color="orange",
            alpha=0.3,
        )

        if pol.vertices:
            xs = [p.x for p in pol.vertices] + [pol.vertices[0].x]
            ys = [p.y for p in pol.vertices] + [pol.vertices[0].y]
            ax.plot(xs, ys, "-o")

        ax.set_aspect("equal", adjustable="box")
        ax.set_title(title)

    return (draw_polygon,)


@app.cell
def _():
    # define the vertwx point structure for polygon
    # it can be defined like set of vertices and edge

    # struct {
    #   vertices =[v1,v2,v3],
    #   edges =[(v1,v2),(v2,v3),(v3,v1)]  # the form of closed polygon..
    # }
    return


@app.cell
def _(Line, Point, Polygon, ViewWindow, WindowEdges):
    def get_region_code(point: Point, window: ViewWindow):
        # T B R L format
        code = 0b0000  # is_inside
        # top
        if point.y > window.Ymax:
            code |= WindowEdges.TOP
        # bottom
        if point.y < window.Ymin:
            code |= WindowEdges.BOTTOM
        # right
        if point.x > window.Xmax:
            code |= WindowEdges.RIGHT
        # left
        if point.x < window.Xmin:
            code |= WindowEdges.LEFT
        return code


    def intersection(edge, edgecode, viewindow):
        dx = edge.end.x - edge.start.x
        dy = edge.end.y - edge.start.y

        if edgecode == WindowEdges.LEFT:
            if dx == 0:
                return None
            x = viewindow.Xmin
            y = edge.start.y + (viewindow.Xmin - edge.start.x) * (dy / dx)

        if edgecode == WindowEdges.RIGHT:
            if dx == 0:
                return None
            x = viewindow.Xmax
            y = edge.start.y + (viewindow.Xmax - edge.start.x) * (dy / dx)

        if edgecode == WindowEdges.BOTTOM:
            if dy == 0:
                return None
            x = edge.start.x + (viewindow.Ymin - edge.start.y) / dy * dx
            y = viewindow.Ymin

        if edgecode == WindowEdges.TOP:
            if dy == 0:
                return None
            x = edge.start.x + (viewindow.Ymax - edge.start.y) / dy * dx
            y = viewindow.Ymax

        return Point(x, y)


    def clip_polygon_against_windowedge(
        edges: list[Line], edgecode: int, viewindow: ViewWindow
    ):
        updated_vertices: list[Point] = []

        def is_inside(point: Point):
            return (get_region_code(point, viewindow) & edgecode) == 0

        for edge in edges:
            # start outside but end inside
            if is_inside(edge.end):
                if not is_inside(edge.start):
                    intersection_point = intersection(edge, edgecode, viewindow)
                    if intersection_point is not None:
                        updated_vertices.append(intersection_point)

                updated_vertices.append(edge.end)

            # start inside end outside
            elif is_inside(edge.start):
                intersection_point = intersection(edge, edgecode, viewindow)
                if intersection_point is not None:
                    updated_vertices.append(intersection_point)

            # else no change to vertices

        return Polygon(updated_vertices)

    return (clip_polygon_against_windowedge,)


@app.cell
def _(Point, Polygon, ViewWindow, WindowEdges):
    # clipping window
    window = ViewWindow((50, 50), (200, 150))

    # define points and run clipping
    # roll 213 => a=1,b=3
    a, b = 1, 3

    polygons = {
        "Q1": Polygon([Point(80, 70), Point(150, 70), Point(115, 130)]),
        "Q2": Polygon([Point(20, 20), Point(250, 20), Point(135, 200)]),
        "Q3": Polygon(
            [
                Point(140 + a, 20 + b),
                Point(230 + a, 20 + b),
                Point(230 + a, 110 + b),
                Point(140 + a, 110 + b),
            ]
        ),
    }

    codes = [WindowEdges.LEFT, WindowEdges.RIGHT, WindowEdges.BOTTOM, WindowEdges.TOP]
    return codes, polygons, window


@app.cell
def _(
    clip_polygon_against_windowedge,
    codes,
    draw_polygon,
    plt,
    polygons,
    window,
):
    figures = []
    for polygon_id, original_polygon in polygons.items():
        print(f"\n\nProcessing polygon {polygon_id}", flush=True)
        stages = [("Original", original_polygon)]
        clipped_polygon = original_polygon

        for which_edge, edge_name in zip(codes, ["left", "right", "bottom", "top"]):
            # PERFORM THE CLIPPING......
            clipped_polygon = clip_polygon_against_windowedge(
                clipped_polygon.edges, which_edge, window
            )
            print(f"After {edge_name} clipping:\n{clipped_polygon}", flush=True)
            stages.append((f"After {edge_name} clipping", clipped_polygon))

        fig, axes = plt.subplots(1, len(stages), figsize=(18, 4))

        for ax, (title, stage_polygon) in zip(axes, stages):
            draw_polygon(stage_polygon, window, ax=ax, title=title)

        plt.axis("equal")
        fig.tight_layout()
        fig.savefig(f"Polygon{polygon_id}.png")
        figures.append(fig)
    # plt.show()
    return (figures,)


@app.cell
def _(figures):
    figures
    return


if __name__ == "__main__":
    app.run()
