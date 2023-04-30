#include <stdio.h>
int lin_hash(int a, int n, int j)
{
    return ((a % n) + j) % n;
}
int check(int B[], int index, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (B[i] == index)
        {
            return 1;
        }
    }
    return 0;
}
int quad_hash(int a, int n, int j)
{
    return ((a % n) + (j * j)) % n;
}
int dob_hash(int a, int n, int j)
{
    int p = 2;
    for (int i = n - 1; i > 2; i--)
    {
        int f = 0;
        for (int j = 2; j < i; j++)
        {
            if (i % j == 0)
            {
                f = 1;
                break;
            }
        }
        if (f == 0)
        {
            p = i;
            break;
        }
    }
    return ((a % n) + j * (p - (a % p))) % n;
}
void lin_probe(int A[], int len, int n)
{
    int B[len];
    for (int i = 0; i < len; i++)
    {
        B[i] = -1;
    }
    int c = 0;
    for (int i = 0; i < len; i++)
    {
        int j = 0;
        while (j < n)
        {
            int index = lin_hash(A[i], n, j);
            if (check(B, index, len))
            {
                c++;
                j++;
            }
            else
            {
                B[i] = index;
                break;
            }
        }
    }
    for (int i = 0; i < len; i++)
    {
        if (B[i] == -1)
        {
            printf("E ");
        }
        else
        {
            printf("%d ", B[i]);
        }
    }
    printf("\n%d\n", c);
}
void quad_probe(int A[], int len, int n)
{
    int B[len];
    for (int i = 0; i < len; i++)
    {
        B[i] = -1;
    }
    int c = 0;
    for (int i = 0; i < len; i++)
    {
        int j = 0;
        while (j < n)
        {
            int index = quad_hash(A[i], n, j);
            if (check(B, index, len))
            {
                c++;
                j++;
            }
            else
            {
                B[i] = index;
                break;
            }
        }
    }
    for (int i = 0; i < len; i++)
    {
        if (B[i] == -1)
        {
            printf("E ");
        }
        else
        {
            printf("%d ", B[i]);
        }
    }
    printf("\n%d\n", c);
}
void dob_probe(int A[], int len, int n)
{
    int B[len];
    for (int i = 0; i < len; i++)
    {
        B[i] = -1;
    }
    int c = 0;
    for (int i = 0; i < len; i++)
    {
        int j = 0;
        while (j < n)
        {
            int index = dob_hash(A[i], n, j);
            if (check(B, index, len))
            {
                c++;
                j++;
            }
            else
            {
                B[i] = index;
                break;
            }
        }
    }
    for (int i = 0; i < len; i++)
    {
        if (B[i] == -1)
        {
            printf("E ");
        }
        else
        {
            printf("%d ", B[i]);
        }
    }
    printf("\n%d", c);
}
int main()
{
    int n;
    scanf("%d", &n);
    int A[n];
    char c;
    int i;
    int len = 0;
    while (c != '\n')
    {
        scanf("%d%c", &i, &c);
        A[len] = i;
        len++;
    }
    lin_probe(A, len, n);
    quad_probe(A, len, n);
    dob_probe(A, len, n);
}