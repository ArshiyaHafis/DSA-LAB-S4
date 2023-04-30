#include <stdio.h>
struct heap
{
    int arr[100000];
    int length;
};
void heapify(struct heap *H, int index)
{
    int l = (2 * index) + 1;
    int r = (2 * index) + 2;
    int largest = index;
    if (l < H->length && H->arr[l] > H->arr[largest])
    {
        largest = l;
    }
    if (r < H->length && H->arr[r] > H->arr[largest])
    {
        largest = r;
    }
    if (largest != index)
    {
        int temp = H->arr[index];
        H->arr[index] = H->arr[largest];
        H->arr[largest] = temp;
        heapify(H, largest);
    }
}
void insert(struct heap *H, int x)
{
    H->arr[H->length] = x;
    H->length++;
    int ptr = H->length - 1;
    while (ptr > 0 && H->arr[((ptr - 1) / 2)] < H->arr[ptr])
    {
        int temp = H->arr[(ptr - 1) / 2];
        H->arr[(ptr - 1) / 2] = H->arr[ptr];
        H->arr[ptr] = temp;
        ptr = (ptr - 1) / 2;
    }
}
int extract_max(struct heap *H)
{
    int length = H->length;
    int max = H->arr[0];
    int key = H->arr[length - 1];
    H->arr[0] = key;
    // printf("[%d] ", H->arr[0]);
    H->length--;
    heapify(H, 0);
    return max;
}
void print(struct heap *H)
{
    for (int i = 0; i < H->length; i++)
    {
        printf("%d ", H->arr[i]);
    }
    printf("\n");
}
void k_max(struct heap *H, int k)
{
    while (k > 0)
    {
        printf("%d ", extract_max(H));
        // print(H);
        k--;
    }
}
int main()
{
    int t;
    scanf("%d", &t);
    while (t--)
    {
        struct heap *H, h;
        H = &h;
        for (int i = 0; i < 100000; i++)
        {
            H->arr[i] = '\0';
        }
        H->length = 0;
        int n;
        scanf("%d", &n);
        for (int i = 0; i < n; i++)
        {
            int k;
            scanf("%d", &k);
            insert(H, k);
        }
        int k;
        scanf("%d", &k);
        k_max(H, k);
        printf("\n");
    }
}