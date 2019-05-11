#include <stdio.h>
#define MAXN 200

void print_arr(int arr[])
{
    int len = 0;
    while (arr[len] > 0) len++;
    for(int i = len-1; i >= 0; i--)
        printf("%d ",arr[i]);
    printf("\n");
}

void print_sum(int n, int k)
{
    static int arr[MAXN];

    if (k == 1) {
        arr[0] = n;
        print_arr(arr);
    } else {
        for(int i = 1; i <= n-k+1; i++) {
            arr[k-1] = i;
            print_sum(n-i, k-1);
        }
    }
}

int main(void)
{
    int n, k; scanf("%d %d", &n, &k);
    print_sum(n, k);

    return 0;
}
