#include <stdio.h>
void dfs_visit(int n, int A[][n], int u, int L[])
{
    L[u] = 1;
    printf("%d ", u);
    for (int i = 1; i < n; i++)
    {
        int v = A[u][i];
        if (v != -1)
        {
            if (L[v] == 0)
            {
                dfs_visit(n, A, v, L);
                // printf("me");
            }
        }
    }
    L[u] = 2;
}
void dfs(int n, int A[][n], int L[])
{
    // printf("Here");
    for (int i = 0; i < n; i++)
    {
        L[i] = 0;
    }
    for (int u = 0; u < n; u++)
    {
        // printf("[u: %d] ", u);
        if (L[u] == 0)
        {
            dfs_visit(n, A, u, L);
        }
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    int A[n][n];
    int L[n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            A[i][j] = -1;
        }
        L[i] = '\0';
    }
    for (int i = 0; i < n; i++)
    {
        // printf("%d", i);
        int j = 0;
        int k;
        char c = 'e';
        while (c != '\n')
        {
            scanf("%d%c", &k, &c);
            A[i][j] = k;
            j++;
        }
    }
    dfs(n, A, L);
}