#include <stdio.h>
#include <math.h>
int main()
{
    float x1, y1, x2, y2, r1, r2, diff;
    scanf("%f %f %f", &x1, &y1, &r1);
    scanf("%f %f %f", &x2, &y2, &r2);

    float d = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));

    if (d > (r1 + r2))
    {
        printf("Not intersecting");
    }
    else
    {
        if (r1 > r2)
        {
            diff = r1 - r2;
        }
        else
        {
            diff = r2 - r1;
        }
        if (d <= diff)
        {
            printf("Inside");
        }
        else
        {
            printf("Intersecting");
        }
    }
    return 0;
}