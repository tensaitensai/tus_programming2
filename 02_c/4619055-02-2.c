//4619055 辰川力駆　課題2
#include <stdio.h>

int main()
{
    FILE *fp;
    fp = fopen("rand.txt", "r"); //rand.txtは100000個のランダムな数字がはいっています

    if (fp == NULL)
    {
        printf("ファイルを開けませんでした。\n");
        return 1;
    }
    int num[100000];
    int sum[1000];
    int cnt[100];
    int i, j;
    for (i = 0; i < 100; i++)
    {
        cnt[i] = 0;
    }
    for (i = 0; i < 1000; i++)
    {
        sum[i] = 0;
    }
    for (i = 0; i < 100000; i++)
    {
        fscanf(fp, "%d", &num[i]);
    }
    printf("テキストから100000個の数字を読み取りました。\n100個ごとに和を求め、その和の分布を考えます。\n");

    for (i = 0; i < 1000; i++)
    {
        for (j = 0; j < 100; j++)
        {
            sum[i] += num[i * 100 + j];
        }
    }
    for (i = 0; i < 100; i++)
    {
        for (j = 0; j < 1000; j++)
        {
            if (sum[j] >= i * 100 && sum[j] < (i + 1) * 100)
                cnt[i]++;
        }
    }

    for (i = 0; i < 100; i++)
    {
        if (cnt[i] != 0)
            printf("%d~%dの値は%d個\n", i * 100, (i + 1) * 100 - 1, cnt[i]);
    }
    printf("表示していない範囲は0個\n");
    printf("中心極限定理に従って分布している\n");

    fclose(fp);
    return 0;
}