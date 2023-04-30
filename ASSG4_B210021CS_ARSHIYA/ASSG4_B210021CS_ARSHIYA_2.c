#include <stdio.h>
struct queue
{
    int data[10000];
    int head;
    int tail;
    int length;
};
int queue_full(struct queue *Q)
{
    int n = Q->length;
    if ((Q->tail + 1) % n == Q->head)
    {
        // printf("%d %d\n", Q->tail, Q->head);
        return 1;
    }
    return 0;
}
int queue_empty(struct queue *Q)
{
    if (Q->head == Q->tail)
    {
        // printf("%d %d\n", Q->head, Q->tail);
        return 1;
    }
    return 0;
}
void enqueue(struct queue *Q, int key)
{
    if (queue_full(Q))
    {
        //printf("FULL\n");
    }
    else
    {
        int n = Q->length;
        Q->data[Q->tail] = key;
        Q->tail = (Q->tail + 1) % n;
    }
    // printf("%d %d\n", Q->head, Q->tail);
}
int dequeue(struct queue *Q)
{
    int n = Q->length;
    int element = Q->data[Q->head];
    Q->head = (Q->head + 1) % n;

    return element;
}
int main()
{
    struct queue qq, *Q;
    Q = &qq;
    Q->head = 0;
    Q->tail = 0;
    int n;
    scanf("%d", &n);
    Q->length = n;
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
    /*for(int i=0; i<n; i++){
    	for(int j=0; j<n; j++){
    		printf("%d ", A[i][j]);
    	}
    	printf("\n");
    }*/
    enqueue(Q, 0);
    int c = 0;
    L[c] = 0;
    while (!queue_empty(Q))
    {
        int visit = dequeue(Q);
        // printf("[%d] ", visit);
        for (int i = 1; i < n; i++)
        {
            if (A[visit][i] != -1)
            {
                int f = 0;
                for (int j = 0; j < c+1; j++)
                {
                    if (A[visit][i] == L[j])
                    {
                        f = 1;
                        break;
                    }
                }
                if (f == 0)
                {
                    enqueue(Q, A[visit][i]);
                    c++;
                    L[c] = A[visit][i];
                }
            }
        }
    }
    for (int i = 0; i < c + 1; i++)
    {
        printf("%d ", L[i]);
    }
}
