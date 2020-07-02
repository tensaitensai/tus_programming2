//4619055 辰川力駆　課題2
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */

void MergeSort(int *A, int p, int r);
void Merge(int *A, int p, int q, int r);

int main(void)
{
    int Data[50]; /* 入力数値の配列 Data */
    int N;        /* 数値の数 N*/
    int i, j;
    /* 必要な変数を宣言 */
    char fname[128];                    /* 読み込むファイルの名前 */
    FILE *fp;                           /* 入力ファイル */
    printf("input filename: ");         /* ファイル名の入力を要求 */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);                      /* 128文字を超えた入力を標準入力から捨てる */
    fp = fopen(fname, "r");             /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d", &N);
    if (N > 50)
    {
        printf("N is too large, setting N = 50\n");
        N = 50;
    }
    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%d", &Data[i]); /* 整数をファイルから読み込む */
    }
    fclose(fp); /* 開いたファイルを閉じる */

    printf("ソートする前のデータを表示します。\n");
    for (i = 0; i < N; i++) /* データを出力（各自作成） */
    {
        printf("[%d],", Data[i]);
    }
    printf("\n");

    MergeSort(Data, 0, N - 1);

    printf("ソートした後のデータを表示します。\n");
    for (i = 0; i < N; i++) /* 結果を出力（各自作成） */
    {
        printf("[%d],", Data[i]);
    }
    printf("\n");
}

void MergeSort(int *A, int p, int r)
{
    int q;
    if (p < r)
    {
        q = (p + r) / 2;
        MergeSort(A, p, q);
        MergeSort(A, q + 1, r);
        Merge(A, p, q, r);
    }
}

void Merge(int *A, int p, int q, int r)
{
    int i = p;
    int j = q + 1;
    int k = p;
    int B[r + 1];
    int t = 0;

    for (t = 0; t < r + 1; t++)
    {
        B[t] = 0;
    }
    while (1)
    {
        if (A[i] <= A[j])
        {
            B[k] = A[i];
            i++;
        }
        else
        {
            B[k] = A[j];
            j++;
        }
        k++;
        if (i > q || j > r)
        {
            break;
        }
    }
    if (i <= q)
    {
        for (; i <= q; i++)
        {
            B[k] = A[i];
            k++;
        }
    }
    if (j <= r)
    {
        for (; j <= r; j++)
        {
            B[k] = A[j];
            k++;
        }
    }
    for (t = p; t <= r; t++)
    {
        A[t] = B[t];
    }
}