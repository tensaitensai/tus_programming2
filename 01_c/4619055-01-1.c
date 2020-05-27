//4619055 辰川力駆　課題1
#include <stdio.h>

int main()
{
    int year, month;
    int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    printf("西暦と月を入力してください\n");
    scanf("%d %d", &year, &month);
    if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
        days[1]++;
    printf("%d年%d月は%d日まであるよ。\n", year, month, days[month - 1]);
    return 0;
}