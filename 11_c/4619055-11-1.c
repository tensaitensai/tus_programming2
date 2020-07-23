//4619055 辰川力駆　課題1
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define maxN 50     /* 扱う頂点数の最大値，ここでは 50 に設定 */
#define inf 1000000 /* 無限大の値を十分大きな整数に設定 */

int minimumA(int *A, int N, int *d);

int main()
{
    int N, M;                           /* 頂点数，辺数 */
    int Adj[maxN][maxN];                /* 重み行列を表す変数 */
    int A[maxN];                        /* 集合 A の保持は 1 次元配列*/
    int d[maxN], p[maxN];               /* 配列変数 d, p */
    int v0;                             /* 始点の変数 */
    int i, u, v, len;                   /* 必要な変数を宣言 */
    char fname[128];                    /* 読み込むファイルの名前 */
    FILE *fp;                           /* 入力ファイル */
    printf("input filename: ");         /* ファイル名の入力を要求 */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);                      /* 128文字を超えた入力を標準入力から捨てる */
    fp = fopen(fname, "r");             /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d %d", &N, &M);        /* ファイルから N, M を読み込む */
    if (N > maxN)
    {
        printf("N is too large, setting N = 50\n");
        N = maxN;
    }
    for (u = 0; u < N; u++) /* 重み行列の初期化 */
    {
        for (v = 0; v < N; v++)
        {
            Adj[u][v] = inf;
        }
    }
    for (i = 0; i < M; i++)
    {
        fscanf(fp, " %d %d %d", &u, &v, &len); /* 順番に辺の両端 u, v ,lenを読み込む */
        Adj[u][v] = len;                       /* 重み行列に対する処理 */
        Adj[v][u] = len;
    }
    fscanf(fp, " %d", &v0); /* 始点 v0 を読み込む */
    fclose(fp);

    //Dijkstra初期化部分
    for (u = 0; u < N; u++)
    {
        if (u == v0)
            continue;
        d[u] = inf;
        p[u] = -1;
        A[u] = 0;
    }
    d[v0] = 0;
    p[v0] = -1;
    A[v0] = 1;
    //Dijkstra主要部分
    while (1)
    {
        v = minimumA(A, N, d);
        A[v] = 0;

        for (i = 0; i < N; i++)
        {
            if (Adj[v][i] != inf)
            {
                if (d[i] == inf)
                {
                    d[i] = d[v] + Adj[v][i];
                    p[i] = v;
                    A[i] = 1;
                }
                else if (d[i] > d[v] + Adj[v][i])
                {
                    d[i] = d[v] + Adj[v][i];
                    p[i] = v;
                }
            }
        }
        if (minimumA(A, N, d) == -1)
            break;
    }
    for (u = 0; u < N; u++) //結果を出力
    {
        printf("vertex %d: d[%d]=%2d, p[%d]=%2d\n", u, u, d[u], u, p[u]);
    }
}

//A の中で d の値が最小の頂点を見つける
int minimumA(int *A, int N, int *d)
{
    int minV = -1;
    int min = inf;
    int i;
    for (i = 0; i < N; i++)
    {
        if (A[i] == 1 && d[i] < min)
        {
            min = d[i];
            minV = i;
        }
    }
    return minV;
}