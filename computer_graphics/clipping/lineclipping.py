# /// script
# requires-python = ">=3.13"
# dependencies = [
#     "marimo>=0.23.3",
#     "matplotlib>=3.11.2",
# ]
# ///

import marimo

__generated_with = "0.25.2"
app = marimo.App()


@app.cell
def _():
    import matplotlib
    import matplotlib.pyplot as plt

    matplotlib.use("TKAgg")
    return (plt,)


@app.cell
def _():
    class Point:
        def __init__(self, x, y):
            self.x = x
            self.y = y

        def __repr__(self):
            return f"({self.x}, {self.y})"


    class Line:
        def __init__(self, start: Point, end: Point):
            self.start = start
            self.end = end

        def __repr__(self):
            return f"Line : from {self.start} to {self.end}"


    class ViewWindow:
        def __init__(self, lower, higher):
            self.Xmin, self.Ymin = lower
            self.Xmax, self.Ymax = higher

        def __repr__(self):
            return f"ViewWindow (Xmin={self.Xmin}, Ymin={self.Ymin}, Xmax={self.Xmax}, Ymax={self.Ymax})"


    class RegionBits:
        # static class for defining  region bits
        TOP = 0b1000
        BOTTOM = 0b0100
        RIGHT = 0b0010
        LEFT = 0b0001


    return Line, Point, RegionBits, ViewWindow


@app.cell
def _(plt):
    # def plot_line_and_window(
    #     window: ViewWindow, line: Line, clipline: Line | None, name="figure", save=False
    # ):
    #     plt.axis("equal")
    #     plt.title(name)
    #     plt.plot(
    #         [window.Xmin, window.Xmin, window.Xmax, window.Xmax, window.Xmin],
    #         [window.Ymin, window.Ymax, window.Ymax, window.Ymin, window.Ymin],
    #     )
    #     plt.plot([line.start.x, line.end.x], [line.start.y, line.end.y])
    #     if clipline is not None:
    #         plt.plot([clipline.start.x, clipline.end.x], [clipline.start.y, clipline.end.y])
    #     if save:
    #         plt.savefig(f"{name}.png")
    #     # return plt.gca()
    #     return plt.show()


    def plot_line_and_window(window, line, clipline=None, name="figure", save=False):
        fig, axes = plt.subplots(1, 2, figsize=(10, 4))
        fig.suptitle(name)
        plt.axis("equal")

        for ax, ln, title in [(axes[0], line, "Original"), (axes[1], clipline, "Clipped")]:
            ax.set_aspect("equal")
            ax.set_title(title)
            ax.fill(
                [window.Xmin, window.Xmin, window.Xmax, window.Xmax, window.Xmin],
                [window.Ymin, window.Ymax, window.Ymax, window.Ymin, window.Ymin],
                color="orange",
                alpha=0.3,
            )
            if ln is not None:
                ax.plot([ln.start.x, ln.end.x], [ln.start.y, ln.end.y])
        if save:
            plt.savefig(f"{name}.png")
        plt.show()


    return (plot_line_and_window,)


