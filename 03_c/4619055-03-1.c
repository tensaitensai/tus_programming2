//4619055 辰川力駆　課題1
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
struct cell
{
    int key;
    int prev;
    int next; /* 構造体 cell の定義 */
};
int allocate_object(struct cell *L, int *f); /* 関数 allocate_object の宣言 */
/* （他の関数も宣言すること） */
void dataprint(int *data, int n);
void free_object(struct cell *L, int *freeL, int x);
void list_delete(struct cell *L, int *head, int x);
int list_minimum(struct cell *L, int *head);
void list_insert(struct cell *L, int *head, int p, int x);

int main(void)
{
    int x;
    struct cell List[50]; /* リストは cell の配列，数値数は 50 まで */
    int N;                /* 数値の数は N */
    int Data[50];         /* 数値を格納する配列は Data */
    int i;
    int head, freeL;                    /* リスト List の先頭，空きアドレスリストの先頭 */
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
        fscanf(fp, "%d", &Data[i]); /* 整数値を順に読み込み，Data に格納する */
    }
    fclose(fp); /* 開いたファイルを閉じる */
    for (i = 0; i < 49; i++)
    { /* allocate_object, free_object のための初期化 */
        List[i].next = i + 1;
        List[i].prev = i - 1;
    }
    List[49].next = -1;
    head = -1;
    freeL = 0; /* head freeL の初期化 */
    /* 主要部分（各自作成） */
    for (i = 0; i < N; i++)
    {
        x = allocate_object(List, &freeL);
        List[x].key = Data[i];
        list_insert(List, &head, -1, x);
    }
    for (i = 0; i < N; i++)
    {
        x = list_minimum(List, &head);
        Data[i] = List[x].key;
        list_delete(List, &head, x);
        free_object(List, &freeL, x);
    }
    dataprint(Data, N);
}

int allocate_object(struct cell *L, int *f)
{ /* リスト配列と空きアドレスリスト先頭はポインタ渡し */
    int x;
    if (*f == -1)
    {
        printf("error: out of space\n");
        x = -1;
    }
    /* 空きアドレスがなければエラーメッセージを表示 */
    else
    {
        x = *f;
        *f = L[*f].next;
    }
    return x;
}

void dataprint(int *data, int n)
{
    int i;
    printf("小さい順に出力します\n");
    for (i = 0; i < n; i++)
    {
        printf("%d\n", data[i]);
    }
}

void free_object(struct cell *L, int *freeL, int x)
{
    L[x].next = *freeL;
    *freeL = x;
}

void list_delete(struct cell *L, int *head, int x)
{
    if (L[x].prev != -1)
    {
        L[L[x].prev].next = L[x].next;
    }
    else
    {
        *head = L[x].next;
    }
    if (L[x].next != -1)
    {
        L[L[x].next].prev = L[x].prev;
    }
}

int list_minimum(struct cell *L, int *head)
{
    int x = *head;
    int y = x;
    int min = 1000000;
    while (x != -1)
    {
        if (L[x].key < min)
        {
            min = L[x].key;
            y = x;
        }
        x = L[x].next;
    }
    return y;
}

void list_insert(struct cell *L, int *head, int p, int x)
{
    L[x].prev = p;
    if (p != -1)
    {
        L[x].next = L[p].next;
        L[p].next = x;
    }
    else
    {
        L[x].next = *head;
        *head = x;
    }
    if (L[x].next != -1)
    {
        L[L[x].next].prev = x;
    }
}
