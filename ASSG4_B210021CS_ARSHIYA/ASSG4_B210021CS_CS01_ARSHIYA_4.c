#include <stdio.h>
#include <stdlib.h>
// for adacency list
struct node
{
    int adj_v;
    int weight;
    struct node *next;
};
// for graph
struct graph
{
    int num_vert;
    int num_edges;
    struct node **list;
};
// for relation b/w vertices and get wieght
struct edge
{
    int weight;
    int u;
    int v;
};
// for visited nodes - prism
struct vertex
{
    int priority;
    int key;
    int p;
};
// for priority queue - prims
struct heap
{
    struct vertex **v_list;
    int heap_size;
    int length;
};
// for set of visited nodes - kruskal
struct ds_node
{
    int key;
    int rank;
    struct ds_node *p;
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
struct ds_node *make_set(int k)
{
    struct ds_node *new_node = (struct ds_node *)malloc(sizeof(struct ds_node));
    new_node->key = k;
    new_node->p = new_node;
    new_node->rank = 0;
    return new_node;
}

// inserting into tree
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

// prims functions
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
int mst_prism(struct graph *G)
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
    insert_pq(A, 0, 0, -1);
    for (int i = 1; i < G->num_vert; i++)
    {
        insert_pq(A, i, 10001, -1);
    }
    int mst_cost = 0;
    while (A->heap_size > -1)
    {
        struct vertex *u = extract_min(A);
        // printf("[%d : %d + %d] ", u->key, u->priority, mst_cost);
        mst_cost = mst_cost + u->priority;
        struct node *temp = G->list[u->key];
        // printf("[%d]", temp->adj_v);
        temp = temp->next;
        while (temp != NULL) // iterating through adj[u]
        {
            int j = check(A, temp->adj_v);
            // printf("(check - %d)", j);
            if (j != -1)
            {
                struct vertex *v = A->v_list[j];
                int wi = w(edges, u->key, v->key, c);
                // printf("[%d - (w%d %dw)] ", v->key, wi, v->priority);
                if (wi < v->priority)
                {
                    decrease_key(A, j, v->key, wi, v->p);
                    // v->priority = wi;
                }
            }
            temp = temp->next;
            // print_pq(A);
            // printf("next");
        }
    }
    return mst_cost;
}

// kruskal functions
struct ds_node *find_path(struct ds_node *temp)
{
    if (temp != temp->p)
    {
        temp->p = find_path(temp->p);
    }
    return temp->p;
}
int rank_union(int x, int y, struct ds_node **list)
{
    struct ds_node *a = find_path(list[x]);
    struct ds_node *b = find_path(list[y]);
    if (a->rank < b->rank)
    {
        a->p = b;
        return b->key;
    }
    else
    {
        b->p = a;
        if (a->rank == b->rank)
        {
            a->rank = a->rank + 1;
        }
        return a->key;
    }
}
int partition(struct edge **edges, int low, int high)
{
    int i = low - 1;
    struct edge *pivot = edges[high];
    for (int j = low; j < high; j++)
    {
        if (edges[j]->weight <= pivot->weight)
        {
            i++;
            struct edge *temp = edges[i];
            edges[i] = edges[j];
            edges[j] = temp;
        }
    }
    struct edge *temp = edges[i + 1];
    edges[i + 1] = edges[high];
    edges[high] = temp;
    return (i + 1);
}
void quick_sort(struct edge **edges, int low, int high)
{
    if (low < high)
    {
        int pi = partition(edges, low, high);
        quick_sort(edges, low, pi - 1);
        quick_sort(edges, pi + 1, high);
    }
}
int mst_kruskal(struct graph *G)
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
    // printf("done %d[%d]", c, (G->num_edges * 2) - 1);
    struct ds_node **list = (struct ds_node **)malloc(G->num_vert * sizeof(struct ds_node *));
    for (int i = 0; i < G->num_vert; i++)
    {
        list[i] = make_set(i);
    }
    quick_sort(edges, 0, (G->num_edges * 2) - 1);
    int mst_cost = 0;
    // printf("sirted");
    // for (int i = 0; i < c; i++)
    // {
    //     printf("%d %d %d\n", edges[i]->u, edges[i]->v, edges[i]->weight);
    // }
    for (int i = 0; i < 2 * G->num_edges; i++)
    {
        if (find_path(list[edges[i]->u]) != find_path(list[edges[i]->v]))
        {
            rank_union(edges[i]->u, edges[i]->v, list);
            mst_cost = mst_cost + edges[i]->weight;
        }
    }
    return mst_cost;
}

int main()
{
    int ch;
    scanf("%c", &ch);
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
    if (ch == 'a')
    {
        printf("%d", mst_kruskal(G));
    }
    if (ch == 'b')
    {
        printf("%d ", mst_prism(G));
    }
}