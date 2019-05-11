#include <stdio.h>

int factorial(int n)
{
    int r, i;

    r = 1;
    for (i = 2; i <= n; i++)
        r *= i;
    return r;
}

int factorial2(int n)
{
    if (n == 1)
        return 1;
    else
        return n * factorial2(n - 1);
}

int main(void)
{
    printf("%d %d\n", factorial(10), factorial(10));

    return 0;
}
