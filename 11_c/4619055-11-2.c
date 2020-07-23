//4619055 辰川力駆　課題2
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define maxN 50     /* 扱う頂点数の最大値，ここでは 50 に設定 */
#define inf 1000000 /* 無限大の値を十分大きな整数に設定 */
struct cell         /* 構造体 cell の定義 */
{
    int key;
    int vertex;
};
int parent(int i); /* parent 関数を宣言 */
int right(int i);  // rightの宣言
int left(int i);   // leftの宣言
void insert(struct cell *H, int *adr, int i, int a, int v);
void decrease_key(struct cell *H, int *adr, int i, int a);
int delete_min(struct cell *H, int *adr, int i);
void downheap_sort(struct cell *H, int *adr, int i);
void upheap_sort(struct cell *H, int *adr, int i);
void swapInt(int *a, int *b);

int main(void)
{
    int N, M;                           /* 頂点数，辺数 */
    int Lmat[maxN][maxN];               /* 重み行列を表す変数 */
    struct cell Heap[maxN];             /* ヒープに用いる配列の宣言 */
    int adr[maxN];                      /* ヒープに含まれる頂点のアドレスの配列 */
    int d[maxN], p[maxN];               /* d[u], p[u] を格納する変数 */
    int hsize;                          /* ヒープに格納された頂点の数 */
    int v0;                             /* 始点を表す変数 */
    int i, u, v, len;                   /* 必要な変数を宣言 */
    char fname[128];                    /* 読み込むファイルの名前 */
    FILE *fp;                           /* 入力ファイル */
    printf("input filename: ");         /* ファイル名の入力を要求 */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);                      /* 128文字を超えた入力を標準入力から捨てる */
    fp = fopen(fname, "r");             /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d %d", &N, &M);        /* ファイルから N, M を読み込む */
    for (u = 0; u < N; u++)
    { /* 重み行列の初期化 */
        for (v = 0; v < N; v++)
        {
            Lmat[u][v] = inf;
        }
    }

    for (i = 0; i < M; i++)
    {
        fscanf(fp, " %d %d %d", &u, &v, &len); /* 順番に辺の両端 u, vと長さを読み込む */
        Lmat[u][v] = len;                      /* 重み行列を作成 */
        Lmat[v][u] = len;
    }
    fscanf(fp, " %d", &v0); /* 始点を読み込む */
    fclose(fp);

    for (u = 0; u < N; u++)
    { /* p[u], d[u], adr[u] の初期化 */
        d[u] = inf;
        p[u] = -1;
        adr[u] = -1;
    }
    d[v0] = 0;
    p[v0] = -1;
    hsize = 0;

    hsize++;
    insert(Heap, adr, hsize - 1, d[v0], v0); // heapにv0を入れる

    while (1)
    {
        v = delete_min(Heap, adr, hsize); // 最小値を削除
        hsize--;

        for (i = 0; i < N; i++)
        {
            if (Lmat[v][i] != inf)
            {
                if (d[i] == inf)
                {
                    d[i] = d[v] + Lmat[v][i];
                    p[i] = v;

                    hsize++;
                    insert(Heap, adr, hsize - 1, d[i], i); // ヒープに格納
                }
                else if (d[i] > d[v] + Lmat[v][i])
                {
                    d[i] = d[v] + Lmat[v][i];
                    p[i] = v;

                    decrease_key(Heap, adr, i, d[i]);
                }
            }
        }
        if (hsize == 0)
            break;
    }

    for (u = 0; u < N; u++) //結果を出力
    {
        printf("vertex %d: d[%d]=%2d, p[%d]=%2d\n", u, u, d[u], u, p[u]);
    }
}

int parent(int i)
{
    return (i - 1) / 2;
}

int right(int i)
{
    return i * 2 + 2;
}

int left(int i)
{
    return i * 2 + 1;
}

void insert(struct cell *H, int *adr, int hsize, int a, int v)
{
    H[hsize].key = a;
    H[hsize].vertex = v;
    adr[v] = hsize;

    upheap_sort(H, adr, hsize);
}

void decrease_key(struct cell *H, int *adr, int i, int a)
{
    H[i].key = a;
    upheap_sort(H, adr, i);
}

int delete_min(struct cell *H, int *adr, int hsize)
{
    int v = H[0].vertex;
    adr[v] = -1;
    if (hsize > 1)
    {
        H[0].key = H[hsize - 1].key;
        H[0].vertex = H[hsize - 1].vertex;
        adr[H[0].vertex] = 0;

        downheap_sort(H, adr, hsize - 2);
    }

    return v;
}

void downheap_sort(struct cell *H, int *adr, int i)
{
    int u = 0;
    int l, r, s;

    while (1)
    {
        l = left(u);
        r = right(u);
        s = u;

        if (l <= i && H[l].key < H[u].key)
        {
            s = l;
        }
        if (r <= i && H[r].key < H[s].key)
        {
            s = r;
        }
        if (s != u)
        {
            swapInt(&H[u].key, &H[s].key);
            swapInt(&H[u].vertex, &H[s].vertex);
            swapInt(&adr[H[u].vertex], &adr[H[s].vertex]);

            u = s;
        }
        else
        {
            break;
        }
    }
}

void upheap_sort(struct cell *H, int *adr, int i)
{
    int u = i;

    while (u > 0 && H[parent(u)].key > H[u].key)
    {
        swapInt(&H[u].key, &H[parent(u)].key);
        swapInt(&H[u].vertex, &H[parent(u)].vertex);
        swapInt(&adr[H[u].vertex], &adr[H[parent(u)].vertex]);

        u = parent(u);
    }
}

void swapInt(int *a, int *b)
{
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}