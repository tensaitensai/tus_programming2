//4619055 辰川力駆　課題2
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define maxN 50     /* 扱う頂点数の最大値，ここでは 50 に設定 */
#define inf 1000000 /* 無限大の値を十分大きな整数に設定 */

int head, tail; /* キューの先頭と末尾 */
void Enqueue(int *Q, int a);
int Dequeue(int *Q);

int main(void)
{
    int N, M;                           /* 頂点数，辺数 */
    int Adj[maxN][maxN];                /* 隣接行列を表す変数 */
    int d[maxN], p[maxN], color[maxN];  /* 配列変数 d, p, color */
    int v0;                             /* 始点の変数 */
    int Q[maxN];                        /* キューを表す変数 */
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
    fscanf(fp, " %d", &v0); /* 始点 v0 を読み込む */
    fclose(fp);

    //BFSの初期化
    for (u = 0; u < N; u++)
    {
        if (u == v0)
            continue;
        color[u] = 0;
        d[u] = inf;
        p[u] = -1;
    }
    head = 0;
    tail = 0;
    Enqueue(Q, v0);
    color[v0] = 1;
    d[v0] = 0;
    p[v0] = -1;

    //繰り返し動作
    while (head != tail)
    {
        v = Dequeue(Q);
        for (u = 0; u < N; u++)
        {
            if (Adj[u][v] == 1)
            {
                if (color[u] == 0)
                {
                    Enqueue(Q, u);
                    color[u] = 1;
                    d[u] = d[v] + 1;
                    p[u] = v;
                }
            }
        }
        color[v] = 2;
    }

    for (u = 0; u < N; u++) //結果を出力
    {
        printf("vertex %d: d[%d]=%2d, p[%d]=%2d\n", u, u, d[u], u, p[u]);
    }
}

void Enqueue(int *Q, int a)
{
    Q[tail] = a;
    tail++;
    if (tail == maxN)
        tail = 0;
    if (tail == head)
    {
        printf("Enqueue overflow\n");
        exit(1);
    }
}

int Dequeue(int *Q)
{
    int a;
    if (head == tail)
    {
        printf("Dequeue overflow\n");
        exit(1);
    }
    else
    {
        a = Q[head];
        head++;
        if (head == maxN)
            head = 0;
        return a;
    }
}