@app.cell
def _(Line, Point, RegionBits, ViewWindow):
    def set_encode(point: Point, window: ViewWindow):
        # T B R L format
        code = 0b0000  # inside

        # top
        if point.y > window.Ymax:
            code |= RegionBits.TOP
        # bottom
        if point.y < window.Ymin:
            code |= RegionBits.BOTTOM
        # right
        if point.x > window.Xmax:
            code |= RegionBits.RIGHT
        # left
        if point.x < window.Xmin:
            code |= RegionBits.LEFT

        return code


    def cut_intersect_point(line: Line, view: ViewWindow, ecode):
        dx = line.end.x - line.start.x
        dy = line.end.y - line.start.y
        x, y = 0, 0

        if dx == 0:  # Handelling the Negative Slope
            x = line.start.x
            if ecode == RegionBits.TOP:
                y = view.Ymax
            elif ecode == RegionBits.BOTTOM:
                y = view.Ymin
            else:
                y = line.start.y
            return Point(x, y)
        else:
            slope = dy / dx

            if ecode & RegionBits.TOP:
                print(
                    f"if any code is top 1000:: x'= xstart + 1/m * (Ymax - ystart), y'= Ymax"
                    f" --> x'= {line.start.x}+1/{slope}*({view.Ymax}-{line.start.y}), y'= {view.Ymax}"
                )
                y = view.Ymax
                x = line.start.x + (view.Ymax - line.start.y) / slope

            elif ecode & RegionBits.BOTTOM:
                print(
                    f"if any code is bottom 0100:: x'= xstart + 1/m * (Ymin - ystart), y'= Ymin"
                    f" --> x'= {line.start.x}+1/{slope}*({view.Ymin}-{line.start.y}), y'= {view.Ymin}"
                )
                y = view.Ymin
                x = line.start.x + (view.Ymin - line.start.y) / slope

            elif ecode & RegionBits.RIGHT:
                print(
                    f"if any code is right 0010:: x'= Xmax, y'= ystart + m * (Xmax - xstart)"
                    f" --> x'= {view.Xmax}, y'= {line.start.y}+{slope}*({view.Xmax}-{line.start.x})"
                )
                x = view.Xmax
                y = line.start.y + slope * (view.Xmax - line.start.x)

            elif ecode & RegionBits.LEFT:
                print(
                    f"if any code is left 0001:: x'= Xmin, y'= ystart + m * (Xmin - xstart)"
                    f" --> x'= {view.Xmin}, y'= {line.start.y}+{slope}*({view.Xmin}-{line.start.x})"
                )
                x = view.Xmin
                y = line.start.y + slope * (view.Xmin - line.start.x)

        return Point(x, y)


    def do_clipping(line: Line, view: ViewWindow):
        ecode1 = set_encode(line.start, view)
        ecode2 = set_encode(line.end, view)
        print(f"RegionCode for start={ecode1:04b}, for end={ecode2:04b}")

        while True:
            if (ecode1 | ecode2) == 0:
                print("fully inside viewpoint")
                return line
            elif (ecode1 & ecode2) != 0:
                print("completely outside")
                return None
            else:
                if ecode1 != 0:
                    print(f"---Cutting the start point:: has code {ecode1:04b}")
                    newstart = cut_intersect_point(line, view, ecode1)
                    line = Line(newstart, line.end)
                    ecode1 = set_encode(line.start, view)
                else:
                    print(f"---Cutting the end point:: has code {ecode2:04b}")
                    newend = cut_intersect_point(line, view, ecode2)
                    line = Line(line.start, newend)
                    ecode2 = set_encode(line.end, view)


    return (do_clipping,)


@app.cell
def _(Line, Point, ViewWindow, do_clipping, plot_line_and_window):
    if __name__ == "__main__":
        view = ViewWindow((50, 50), (200, 150))

        lines = {
            "Line 1": Line(Point(140, 70), Point(185, 130)),
            "Line 2": Line(Point(10, 165), Point(40, 190)),
            "Line 3": Line(Point(20, 125), Point(250, 125)),
            "Line 4": Line(Point(80, 20), Point(80, 180)),
            "Line 5": Line(Point(20, 20), Point(150, 200)),
            # roll = 13 so a=1,b=3 => Line L6 : from (40 + a, 20) to (190 − b, 180)
            "Line 6": Line(Point(40 + 1, 20), Point(190 - 3, 180)),
        }

        print(view)
        for name, line in lines.items():
            print("\n", name, line, "\n")
            clipped_line = do_clipping(line, view)
            if clipped_line is None:
                plot_line_and_window(view, line, clipline=None, name=name, save=True)
            else:
                plot_line_and_window(view, line, clipped_line, name, True)
            print("AFTER CLIPPING: ", clipped_line)
    return


@app.cell
def _():
    return


if __name__ == "__main__":
    app.run()
