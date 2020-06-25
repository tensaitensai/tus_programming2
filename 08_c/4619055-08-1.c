//4619055 辰川力駆　課題1
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
void counting_sort(int *A, int n, int k);

int main(void)
{
    int Data[50]; /* 入力数値の配列，数値数は 50 まで */
    int N, k;     /* 数値の数 N，値の種類 k */
    int i;
    /* 必要な変数を宣言 */
    char fname[128];                    /* 読み込むファイルの名前 */
    FILE *fp;                           /* 入力ファイル */
    printf("input filename: ");         /* ファイル名の入力を要求 */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);                      /* 128文字を超えた入力を標準入力から捨てる */
    fp = fopen(fname, "r");             /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d %d", &N, &k);
    /* N, k をファイルから読み込む */
    if (N > 50)
    {
        printf("N is too large, setting N = 50\n");
        N = 50;
    }
    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%d", &Data[i]);         /* 整数をファイルから読み込む */
        if (Data[i] < 0 || Data[i] > k - 1) /* [0, k-1] の範囲内かを判定し，範囲外ならエラーメッセージを表示し，データから外す */
        {
            printf("データが%d~%dの範囲外なので、このデータ%dは除外します。\n", 0, k - 1, Data[i]);
            N--;
            i--;
        }
    }
    fclose(fp); /* 開いたファイルを閉じる */

    printf("%d~%dの範囲にある、ソートする前のデータを表示します。\n", 0, k - 1);
    for (i = 0; i < N; i++) /* データを出力（各自作成） */
    {
        printf("[%d],", Data[i]);
    }
    printf("\n");

    counting_sort(Data, N, k); /* counting_sort を呼び出し */

    printf("%d~%dの範囲にある、ソートした後のデータを表示します。\n", 0, k - 1);
    for (i = 0; i < N; i++) /* 結果を出力（各自作成） */
    {
        printf("[%d],", Data[i]);
    }
    printf("\n");
}

void counting_sort(int *A, int n, int k)
{
    int B[50]; //補助配列
    int C[50]; //カウントする配列
    int i;
    for (i = 0; i < k; i++) //C[i]の値初期化
    {
        C[i] = 0;
    }
    for (i = 0; i < n; i++) //C[i]の値を求める
    {
        C[A[i]]++;
    }
    for (i = 1; i < k; i++) //C[i]の値を求める
    {
        C[i] = C[i - 1] + C[i];
    }

    for (i = n - 1; i >= 0; i--)
    {
        B[C[A[i]] - 1] = A[i];
        C[A[i]]--;
    }
    for (i = 0; i < n; i++)
    {
        A[i] = B[i];
    }
}