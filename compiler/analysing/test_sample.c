#include <stdio.h>

// This is a single line comment
/*
   Multi-line block comment
   to test comment skipping
*/
int main()
{
    int a = 10;
    int b = 20;
    float sum = 0.0;

    if (a < b && b != 0)
    {
        a++;
        b -= 5;
        sum += a * b;
    }

    printf("Result sum: %f\n", sum);
    return 0;
}
