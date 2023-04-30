#include <stdio.h>
int hash(int key, int n)
{
    return key % n;
}
int main()
{
    int n;
    scanf("%d", &n);
    int A[100001], B[100001];
    int k;
    for (int i = 0; i < 100001; i++)
    {
        A[i] = '\0';
        B[i] = '\0';
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &k);
        (A[k])++;
    }
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &k);
        (B[k])++;
    }
    for (int i = 0; i < 100001; i++)
    {
        if (A[i] != '\0' || B[i] != '\0')
        {
            printf("%d <%d %d>\n", i, A[i], B[i]);
        }
    }
    for (int i = 0; i < 100001; i++)
    {
        if (A[i] != B[i])
        {
            printf("0");
            return 0;
        }
    }
    printf("1");
}