#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct heap
{
    struct vertex **v_list;
    int heap_size;
    int length;
};
struct node
{
    int adj_v;
    int weight;
    struct node *next;
};
struct graph
{
    int num_vert;
    int num_edges;
    struct node **list;
};
struct edge
{
    int weight;
    int u;
    int v;
};
struct vertex
{
    int priority;
    int key;
    int p;
};
struct node *createnode(int key)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->adj_v = key;
    temp->next = NULL;
    return temp;
}
struct edge *createedge(int wieght, int u, int v)
{
    struct edge *temp = (struct edge *)malloc(sizeof(struct edge));
    temp->weight = wieght;
    temp->u = u;
    temp->v = v;
    return temp;
}
struct vertex *createvertex(int priority, int p, int key)
{
    struct vertex *temp = (struct vertex *)malloc(sizeof(struct vertex));
    temp->p = p;
    temp->priority = priority;
    temp->key = key;
    return temp;
}
void insert(struct node *root, struct node *new)
{
    struct node *temp = root;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = new;
}
void print(struct graph *G)
{
    for (int i = 0; i < G->num_vert; i++)
    {
        struct node *temp = G->list[i];
        temp = temp->next;
        printf("%d ", i);
        while (temp != NULL)
        {
            printf("%d(%d) ", temp->adj_v, temp->weight);
            temp = temp->next;
        }
        printf("\n");
    }
}

void swap(struct heap *A, int a, int b)
{
    int temp = A->v_list[a]->key;
    A->v_list[a]->key = A->v_list[b]->key;
    A->v_list[b]->key = temp;

    temp = A->v_list[a]->p;
    A->v_list[a]->p = A->v_list[b]->p;
    A->v_list[b]->p = temp;

    temp = A->v_list[a]->priority;
    A->v_list[a]->priority = A->v_list[b]->priority;
    A->v_list[b]->priority = temp;
}
void print_pq(struct heap *A)
{
    for (int i = 0; i < A->heap_size + 1; i++)
    {
        printf("[%d %d]", A->v_list[i]->key, A->v_list[i]->priority);
    }
    printf("\n");
}
void min_heapify(struct heap *A, int i)
{
    int small = i;
    int l = (2 * i) + 1;
    int r = (2 * i) + 2;
    if (l < A->heap_size && A->v_list[small]->priority > A->v_list[l]->priority)
    {
        small = l;
    }
    if (r < A->heap_size && A->v_list[small]->priority > A->v_list[r]->priority)
    {
        small = r;
    }
    if (small != i)
    {
        swap(A, small, i);
        min_heapify(A, small);
    }
}
struct vertex *extract_min(struct heap *A)
{
    if (A->heap_size < 0)
    {
        return 0;
    }
    struct vertex *min = createvertex(0, 0, 0);
    min->key = A->v_list[0]->key;
    min->p = A->v_list[0]->p;
    min->priority = A->v_list[0]->priority;

