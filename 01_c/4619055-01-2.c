//4619055 辰川力駆　課題2
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
    srand((unsigned int)time(NULL)); // 現在時刻の情報で初期化
    int ans = rand() % 100;
    int num;
    printf("0以上99以下の整数がランダムに生成されました。\n");
    printf("当ててください\n");

    while (1)
    {
        printf("数字を入力してください\n");
        scanf("%d", &num);
        if (num > 99 || num < 0)
        {
            printf("数字は0~99を入力してください\n");
            continue;
        }
        int deff = num - ans;
        if (deff == 0)
        {
            printf("正解です\n");
            exit(0);
        }
        else if (deff <= -10)
            printf("小さすぎます\n");
        else if (deff >= -9 && deff <= -1)
            printf("小さいです\n");
        else if (deff >= 1 && deff <= 9)
            printf("大きいです\n");
        else if (deff >= 10)
            printf("大きすぎます\n");
    }

    return 0;
}