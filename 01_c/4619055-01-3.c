//4619055 辰川力駆　課題3
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void limit(double a, double *x)
{
    int i;
    for (i = 0; i < 100000; i++)
        x[i + 1] = a * x[i] * x[i] + 1;
    for (i = 100000; i < 100100; i++)
    {
        x[i + 1] = a * x[i] * x[i] + 1;
        if (fabs(x[i + 1] - x[i]) > fabs(x[i] - x[i - 1]))
        {
            printf("このa,x[0]では収束しません。\n");
            printf("終了します。\n");
            exit(0);
        }
    }
}

int main()
{
    double x[100100];
    double a;
    printf("x[n+1]=ax[n]^2+1について極限を求めます。aとx[0]を入力してください。\n");
    scanf("%lf %lf", &a, x[0]);
    limit(a, x);
    printf("%g\n", x[100100]);
    return 0;
}