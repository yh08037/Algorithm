#include <stdio.h>

int pay(int m, int n, int *bill)
{
    if (n == 1)
        return (m % n) ? 0 : 1;

    int cnt = 0;
    int t = m / bill[n-1];

    for (int i = 0; i <= t; i++)
        cnt += pay(m - i * bill[n-1], n-1, bill);
    return cnt;
}

#define MAXN 50

int main(void)
{
    int num, money;
    int bill[MAXN];

    printf("input number of bills: ");
    scanf("%d", &num);
    printf("input bills: ");
    for (size_t i = 0; i < num; i++) {
        scanf("%d", bill+i);
    }
    printf("input money: ");
    scanf("%d", &money);

    printf("%d\n", pay(money, num, bill));
    return 0;
}
