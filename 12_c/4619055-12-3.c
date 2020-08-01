//4619055 辰川力駆　課題3
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define maxN 50     /* 扱う頂点数の最大値，ここでは 50 に設定 */
#define maxM 500    /* 扱う辺数の最大値，ここでは 500 に設定 */

struct edge_data /* 構造体 edge_data の定義 */
{
    int end1;
    int end2;
    int weight;
};

void kruskal(int n, int m, int *p, int *rank, int *W, struct edge_data *edge, int *ednum, int *T);
void make_set(int *p, int *rank, int x); /* make_set 関数を宣言 */
int find_set(int *p, int *rank, int x);  /* find_set, link も宣言すること */
void link(int *p, int *rank, int x, int y);
void set_union(int *p, int *rank, int x, int y, int k, int *T); /* set_union 関数を宣言 */
void quicksort(int *A, int *ednum, int p, int r);
int partition(int *A, int *ednum, int p, int r);
void swapInt(int *a, int *b); /* quicksort 関連の関数の宣言 */

int main(void)
{
    int T[maxN];
    int N, M;                           /* 頂点数，辺数 */
    struct edge_data edge[maxM];        /* 辺データを表す変数 */
    int p[maxN], rank[maxN];            /* p[x], rank[x] を格納する変数 */
    int W[maxM];                        /* 辺の重みを格納する配列 */
    int ednum[maxM];                    /* 昇順における辺の番号を格納する配列 */
    int u, v, w;                        /* 頂点番号，重みを表す変数 */
    int i, k;                           /* 必要な変数を宣言 */
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
    for (i = 0; i < M; i++)
    {
        fscanf(fp, " %d %d %d", &u, &v, &w); /* 辺データを読み込み，edge に格納 */
        edge[i].end1 = u;
        edge[i].end2 = v;
        edge[i].weight = w;
    }
    fclose(fp);

    for (i = 0; i < M; i++)
    {
        W[i] = edge[i].weight;
        ednum[i] = i; /* 配列 W と ednum にデータを格納 */
    }

    kruskal(N, M, p, rank, W, edge, ednum, T);

    for (i = 0; i < N; i++) //結果を出力
    {
        printf("vertex %2d, parent=%2d rank=%2d\n", i, p[i], rank[i]);
    }
    for (i = 0; i < M; i++)
    {
        if (T[i] == 1)
        {
            printf("edge (%2d, %2d)", edge[i].end1, edge[i].end2);
            printf(" weight = %d\n", edge[i].weight);
        }
    }

    return 0;
}

void kruskal(int n, int m, int *p, int *rank, int *W, struct edge_data *edge, int *ednum, int *T)
{
    int i, u, v, k, x, y;
    quicksort(W, ednum, 0, m - 1);
    for (i = 0; i < m; i++)
    {
        T[i] = 0;
    }
    for (u = 0; u < n; u++)
    {
        make_set(p, rank, u);
    }
    for (i = 0; i < m; i++)
    {
        k = ednum[i];
        u = edge[k].end1;
        v = edge[k].end2;

        x = find_set(p, rank, u);
        y = find_set(p, rank, v);
        set_union(p, rank, x, y, k, T);
    }
}

void make_set(int *p, int *rank, int x)
{
    p[x] = x;
    rank[x] = 0;
}

int find_set(int *p, int *rank, int x)
{
    int y = x;
    int z, r;
    while (y != p[y])
    {
        y = p[y];
    }
    r = y;
    y = x;
    while (y != r)
    {
        z = p[y];
        p[y] = r;
        y = z;
    }

    return r;
}

void link(int *p, int *rank, int x, int y)
{
    if (rank[x] > rank[y])
    {
        p[y] = x;
    }
    else
    {
        p[x] = y;
        if (rank[x] == rank[y])
            rank[y]++;
    }
}

void set_union(int *p, int *rank, int x, int y, int k, int *T)
{
    if (x != y)
    {
        link(p, rank, x, y);
        T[k] = 1;
    }
}

void quicksort(int *A, int *ednum, int p, int r)
{
    int q;
    if (p < r)
    {
        q = partition(A, ednum, p, r);
        quicksort(A, ednum, p, q);
        quicksort(A, ednum, q + 1, r);
    }
}

int partition(int *A, int *ednum, int p, int r)
{
    int x = A[p];
    int i = p;
    int j = r;
    int tmp;
    while (1)
    {
        if (A[j] > x)
        {
            j--;
            continue;
        }
        else if (A[i] < x)
        {
            i++;
            continue;
        }
        else if (i < j)
        {
            swapInt(&A[i], &A[j]);
            swapInt(&ednum[i], &ednum[j]);
            j--;
            i++;
            continue;
        }
        else if (i >= j)
        {
            break;
        }
    }
    return j;
}

void swapInt(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}