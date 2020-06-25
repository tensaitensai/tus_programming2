//4619055 辰川力駆　課題2
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#include <math.h>

void radix_sort(int *A, int n, int k, int d); //分布数え上げソートによる基数ソート

int main(void)
{
    int Data[50]; /* 入力数値の配列，数値数は 50 まで */
    int N, k, d;  /* 数値の数 N，k 進数，桁数 d */
    int i, j;
    /* 必要な変数を宣言 */
    char fname[128];                    /* 読み込むファイルの名前 */
    FILE *fp;                           /* 入力ファイル */
    printf("input filename: ");         /* ファイル名の入力を要求 */
    fgets(fname, sizeof(fname), stdin); /* 標準入力からファイル名を取得 */
    fname[strlen(fname) - 1] = '\0';    /* 最後の改行コードを除去 */
    fflush(stdin);                      /* 128文字を超えた入力を標準入力から捨てる */
    fp = fopen(fname, "r");             /* ファイルを読み込みモードで開く */
    fscanf(fp, "%d %d %d", &N, &k, &d);
    if (N > 50)
    {
        printf("N is too large, setting N = 50\n");
        N = 50;
    }
    for (i = 0; i < N; i++)
    {
        fscanf(fp, "%d", &Data[i]); /* 整数をファイルから読み込む */
        if (Data[i] >= pow(k, d))   //k進表現の桁数がdを超えているかチェックし，超過した場合は省く
        {
            printf("データが%d進表現の桁数が%dを超えているので、このデータ%dは除外します。\n", k, d, Data[i]);
            N--;
            i--;
        }
        if (Data[i] < 0)
        {
            printf("データが負の数のため、このデータ%dは除外します。\n", Data[i]);
            N--;
            i--;
        }
    }
    fclose(fp);

    printf("ソートする前のデータを表示します。\n");
    for (i = 0; i < N; i++)
    {
        printf("[%d],", Data[i]);
    }
    printf("\n");

    radix_sort(Data, N, k, d); //分布数え上げソートによる基数ソート

    printf("ソートした後のデータを表示します。\n");
    for (i = 0; i < N; i++)
    {
        printf("[%d],", Data[i]);
    }
    printf("\n");

    return 0;
}

void radix_sort(int *A, int n, int k, int d) //分布数え上げソートによる基数ソート
{
    int B[50]; //補助配列
    int C[50]; //カウントする配列
    int i, j;
    int val; //k^dの桁の値

    for (i = 0; i < d; i++)
    {
        for (j = 0; j < k; j++) //C[i]の値初期化
        {
            C[j] = 0;
        }
        for (j = 0; j < n; j++) //C[i]の値を求める
        {
            val = (A[j] / (int)pow(k, i)) % k;
            C[val]++;
        }
        for (j = 1; j < k; j++) //C[i]の値を求める
        {
            C[j] = C[j - 1] + C[j];
        }

        for (j = n - 1; j >= 0; j--)
        {
            val = (A[j] / (int)pow(k, i)) % k;
            B[C[val] - 1] = A[j];
            C[val]--;
        }
        for (j = 0; j < n; j++)
        {
            A[j] = B[j];
        }
    }
}