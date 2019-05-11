#include <stdio.h>
#define MAXN 200

int partition(int n, int m)
{
    if (n < m)
        m = n;
    if (n == 0)
        return 1;

    int cnt = 0;
    for ( int i = 1; i <= m; i++ )
        cnt += partition(n-i, i);
    return cnt;
}

void print_arr(int arr[], int arr_len)
{
    for ( int i = 0; i < arr_len; i++ ) {
        printf("%d ", arr[i]);
    } printf("\n");
}

int partition_print(int n, int m, int arr[], int arr_len)
{
    if (n < m)
        m = n;
    if (n == 0){
        print_arr(arr, arr_len);
        return 1;
    }
    int cnt = 0;
    for ( int i = 1; i <= m; i++ ){
        arr[arr_len] = i;
        cnt += partition_print(n-i, i, arr, arr_len + 1);
    }
    return cnt;
}

int partition_memo(int n, int m)
{
    static int memo[MAXN][MAXN];

    if (n < m)
        m = n;
    if (memo[n][m] > 0)
        return memo[n][m];
    if (n == 0)
        return memo[n][m] = 1;

    int cnt = 0;
    for ( int i = 1; i <= m; i++ )
        cnt += partition_memo(n-i, i);
    return memo[n][m] = cnt;
}

int main(void)
{
    printf("input n, m: ");
    int m, n; scanf("%d %d", &n, &m);

    int num[MAXN];
    // printf("total: %d\n", partition_print(n, m, num, 0));
    printf("total: %d\n", partition_memo(n, m));
    return 0;
}
