//4619055 辰川力駆　課題2
#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* 文字列関数を扱えるようにする */
#include <math.h>

struct cell
{
    int key;
    int next; /* 構造体 cell の定義 */
};

void radix_sort_bucket(int *A, int n, int k, int d);

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

    radix_sort_bucket(Data, N, k, d); /* radix_sort を呼び出し */

    printf("ソートした後のデータを表示します。\n");
    for (i = 0; i < N; i++)
    {
        printf("[%d],", Data[i]);
    }
    printf("\n");

    return 0;
}

void radix_sort_bucket(int *A, int n, int k, int d)
{
    struct cell List[50]; /* リストを格納する配列 */
    int B[50];            /* バケットを表す配列 */
    int i, j;
    int val;  //k^dの桁の値
    int post; //どれだけAに格納したか
    int now;

    for (i = 0; i < d; i++)
    {
        for (j = 0; j < n; j++)
        {                       /* あらかじめ n 個の数値をリストに格納 */
            List[j].key = A[j]; /* next の値を初期化 */
            List[j].next = -1;
        }
        for (j = 0; j < k; j++)
        {
            B[j] = -1;
        }
        post = 0;
        for (j = n - 1; j >= 0; j--)
        {
            val = (List[j].key / (int)pow(k, i)) % k;
            List[j].next = B[val];
            B[val] = j;
        }
        for (j = 0; j < k; j++)
        {
            now = B[j];
            while (now != -1)
            {
                A[post] = List[now].key;
                now = List[now].next;
                post++;
            }
        }
    }
}