#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int x;
    int y;
} point;

#define SIZE 300

point arr[SIZE];

int lineDDA(point p1, point p2) {
    int dx = p2.x - p1.x;
    int dy = p2.y - p1.y;

    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);

    if (steps >= SIZE) {
        fprintf(stderr, "Line is too long for arr\n");
        return 0;
    }

    float x_increment = (float)dx / steps;
    float y_increment = (float)dy / steps;

    float x = p1.x;
    float y = p1.y;

    for (int i = 0; i <= steps; i++) {
        arr[i].x = (int)roundf(x);
        arr[i].y = (int)roundf(y);

        x += x_increment;
        y += y_increment;
    }

    return steps + 1;
}

void print_points(point points[], int count) {
    for (int i = 0; i < count; i++) {
        printf("(%d,%d)", points[i].x, points[i].y);

        if (i < count - 1) {
            printf(", ");
        }
    }

    printf("\n");
}

void write_ppm_file(const char* filename, point points[], int point_count,
                    int width, int height) {
    // Three bytes per pixel: red, green, blue
    unsigned char* image = calloc(width * height * 3, sizeof(unsigned char));

    if (image == NULL) {
        perror("calloc");
        return;
    }

    // Set each DDA point to white
    for (int i = 0; i < point_count; i++) {
        int x = points[i].x;
        int y = points[i].y;

        if (x < 0 || x >= width || y < 0 || y >= height) {
            continue;
        }

        int index = (y * width + x) * 3;

        image[index + 0] = 255;  // red
        image[index + 1] = 255;  // green
        image[index + 2] = 255;  // blue
    }

    FILE* fp = fopen(filename, "wb");

    if (fp == NULL) {
        perror(filename);
        free(image);
        return;
    }

    // Correct P6 PPM header
    fprintf(fp, "P6\n%d %d\n255\n", width, height);

    // Write binary RGB pixel data
    fwrite(image, 3, width * height, fp);

    fclose(fp);
    free(image);
}

void simulate(point p1, point p2, const char* filename, int width, int height) {
    clock_t start = clock();

    int point_count = lineDDA(p1, p2);

    clock_t end = clock();

    print_points(arr, point_count);

    printf("execution time: %lf seconds\n",
           (double)(end - start) / CLOCKS_PER_SEC);

    write_ppm_file(filename, arr, point_count, width, height);
}

int main(void) {
    int width = 300;
    int height = 300;

    simulate((point){50, 50}, (point){200, 130}, "line1.ppm", width, height);

    simulate((point){50, 50}, (point){130, 200}, "line2.ppm", width, height);

    simulate((point){50, 100}, (point){250, 100}, "line3.ppm", width, height);

    simulate((point){150, 50}, (point){150, 250}, "line4.ppm", width, height);

    simulate((point){200, 50}, (point){50, 200}, "line5.ppm", width, height);

    simulate((point){50, 200}, (point){200, 50}, "line6.ppm", width, height);

    return 0;
}
