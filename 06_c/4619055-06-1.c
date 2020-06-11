//4619055 辰川力駆　課題1
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#define W 10        /* W = 文字列の最大長さ，ここでは 10 に設定 */
#define m 97        /* m = ハッシュ表のサイズ，ここでは 97 に設定 */
#define n 50        /* n = 扱う文字列の最大数，ここでは 50 に設定 */

struct cell
{
    char key[W + 1];
    int next; /* 構造体 cell の定義 */
};

int allocate_object(struct cell *L, int *f);
void free_object(struct cell *L, int *freeL, int x);
int chained_hash_search(int *A, struct cell *L, char *a);
void chained_hash_insert(int *A, struct cell *L, int x);
void chained_hash_delete(int *A, struct cell *L, int x);
int hash_val(char *a);
int len_list(struct cell *L, int x);

int main(void)
{
    struct cell List[n]; /* リストは cell の配列，数値数は n まで */
    int A[m];            /* ハッシュ表を表す配列 */
    int N;               /* 数値の数は N */
    int freeL;           /* 空きアドレスのリストの先頭*/
    int i, h;
    int x, y;
    char word[W + 1]; /* ファイルから読み込んだ文字列を格納する変数 */
    char fname[128];  /* 読み込むファイルの名前 */
    FILE *fp;         /* 入力ファイル */
    for (i = 0; i < n - 1; i++)
    { /* allocate_object, free_object のための初期化 */
        List[i].next = i + 1;
    }
    List[n - 1].next = -1;
    freeL = 0; /* 空きリストの初期化 */
    for (h = 0; h < m; h++)
    {
        A[h] = -1;
    }                                   /* ハッシュ表の初期化 */
    printf("input filename: ");         /* ファイル名の入力を要求 */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);                      /* 128文字を超えた入力を標準入力から捨てる */
    fp = fopen(fname, "r");             /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d", &N);               /* N をファイルから読み込む */
    if (N > n)
    {
        printf("N is too large, setting N = %d\n", n);
        N = n;
    }

    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%s", word);                 /* 文字列をファイルから読み込み，wordに格納 */
        y = chained_hash_search(A, List, word); /* ハッシュ表の中で文字列 word を探索 */
        if (y == -1)
        {
            x = allocate_object(List, &freeL);
            strcpy(List[x].key, word);
            chained_hash_insert(A, List, x);
        }
    }

    fclose(fp); /* 開いたファイルを一旦閉じる */

    printf("データを追加しました。結果を表示します。\n");
    printf("リスト長が0でない場合のみ表示します。\n");
    for (h = 0; h < m; h++) /* ハッシュ表のアドレス h が指す*/
    {
        int len = len_list(List, A[h]);
        if (len)
        {
            printf("A[%d]の長さ=%d\n", h, len); /* リスト A[h] の長さを出力 */
        }
    }
    printf("以上です。\n");

    fp = fopen(fname, "r"); /* ファイルを再度読み込みモードで開く */
    fscanf(fp, "%d", &N);   /* N をファイルから読み込む */
    if (N > n)
    {
        N = n;
    }

    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%s", word);                 /* 文字列をファイルから読み込み，wordに格納 */
        x = chained_hash_search(A, List, word); /* ハッシュ表の中で文字列 word を探索 */
        if (x != -1)
        {
            chained_hash_delete(A, List, x);
            free_object(List, &freeL, x);
        }
    }

    fclose(fp); /* 開いたファイルを閉じる */

    printf("データを削除しました。結果を表示します。\n");
    printf("リスト長が0でない場合のみ表示します。\n");
    for (h = 0; h < m; h++) /* ハッシュ表のアドレス h が指す*/
    {
        int len = len_list(List, A[h]);
        if (len)
        {
            printf("A[%d]の長さ=%d\n", h, len); /* リスト A[h] の長さを出力 */
        }
    }
    printf("以上です。\n");

    return 0;
}

int allocate_object(struct cell *L, int *f)
{ /* リスト配列と空きアドレスリスト先頭はポインタ渡し */
    int x;
    if (*f == -1) /* 空きアドレスがなければエラーメッセージを表示 */
    {
        printf("error: out of space\n");
        x = -1;
    }
    else
    {
        x = *f;
        *f = L[*f].next;
    }
    return x;
}

void free_object(struct cell *L, int *freeL, int x)
{
    L[x].next = *freeL;
    *freeL = x;
}

int chained_hash_search(int *A, struct cell *L, char *a)
{
    int x = A[hash_val(a)];
    while (x != -1 && strcmp(L[x].key, a))
    {
        x = L[x].next;
    }
    return x;
}

void chained_hash_insert(int *A, struct cell *L, int x)
{
    int h = hash_val(L[x].key); /* L[x].key のハッシュ値を計算する */
    L[x].next = A[h];
    A[h] = x;
}

void chained_hash_delete(int *A, struct cell *L, int x)
{
    int z;
    if (x == -1)
    {
        z = -1;
    }
    else
    {
        z = A[hash_val(L[x].key)];
        while (z != -1 && L[z].next != x)
        {
            z = L[z].next;
        }
    }

    if (z != -1)
    {
        L[z].next = L[x].next;
    }
    else
    {
        A[hash_val(L[x].key)] = L[x].next;
    }
}

int hash_val(char *a) /* 文字列はポインタ渡し */
{
    int h, i;
    h = 0;
    i = 0;
    while (a[i] != 0 && i < W) /* 文字の整数コードの和を計算 */
    {
        h = h + (int)a[i];
        i = i + 1;
    }
    h = h % m; /* m で割った余りを取る */
    return h;
}

int len_list(struct cell *L, int x)
{
    int len = 0;
    while (x != -1)
    {
        len += 1;
        x = L[x].next;
    }
    return len;
}
