//4619055 辰川力駆　課題2
#include <stdio.h>
#include <stdlib.h>

int GetRandom(int min, int max)
{
    return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}

int main()
{
    int min = 0;
    int max = 99;
    FILE *fp;
    fp = fopen("rand.txt", "w");
    int a[100000];
    int i;
    for (i = 0; i < 100000; i++)
    {
        a[i] = GetRandom(min, max);
        fprintf(fp, "%d\n", a[i]);
    }
    fclose(fp);
    return 0;
}