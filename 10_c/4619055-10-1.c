//4619055 辰川力駆　課題1
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define maxN 50     /* 扱う頂点数の最大値，ここでは 50 に設定 */
int main(void)
{
    int N, M;                           /* 頂点数，辺数 */
    int Adj[maxN][maxN];                /* 隣接行列を表す変数 */
    int u, v, i;                        /* 必要な変数を宣言 */
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
    for (u = 0; u < N; u++) /* 隣接行列の初期化 */
    {
        for (v = 0; v < N; v++)
        {
            Adj[u][v] = 0;
        }
    }

    for (i = 0; i < M; i++)
    {
        fscanf(fp, " %d %d", &u, &v); /* 順番に辺の両端 u, v を読み込む */
        Adj[u][v]++;                  /* 隣接行列に対する処理 */
        Adj[v][u]++;
    }
    fclose(fp);
    printf("Adjacency matrix\n"); /* 隣接行列出力 */
    printf("  /");
    for (v = 0; v < N; v++)
    {
        u = 0;
        printf(" %d", Adj[u][v]);
    }
    printf(" \\\n");
    for (u = 1; u < N - 1; u++)
    {
        printf("  |");
        for (v = 0; v < N; v++)
        {
            printf(" %d", Adj[u][v]);
        }
        printf(" |\n");
    }
    printf("  \\");
    for (v = 0; v < N; v++)
    {
        u = N - 1;
        printf(" %d", Adj[u][v]);
    }
    printf(" /\n");
}