//データ構造テスト用
#include <stdio.h>
#define inf 1e9

int main()
{
    int i, j, k;
    int N, M;
    printf("入力：頂点数、辺の数\n");
    scanf("%d%d", &N, &M);
    int d[N][N];
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            d[i][j] = inf;
        }
    }
    for (i = 0; i < N; i++)
        d[i][i] = 0;

    printf("入力：頂点、頂点、距離\n");
    for (i = 0; i < M; i++)
    {
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        a--;
        b--;
        d[a][b] = c;
        d[b][a] = c;
    }
    printf("\n");

    printf("k=0のとき\n");
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            printf("%d ", d[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    for (k = 0; k < N; k++)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (d[i][k] + d[k][j] < d[i][j])
                {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
        printf("k=%dのとき\n", k + 1);
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < N; j++)
            {
                if (d[i][j] == inf)
                {
                    printf("inf ");
                }
                else
                    printf("%d ", d[i][j]);
            }
            printf("\n");
        }
        printf("\n");
    }
}