#include <stdio.h>
#include <string.h>

int starting = -1;
int ending = -1;
char ans_str[100];

int No_Vowel_Number(char str[]);

int No_Vowel_Number(char str[])
{
    char delim[] = "AEIOUaeiou0123456789";
    int size_delim = strlen(delim);
    int max = -1;
    int i = 0;
    while (str[i] != '\0')
    {
        int allowed = 1;
        for (int j = 0; j < size_delim; j++)
        {
            if (delim[j] == str[i])
            {
                allowed = 0;
                break;
            }
        }
        if (allowed)
        {
            int temp_starting = i;
            while (str[i] != '\0')
            {
                int inner_allowed = 1;
                for (int j = 0; j < size_delim; j++)
                {
                    if (delim[j] == str[i])
                    {
                        inner_allowed = 0;
                        break;
                    }
                }
                if (inner_allowed)
                {
                    i++;
                }
                else
                {

                    if (max <= (i - 1 - temp_starting))
                    {
                        starting = temp_starting;
                        ending = i - 1;
                        max = ending - starting;
                    }

                    break;
                }
            }
            if (str[i] == '\0')
            {
                if (max <= (i - 1 - temp_starting))
                {
                    starting = temp_starting;
                    ending = i - 1;
                    max = ending - starting;
                }
            }
        }
        else
        {
            i++;
        }
    }
    if (starting != -1)
    {
        int str_starting = starting;
        int c;
        for (c = 0; c <= ending - starting; c++)
        {
            ans_str[c] = str[str_starting];
            str_starting++;
        }
        ans_str[c] = '\0';
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    char str[1001];
    fgets(str, 1000, stdin);
    str[strlen(str) - 1] = '\0';

    int ans = No_Vowel_Number(str);
    if (ans)
    {
        printf("%s", ans_str);
    }
    else
    {
        printf("No Substring");
    }

    return 0;
}