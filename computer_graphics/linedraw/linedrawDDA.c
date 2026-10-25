#include <stdio.h>
#include <time.h>

typedef struct points {
  int x;
  int y;
} point;

#define SIZE 200
point arr[SIZE];

void lineDDA(point p1, point p2) {
  int dx = p2.x - p1.x;
  int dy = p2.y - p1.y;
  int x = p1.x;
  int y = p1.y;
  float m = (float)dy / (float)dx;

  arr[0].x = x, arr[0].y = y;
  if (m < 1) {
    for (int i = 1; i <= dx; i++) {
      y += m;
      x++;
      arr[i].x = x;
      arr[i].y = (int)y;
    }
  } else {
    for (int i = 1; i <= dy; i++) {
      x += (1 / m);
      y++;
      arr[i].x = (int)x;
      arr[i].y = y;
    }
  }
}

void print_points(point p[]) {
  for (int i = 0; i < SIZE; i++) {
    if (arr[i].x == -1 && arr[i].y == -1)
      break;
    printf("(%d,%d), ", arr[i].x, arr[i].y);
  }
}

void init_points(point p[]) {
  for (int i = 0; i < SIZE; i++)
    p[i].x = -1, p[i].y = -1;
}

void simulate(point p1, point p2) {
  clock_t start, end;

  init_points(arr);

  start = clock();
  lineDDA(p1, p2);
  end = clock();

  print_points(arr);
  printf("\nexecution time: %f", ((double)(end - start)) / CLOCKS_PER_SEC);
}

int main() {
  simulate((point){2, 3}, (point){45, 56});

  return 0;
}
