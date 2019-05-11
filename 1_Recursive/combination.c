#include <stdio.h>
#define MAXN 200

long long choose(int n, int r)
{
    if (r == 0 || n == r)
        return 1;
    return choose(n-1, r-1) + choose(n-1, r);
}

long long choose2(int n, int r)
{
    /* Memoization을 위한 배열 */
    /* C에서 static 변수는 0으로 초기화된다 */
    static long long memo[MAXN][MAXN];

    if (memo[n][r] > 0)
        return memo[n][r];

    if (r == 0 || n == r)
        return memo[n][r] = 1;

    return memo[n][r] = choose2(n-1, r-1) + choose2(n-1, r);
}

int main(void)
{
    int n, r;

    printf("input n, r: ");
    scanf("%d %d", &n, &r);
    printf("%lld\n", choose2(n, r));

    return 0;
}
