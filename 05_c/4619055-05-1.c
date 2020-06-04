//4619055 辰川力駆　課題1
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
/* 関数 parent, heapsort の宣言，他の関数も宣言すること */
int parent(int i);
int left(int i);
int right(int i);
void heap_sort(int *H, int *A, int n);
void build_heap(int *H, int *A, int n);
void downheap_sort(int *H, int i);
void insert(int *H, int i, int a);
void upheap_sort(int *H, int i);

int main(void)
{
    int Data[50]; /* 数値を格納する配列， 50 まで */
    int Heap[50]; /* ヒープを表す補助配列 */
    int N;        /* N やループで用いる int 型変数 */
    int i;
    char fname[128];                    /* 読み込むファイルの名前を格納する変数 */
    FILE *fp;                           /* ファイル名は 128 文字まで対応可能にする */
    printf("input filename: ");         /* ファイル名の入力を要求 */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);                      /* 128文字を超えた入力を標準入力から捨てる */
    fp = fopen(fname, "r");             /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d", &N);               /* N をファイルから読み込む */
    if (N > 50)
    {
        printf("N is too large, setting N = 50\n");
        N = 50; /* N が 50 を超えるときは警告をした上で */
    }           /* N =50 に設定する */

    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%d", &Data[i]);
    }
    fclose(fp); /* 開いたファイルを閉じる */
    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]); /* ソート前の数値の出力 */
    }
    printf("\n");
    heap_sort(Heap, Data, N); /* ヒープソートを呼ぶ */
    for (i = 0; i < N; i++)
    {
        printf("%d ", Data[i]); /* ソート後の数値の出力 */
    }
    printf("\n");
}

int parent(int i)
{
    return (i - 1) / 2;
}

int left(int i)
{
    return 2 * i + 1;
}

int right(int i)
{
    return 2 * i + 2;
}

void heap_sort(int *H, int *A, int n)
{
    int i;
    build_heap(H, A, n);
    for (i = 1; i < n; i++)
    {
        A[n - i] = H[0];
        H[0] = H[n - i];
        downheap_sort(H, n - i - 1);
    }
    A[0] = H[0];
}

void build_heap(int *H, int *A, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        insert(H, i, A[i]);
    }
}

void downheap_sort(int *H, int i)
{
    int u = 0;
    int l, r, tmp;
    while (1)
    {
        if (left(u) <= i)
        {
            l = left(u);
        }
        else
        {
            l = u;
        }
        if (right(u) <= i)
        {
            r = right(u);
        }
        else
        {
            r = u;
        }

        if (H[l] > H[u] && H[l] >= H[r])
        {
            tmp = H[u];
            H[u] = H[l];
            H[l] = tmp;
            u = l;
        }
        else if (H[r] > H[u] && H[l] <= H[r])
        {
            tmp = H[u];
            H[u] = H[r];
            H[r] = tmp;
            u = r;
        }
        else
        {
            break;
        }
    }
}

void insert(int *H, int i, int a)
{
    H[i] = a;
    upheap_sort(H, i);
}

void upheap_sort(int *H, int i)
{
    int u = i;
    int tmp;
    while (u > 0 && H[parent(u)] < H[u])
    {
        tmp = H[parent(u)];
        H[parent(u)] = H[u];
        H[u] = tmp;
        u = parent(u);
    }
}