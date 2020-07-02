//4619055 辰川力駆　課題1
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */

void quicksort(int *A, int p, int r); /* 関数 quicksort の宣言 */
int partition(int *A, int p, int r);  /* 関数 partition の宣言 */

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

    quicksort(Data, 0, N - 1); /* quicksort を呼び出し */

    printf("ソートした後のデータを表示します。\n");
    for (i = 0; i < N; i++) /* 結果を出力（各自作成） */
    {
        printf("[%d],", Data[i]);
    }
    printf("\n");
}

void quicksort(int *A, int p, int r)
{
    int q;
    if (p < r)
    {
        q = partition(A, p, r);
        quicksort(A, p, q);
        quicksort(A, q + 1, r);
    }
}

int partition(int *A, int p, int r)
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
            tmp = A[i];
            A[i] = A[j];
            A[j] = tmp;
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