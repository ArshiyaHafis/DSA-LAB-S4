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
    int smallest = index;
    if (l < H->length && H->arr[l] < H->arr[smallest])
    {
        smallest = l;
    }
    if (r < H->length && H->arr[r] < H->arr[smallest])
    {
        smallest = r;
    }
    if (smallest != index)
    {
        int temp = H->arr[index];
        H->arr[index] = H->arr[smallest];
        H->arr[smallest] = temp;
        heapify(H, smallest);
    }
}
void insert(struct heap *H, int x)
{
    H->arr[H->length] = x;
    H->length++;
    int ptr = H->length - 1;
    while (ptr > 0 && H->arr[((ptr - 1) / 2)] > H->arr[ptr])
    {
        int temp = H->arr[(ptr - 1) / 2];
        H->arr[(ptr - 1) / 2] = H->arr[ptr];
        H->arr[ptr] = temp;
        ptr = (ptr - 1) / 2;
    }
}
int decrease_key(struct heap *H, int x, int k)
{
    int i;
    for (i = 0; i < H->length; i++)
    {
        if (H->arr[i] == x)
        {
            H->arr[i] = k;
            break;
        }
    }
    int ptr = i;
    while (ptr >= 0 && H->arr[((ptr - 1) / 2)] > H->arr[ptr])
    {
        int temp = H->arr[(ptr - 1) / 2];
        H->arr[(ptr - 1) / 2] = H->arr[ptr];
        H->arr[ptr] = temp;
        ptr = (ptr - 1) / 2;
    }
    return k;
}
int find_min(struct heap *H)
{
    return H->arr[0];
}
int extract_min(struct heap *H)
{
    int length = H->length;
    int min = H->arr[0];
    int key = H->arr[length - 1];
    H->arr[0] = key;
    // printf("[%d] ", H->arr[0]);
    H->length--;
    heapify(H, 0);
    return min;
}
int delete(struct heap *H, int x)
{
    decrease_key(H, x, -1000000);
    extract_min(H);
    return x;
}
int find(struct heap *H, int k){
	for(int i=0; i<H->length; i++){
		if(H->arr[i]==k){
			return 1;
			}
			}
	return -1;
}
void print(struct heap *H)
{
    for (int i = 0; i < H->length; i++)
    {
        printf("%d ", H->arr[i]);
    }
    printf("\n");
}
int main()
{
    struct heap *H, h;
    H = &h;
    for (int i = 0; i < 100000; i++)
    {
        H->arr[i] = '\0';
    }
    H->length = 0;
    while (1)
    {
        char ch;
        int k;
        int y, z;
        scanf("%c", &ch);
        if (ch == 'i')
        {
            scanf("%d", &k);
            insert(H, k);
        }
        if (ch == 'p')
        {
            print(H);
        }
        if (ch == 'r')
        {
        	
            scanf("%d%d", &y, &z);
            if(y<z){
            	printf("-1\n");
            	}
            	else{
            int f = find(H, y);
            if(f==1){
            printf("%d \n", decrease_key(H, y, z));
            }
            else{
            printf("%d \n", f);}}
       
        }
        if (ch == 'd')
        {
            scanf("%d", &k);
            int f = find(H, k);
            if(f==1){
            printf("%d \n", delete (H, k));
            }
            else{
            printf("%d \n", f);}
        }
        if (ch == 'g')
        {
            printf("%d \n", find_min(H));
        }
        if (ch == 'x')
        {
            extract_min(H);
            print(H);
        }
        if (ch == 'e')
        {
            break;
        }
    }
}
