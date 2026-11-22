# /// script
# requires-python = ">=3.15"
# dependencies = [
#     "marimo>=0.23.3",
#     "matplotlib>=3.11.2",
#     "numpy>=2.5.5",
# ]
# ///

import marimo

__generated_with = "0.25.1"
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
            return f"({self.x},{self.y})"


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
    def draw_polygon(pol: Polygon, window: ViewWindow):
        plt.plot(
            [i.x for i in pol.vertices] + [pol.vertices[0].x],
            [i.y for i in pol.vertices] + [pol.vertices[0].y],
            "-o",
        )
        plt.fill(
            [window.Xmin, window.Xmin, window.Xmax, window.Xmax, window.Xmin],
            [window.Ymin, window.Ymax, window.Ymax, window.Ymin, window.Ymin],
            color="orange",
            alpha=0.3,
        )
        plt.show()


    return (draw_polygon,)


@app.cell
def _(draw_polygon, pol, view):
    draw_polygon(pol, view)
    return


@app.cell
def _(Point, Polygon):
    pol = Polygon([Point(100, 20), Point(190, 140), Point(30, 140)])
    pol
    return (pol,)


@app.cell
def _(ViewWindow):
    view = ViewWindow((50, 50), (200, 150))
    view
    return (view,)


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
def _(Line, Point, ViewWindow, WindowEdges):
    def get_region_code(point: Point, window: ViewWindow):
        # T B R L format
        code = 0b0000  # inside
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
            t = (viewindow.Xmin - edge.start.x) / dx
            return Point(viewindow.Xmin, edge.start.y + t * dy)

        if edgecode == WindowEdges.RIGHT:
            if dx == 0:
                return None
            t = (viewindow.Xmax - edge.start.x) / dx
            return Point(viewindow.Xmax, edge.start.y + t * dy)

        if edgecode == WindowEdges.BOTTOM:
            if dy == 0:
                return None
            t = (viewindow.Ymin - edge.start.y) / dy
            return Point(edge.start.x + t * dx, viewindow.Ymin)

        if edgecode == WindowEdges.TOP:
            if dy == 0:
                return None
            t = (viewindow.Ymax - edge.start.y) / dy
            return Point(edge.start.x + t * dx, viewindow.Ymax)


    def clip_polygon(
        vertices: list[Point], edgecode: int, viewindow: ViewWindow
    ) -> list[Point]:
        if not vertices:
            return []

        updated_vertices = []

        def inside(point: Point) -> bool:
            return (get_region_code(point, viewindow) & edgecode) == 0

        previous = vertices[-1]
        previous_inside = inside(previous)

        for current in vertices:
            current_inside = inside(current)

            if current_inside:
                if not previous_inside:
                    intersection_point = intersection(
                        Line(previous, current), edgecode, viewindow
                    )
                    if intersection_point is not None:
                        updated_vertices.append(intersection_point)

                updated_vertices.append(current)

            elif previous_inside:
                intersection_point = intersection(
                    Line(previous, current), edgecode, viewindow
                )
                if intersection_point is not None:
                    updated_vertices.append(intersection_point)

            previous = current
            previous_inside = current_inside

        return updated_vertices


    return (clip_polygon,)


@app.cell
def _(WindowEdges, clip_polygon, pol, view):
    new_vertices = clip_polygon(pol.vertices, WindowEdges.LEFT, view)
    print(new_vertices)
    return (new_vertices,)


@app.cell
def _(Polygon, draw_polygon, new_vertices, view):
    draw_polygon(Polygon(new_vertices), view)
    return


@app.cell
def _(WindowEdges, clip_polygon, pol, view):
    new_vertices1 = clip_polygon(pol.vertices, WindowEdges.BOTTOM, view)
    print(new_vertices1)

    return (new_vertices1,)


@app.cell
def _(Polygon, draw_polygon, new_vertices1, view):
    draw_polygon(Polygon(new_vertices1), view)
    return


@app.cell
def _():
    return


@app.cell
def _():
    return


if __name__ == "__main__":
    app.run()
