#include <stdio.h>
#include <stdlib.h>

void decode(char *str)
{
    int n = 0;
    while (*(str + n) != '\0')
    {
        n++;
    }
    int size_of_out = 0;
    for (int i = 0; i < n; i++)
    {
        if (*(str + i) >= 'a' && *(str + i) <= 'z')
        {
        }
        else
        {
            int t = 0;
            while (*(str + i) >= '0' && *(str + i) <= '9')
            {
                t = t * 10 + *(str + i) - '0';
                i++;
            }
            size_of_out = size_of_out + t;
        }
    }

    char *out = (char *)malloc((size_of_out + 1) * sizeof(char));
    int out_gone = 0;
    for (int i = 0; i < n; i++)
    {
        if (*(str + i) >= 'a' && *(str + i) <= 'z')
        {
            int t = 0;
            char x = *(str + i);
            i = i + 1;
            while (*(str + i) >= '0' && *(str + i) <= '9')
            {
                t = t * 10 + *(str + i) - '0';
                i++;
            }
            i--;
            for (int k = 0; k < t; k++)
            {
                *(out + out_gone) = x;
                out_gone++;
            }
        }
    }
    *(out + size_of_out) = '\0';
    printf("%s", out);
    free(out);
}

int main()
{
    char *str = (char *)malloc(100 * sizeof(char));

    scanf("%s", str);

    decode(str);

    free(str);

    return 0;
}