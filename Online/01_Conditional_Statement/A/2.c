#include <stdio.h>
#include <math.h>
int main()
{
    float a, b, c, x, y;
    scanf("%f %f %f", &a, &b, &c);
    float d;
    d = b * b - 4 * a * c;
    if (d == 0)
    {
        printf("Equal Solutions\n");
        x = (-1 * b) / (2 * a);
        printf("%.2f", x);
    }
    else
    {
        if (d > 0)
        {
            x = (-1 * b + sqrt(d)) / (2 * a);
            y = (-1 * b - sqrt(d)) / (2 * a);
            printf("Distinct Solutions\n");
            printf("%.2f,%.2f", x, y);
        }
        else
        {
            printf("Imaginary Solutions\n");
            x = (-1 * b) / (2 * a);
            y = sqrt((-1 * d)) / (2 * a);

            printf("(%.2f, %.2f), (%.2f, %.2f)", x, y, x, (-1 * y));
        }
    }
    return 0;
}