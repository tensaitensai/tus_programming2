//4619055 辰川力駆　課題1
#include <stdio.h>

typedef struct
{
    double height;
    double weight;
    char blood[2];
} human;

void input(int n, human *h)
{
    printf("生徒%d人分の身長，体重，血液型を入力してください。\n", n);
    int i;
    for (i = 0; i < n; i++)
    {
        printf("%d人目の身長を入力してください。\n", i + 1);
        scanf("%lf", &h[i].height);
        printf("%d人目の体重を入力してください。\n", i + 1);
        scanf("%lf", &h[i].weight);
        printf("%d人目の血液型を入力してください。\n", i + 1);
        scanf("%s", h[i].blood);
    }
}

void out(int n, human *h)
{
    int i;
    for (i = 0; i < n; i++)
    {
        printf("生徒%d人目の身長は%g,体重は%g,血液型は%sです。\n", i + 1, h[i].height, h[i].weight, h[i].blood);
    }
}
int main()
{
    int n;
    printf("何人分入力するか教えて下さい。\n");
    scanf("%d", &n);
    human h[n];
    input(n, h);
    out(n, h);
    return 0;
}