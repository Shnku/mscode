#include <stdio.h>
#include <time.h>

void midpoint_circle(int r, int xc, int yc) {
    int x, y, p;
    x = 0;
    y = r;
    p = 1 - r;
    int iter = 0;
    while (x <= y) {
        iter++;
        printf("(%d,%d), ", (xc + x), (yc + y));
        printf("(%d,%d), ", (xc + y), (yc + x));

        printf("(%d,%d), ", (xc + x), (yc - y));
        printf("(%d,%d), ", (xc + y), (yc - x));

        printf("(%d,%d), ", (xc - x), (yc - y));
        printf("(%d,%d), ", (xc - y), (yc - x));

        printf("(%d,%d), ", (xc - x), (yc + y));
        printf("(%d,%d), ", (xc - y), (yc + x));

        printf("\n");
        x++;
        if (p > 0) {
            y = y - 1;
            p = p + (2 * x) - (2 * y) + 1;
        } else {
            p = p + (2 * x) + 1;
        }
    }
    printf("NO of iter: %d\n", iter);
}

void simulate(int r, int xc, int yc) {
    clock_t start, end;

    start = clock();
    midpoint_circle(r, xc, yc);
    end = clock();

    printf("\nexecution time: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);
}

int main() {
    printf("=== Midpoint Circle Test Cases ===\n\n");

    printf("midpoint_circle>Case 1: Centre=(100,100), r=10 - Small circle\n");
    simulate(10, 100, 100);

    printf(
        "\nmidpoint_circle>Case 2: Centre=(100,100), r=25 - Medium circle\n");
    simulate(25, 100, 100);

    printf("\nmidpoint_circle>Case 3: Centre=(150,150), r=50 - Large circle\n");
    simulate(50, 150, 150);

    printf("\nmidpoint_circle>Case 4: Centre=(0,0), r=8 - Centre at origin\n");
    simulate(8, 0, 0);

    printf(
        "\nmidpoint_circle>Case 5: Centre=(200,200), r=100 - Very large "
        "circle\n");
    simulate(100, 200, 200);

    printf(
        "\nmidpoint_circle>Case 6: Centre=(100,100), r=3 - Very small "
        "radius\n");
    simulate(3, 100, 100);
}
