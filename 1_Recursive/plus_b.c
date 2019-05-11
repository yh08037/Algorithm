#include <stdio.h>
#define MAXN 50

int combination(int n, int k)
{
    static int memo[MAXN][MAXN];

    if (memo[n][k] > 0)
        return memo[n][k];

    if (k == 0 || n == k)
        return memo[n][k] = 1;

    return memo[n][k] = combination(n-1, k-1) + combination(n-1, k);
}

int print_pascal(int n)
{
    for ( int i = 0; i < n; i++ ) {
        for ( int j = 0; j < n - i - 1; j++ ) {
            printf("    ");
        }
        for ( int j = 0; j <= i; j++ ) {
            printf("%8d", combination(i, j));
        }
        printf("\n");
    }
}

int main(void) {
    int n; scanf("%d", &n);
    print_pascal(n);

    return 0;
}
