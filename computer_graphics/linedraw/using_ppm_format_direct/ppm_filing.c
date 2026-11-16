#include <stdio.h>

int main() {
    FILE* fp = NULL;
    int height = 300;
    int width = 300;
    if (!(fp = fopen("demo.ppm", "wb"))) {
        printf("cant get file");
    }
    // PPM header: magic number, width/height, maximum color value
    fprintf(fp, "P6\n");
    fprintf(fp, "%d %d\n", width, height);
    fprintf(fp, "255\n");

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            // fputc(0xff, fp); fputc(0x00, fp); fputc(0x00, fp);
            if (x % 2 == 0 && y % 2 == 0)
                fprintf(fp, "%c%c%c", 0x33, 0x00, 0x00);
            else if (y % 2 == 0)
                fprintf(fp, "%c%c%c", 0x00, 0x44, 0x00);
            else if (x % 2 == 0)
                fprintf(fp, "%c%c%c", 0x00, 0x00, 0x55);
            else
                fprintf(fp, "%c%c%c", 0x00, 0x00, 0x00);
        }
    }
    fclose(fp);
    return 0;
}