    A->v_list[0]->key = A->v_list[A->heap_size]->key;
    A->v_list[0]->p = A->v_list[A->heap_size]->p;
    A->v_list[0]->priority = A->v_list[A->heap_size]->priority;
    A->heap_size = A->heap_size - 1;
    min_heapify(A, 0);
    return min;
}
void decrease_key(struct heap *A, int i, int key, int priority, int p)
{
    A->v_list[i] = createvertex(priority, p, key);
    while (i > 0 && A->v_list[(i - 1) / 2]->priority > A->v_list[i]->priority)
    {
        swap(A, (i - 1) / 2, i);
        i = (i - 1) / 2;
    }
    // print_pq(A);
}
void insert_pq(struct heap *A, int key, int priority, int p)
{
    A->heap_size = A->heap_size + 1;
    // printf("[%d] ", A->heap_size);
    decrease_key(A, A->heap_size, key, priority, p);
}
int check(struct heap *A, int key)
{
    for (int i = 0; i < A->heap_size + 1; i++)
    {
        if (A->v_list[i]->key == key)
        {
            return i;
        }
    }
    return -1;
}
int w(struct edge **edges, int u, int v, int len)
{
    for (int i = 0; i < len; i++)
    {
        if (edges[i]->u == u && edges[i]->v == v)
        {
            return edges[i]->weight;
        }
    }
}
int mst_prism(struct graph *G, int src, int min_dist[])
{
    struct edge **edges = (struct edge **)malloc(2 * G->num_edges * sizeof(struct edge *));
    int c = 0;
    for (int i = 0; i < G->num_vert; i++)
    {
        struct node *temp = G->list[i];
        while (temp != NULL)
        {
            if (i != temp->adj_v)
            {
                edges[c] = createedge(temp->weight, i, temp->adj_v);
                ++c;
            }
            temp = temp->next;
        }
    }
    struct heap aa, *A;
    A = &aa;
    A->heap_size = -1;
    A->v_list = (struct vertex **)malloc(G->num_vert * sizeof(struct vertex *));
    // initial single source
    min_dist[src] = 0;
    insert_pq(A, src, 0, -1);
    for (int i = 0; i < G->num_vert; i++)
    {
        if (i != src)
        {
            insert_pq(A, i, 10001, -1);
            min_dist[i] = 10001;
        }
    }
    // int mst_cost = 0;
    // printf("H");
    // print_pq(A);
    while (A->heap_size > -1) // while Q is not empty
    {
        struct vertex *u = extract_min(A);
        // printf("\n(access%d)", u->key);
        int min = u->priority;
        struct node *temp = G->list[u->key];

        temp = temp->next;
        while (temp != NULL) // iterating through adj[u]
        {
            // printf("`%d`", temp->adj_v);
            int j = check(A, temp->adj_v);
            // printf("*%d* ", j);
            if (j != -1)
            {
                struct vertex *v = A->v_list[j];
                int wi = w(edges, u->key, v->key, c); // weight of v
                // printf("(%d$%d$%d$%d$%d) ", temp->weight, u->priority, v->priority);
                if (temp->weight + u->priority < v->priority )
                {
                    // printf("(%d)", v->key);
                    min_dist[v->key] = temp->weight + u->priority;
                    decrease_key(A, j, v->key, temp->weight + u->priority, v->p);
                }
            }
            else{
                int wi = w(edges, u->key, temp->adj_v, c);
                // printf("(?%d %d %d %d %d?) ", u->priority, u->key, temp->adj_v, min_dist[temp->adj_v], wi);
                if(u->priority + wi < min_dist[temp->adj_v]){
                    min_dist[temp->adj_v] = u->priority + wi;
                }
            }
            temp = temp->next;
        }
        // printf("-->NEXT in QUEUE<--");
    }
    // printf("\n");
}

int main()
{
    int n;
    scanf("%d", &n);
    struct graph *G = (struct graph *)malloc(sizeof(struct graph));
    G->num_vert = n;
    G->num_edges = 0;
    G->list = (struct node **)malloc(n * sizeof(struct node *));
    for (int i = 0; i < n; i++)
    {
        G->list[i] = createnode(i);
    }
    for (int i = 0; i < n; i++)
    {
        int k;
        char c;
        scanf("%d%c", &k, &c);
        while (c != '\n')
        {
            scanf("%d%c", &k, &c);
            struct node *temp = createnode(k);
            insert(G->list[i], temp);
            G->num_edges++;
        }
    }
    G->num_edges = G->num_edges / 2;
    for (int i = 0; i < n; i++)
    {
        int k;
        scanf("%d", &k);
        struct node *temp = G->list[i];
        temp = temp->next;
        while (temp != NULL)
        {
            scanf("%d", &k);
            temp->weight = k;
            temp = temp->next;
        }
    }
    // print(G);
    while (1)
    {
        char str[4];
        scanf("%s", str);
        int min_dist[G->num_vert];
        if (strcmp(str, "apsp") == 0)
        {
            int k;
            scanf("%d", &k);
            mst_prism(G, k, min_dist);
            // printf("\n");
            for (int i = 0; i < G->num_vert; i++)
            {
                if (min_dist[i] == 10001)
                {
                    printf("INF ");
                }
                else
                {
                printf("%d ", min_dist[i]);
                }
            }
            printf("\n");
        }
        else if (strcmp(str, "sssp") == 0)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            mst_prism(G, x, min_dist);
            if (min_dist[y] == 10001)
            {
                printf("UNREACHABLE\n");
            }
            else
            {
                printf("%d\n", min_dist[y]);
            }
        }
        else if (strcmp(str, "stop") == 0)
        {
            break;
        }
    }
}
// 5
// 0 1 4
// 1 2 4
// 2 3
// 3 2
// 4 1 2 3
// 0 10 3
// 1 2 4
// 2 9
// 3 7
// 4 1 8 2
// apsp 0
// apsp 1
// apsp 2
// apsp 3
// apsp 4
// sssp 0 4