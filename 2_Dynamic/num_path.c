#include <stdio.h>
#define M 100
#define N 100

int map[M][N];

long long num_path(int m, int n) {
    if ( map[m][n] == 0 )
        return 0;
    if ( m == 0 && n == 0 )
        return 1;
    return ((m>0) ? num_path(m-1, n) : 0)
        + ((n>0) ? num_path(m, n-1) : 0);
}

long long num_path_memo(int m, int n) {
    static long long memo[M][N];
    if ( memo[m][n] > 0 )
        return memo[m][n];
    if ( map[m][n] == 0 )
        return memo[m][n] = 0;
    if ( m == 0 && n == 0 )
        return memo[0][0] = 1;
    return memo[m][n] = ((m>0) ? num_path_memo(m-1, n) : 0)
        + ((n>0) ? num_path_memo(m, n-1) : 0);
}


int path[M][N];

void calculate_path(int m, int n) {
    int i, j;

    path[0][0] = map[0][0];

    for (i = 1; i < m; i++) {
        if ( map[i][0] == 0 )
            path[i][0] = 0;
        else
            path[i][0] = path[i-1][0];
    }
    for (j = 1; j < n; j++) {
        if (map[0][j] == 0)
            path[0][j] = 0;
        else
            path[0][j] = path[0][j-1];
    }
    for (i = 1; i < m; i++) {
        for (j = 1; j < m; j++) {
            if (map[i][j] == 0)
                path[0][0] = 0;
            else
                path[i][j] = path[i-1][j] + path[i][j-1];
        }
    }
}

int main(void) {
    int m, n, i, j;
    scanf("%d %d", &m, &n);
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%d", map[i]+j);
    //printf("%lld\n", num_path_memo(m-1, n-1));
    calculate_path(m, n);
    printf("%d\n", path[m-1][n-1]);

    return 0;
}
