//4619055 辰川力駆　課題3
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int *point;
    double ave = 0;
    int n;
    printf("受験者の人数を入力してください\n");
    scanf("%d", &n);
    point = (int *)malloc(n * sizeof(int));
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d人目の点数を入力してください\n", i + 1);
        scanf("%d", &point[i]);
        ave += point[i];
    }
    ave /= n;
    printf("%d人の平均点は%gです\n", n, ave);
    for (i = 0; i < n; i++)
    {
        printf("%d人目の点数は%dです\n", i + 1, point[i]);
    }
    free(point);
    return 0;
}