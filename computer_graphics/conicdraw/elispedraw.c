#include <stdio.h>
#include <time.h>

#include "draw.h"
// #define SQR(X) (X * X)
#define SQR(X) ((X) * (X))

void midpoint_eclipse(int a, int b, int cx, int cy) {
    int x = 0, y = b;
    int a_sq = SQR(a);
    int b_sq = SQR(b);
    // int two_a_sq_y = 2 * a_sq * y;
    // int two_b_sq_x = 2 * b_sq * x;

    // int r1 = b_sq + SQR(a << 2) - a_sq * b;
    int r1 = b_sq + a_sq / 4 - a_sq * b;

    while (2 * a_sq * y > 2 * b_sq * x) {
        printf("(%d,%d), ", cx + x, cy + y);
        printf("(%d,%d), ", cx + x, cy - y);
        printf("(%d,%d), ", cx - x, cy + y);
        printf("(%d,%d), ", cx - x, cy - y);
        printf("\n");

        if (r1 > 0) {
            y = y - 1;
            r1 = r1 - 2 * a_sq * y;
        }
        x = x + 1;
        r1 = r1 + 2 * b_sq * x + b_sq;
    }

    int r2 = b_sq * SQR(x + 0.5) + a_sq * SQR(y - 1) - a_sq * b_sq;

    while (y >= 0) {
        printf("(%d,%d), ", cx + x, cy + y);
        printf("(%d,%d), ", cx + x, cy - y);
        printf("(%d,%d), ", cx - x, cy + y);
        printf("(%d,%d), ", cx - x, cy - y);
        printf("\n");

        if (r2 <= 0) {
            x = x + 1;
            r2 = r2 + 2 * b_sq * x;
        }
        y = y - 1;
        r2 = r2 - 2 * a_sq * y + a_sq;
    }
}

void simulate(int a, int b, int cx, int cy) {
    clock_t start, end;

    start = clock();
    midpoint_eclipse(a, b, cx, cy);
    end = clock();

    printf("\nexecution time: %f\n", ((double)(end - start)) / CLOCKS_PER_SEC);
}

int main() {
    printf("=== Midpoint Ellipse Test Cases ===\n\n");

    printf("Case 1: Centre=(100,100), rx=40, ry=25\n");
    simulate(40, 25, 100, 100);

    printf("\nCase 2: Centre=(100,100), rx=25, ry=40\n");
    simulate(25, 40, 100, 100);

    printf("\nCase 3: Centre=(100,100), rx=25, ry=25\n");
    simulate(25, 25, 100, 100);

    printf("\nCase 4: Centre=(150,150), rx=60, ry=20\n");
    simulate(60, 20, 150, 150);

    printf("\nCase 5: Centre=(200,150), rx=15, ry=10\n");
    simulate(15, 10, 200, 150);
    return 0;
}
