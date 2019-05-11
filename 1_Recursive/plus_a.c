#include <stdio.h>

int sum(int n, int k)
{
    int sum = 0;
    for ( int i = 1; i <= n; i++ ) {
        int prod = 1;
        for ( int j = 1; j <= k; j++ ) {
            prod *= i;
        }
        sum += prod;
    }

    return sum;
}

int sum2(int n, int k)
{
    if (n == 1)
        return 1;
    int prod = 1;
    for ( int i = 1; i <= k; i++ )
        prod *= n;
    return prod + sum(n-1, k);
}

int main(void)
{
    int n, k; scanf("%d %d", &n, &k);
    printf("%d\n", sum2(n, k));
    return 0;
}
