//4619055 辰川力駆　課題3
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define maxN 50     /* 扱う頂点数の最大値，ここでは 50 に設定 */
#define inf 1000000 /* 無限大の値を十分大きな整数に設定 */

int N, M;                                   /* 頂点数，辺数 */
int Adj[maxN + 1][maxN + 1];                /* 隣接行列を表す変数 */
int d[maxN], f[maxN], p[maxN], color[maxN]; /* 配列変数 d, f, p, color */
int T;                                      /* time を表す変数 T*/

void traverse(int v); /* 関数 traverse を宣言 */
void DFS();           //すべての頂点を訪問する DFS

int main(void)
{
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

    DFS();

    for (u = 0; u < N; u++) //結果を出力
    {
        printf("vertex %d: d[%d]=%2d, f[%d]=%2d, p[%d]=%2d\n", u, u, d[u], u, f[u], u, p[u]);
    }
}

void traverse(int v) /* 関数 traverse を宣言 */
{
    int u;
    color[v] = 1;
    T++;
    d[v] = T;
    for (u = 0; u < N; u++)
    {
        if (Adj[u][v] == 1)
        {
            if (color[u] == 0)
            {
                p[u] = v;
                traverse(u);
            }
        }
    }
    color[v] = 2;
    T++;
    f[v] = T;
}

void DFS() //すべての頂点を訪問する DFS
{
    int v;
    for (v = 0; v < N; v++)
    {
        color[v] = 0;
        d[v] = inf;
        f[v] = inf;
        p[v] = -1;
    }
    T = 0;
    for (v = 0; v < N; v++)
    {
        if (color[v] == 0)
        {
            traverse(v);
        }
    }
}