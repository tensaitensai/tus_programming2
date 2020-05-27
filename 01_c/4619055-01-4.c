//4619055 辰川力駆　課題4
#include <stdio.h>

void square(double *n)
{
    int i;
    for (i = 0; i < 6; i++)
        n[i] *= n[i];
}

int main()
{
    double n[6];
    int i;
    printf("二乗したい数字を6つ入力してください\n");
    for (i = 0; i < 6; i++)
        scanf("%lf", &n[i]);
    square(n);
    printf("二乗したよ\n");
    for (i = 0; i < 6; i++)
        printf("%g\n", n[i]);
    return 0;
}