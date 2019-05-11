#include <stdio.h>
#define MAXN 200

long long fibo(int n)
{
    if (n == 1 || n == 2)
        return 1;
    else
        return fibo(n-1) + fibo(n-2);
}

long long fibo2(int n)
{
    static long long memo[MAXN];

    if (memo[n] > 0)    /* 메모이제이션 배열에 값이 저장되어있다면 */
        return memo[n]; /* 중복 연산하지 않고 그 값을 반환한다 */

    if (n == 1 || n == 2)
        return memo[n] = 1;

    else
        return memo[n] = fibo2(n-1) + fibo2(n-2);
}

int main(void)
{
    int n; scanf("%d", &n);
    printf("%d\n", fibo2(n));

    return 0;
}
