#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    int deg;
    struct node *p;
    struct node *c;
    struct node *s;
};
struct heap
{
    struct node *head;
};
struct node *create_node(int k)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->c = NULL;
    new_node->deg = 0;
    new_node->data = k;
    new_node->p = NULL;
    new_node->s = NULL;
    return new_node;
}
struct heap *makeheap()
{
    struct heap *temp = (struct heap *)malloc(sizeof(struct heap));
    temp->head = NULL;
    return temp;
}
void printheap(struct node *p)
{
    if (p->deg == 0)
    {
        return;
    }
    else
    {
        while (p->c != NULL)
        {
            struct node *x = p->c;
            while (x != NULL)
            {
                printf("%d ", x->data);
                x = x->s;
            }
            p = p->c;
        }
    }
}
void print(struct heap *H)
{
    struct node *p;
    if (H == NULL)
    {
        return;
    }
    p = H->head;
    // printf("%d ", H->head->data);
    while (p != NULL)
    {
        printf("%d ", p->data);
        struct node *temp = p;
        // printheap(p);
        p = p->s;
    }
    printf("\n");
}
struct node *link(struct node *y, struct node *z)
{
    y->p = z;
    y->s = z->c;
    z->c = y;
    z->deg = z->deg + 1;
}
struct heap *merge(struct heap *H1, struct heap *H2)
{
    struct heap *H = makeheap();
    struct node *y = H1->head;
    struct node *z = H2->head;
    // printf("[*%d]", z->data);
    if (y != NULL)
    {
        if (z != NULL && y->deg <= z->deg)
        {
            // printf("l");
            H->head = y;
            y = y->s;
        }
        else if (z != NULL && y->deg > z->deg)
        {
            // printf("g");
            H->head = z;
            z = z->s;
        }
        else
        {
            H->head = y;
            y = y->s;
        }
    }
    else
    {
        H->head = z;
        z = z->s;
    }
    struct node *x = H->head;
    // printf("_%d_ ", x->data);
    while (y != NULL && z != NULL)
    {
        // printf("here");
        if (y->deg < z->deg)
        {
            // printf("y");
            x->s = y;
            y = y->s;
        }
        else
        {
            // printf("z:%d:", z->data);
            x->s = z;
            z = z->s;
        }
        x = x->s;
    }
    if (y != NULL)
    {
        x->s = y;
    }
    if (z != NULL)
    {
        x->s = z;
    }
    return H;
}

struct heap *heap_union(struct heap *H1, struct heap *H2)
{
    struct heap *H = makeheap();
    H = merge(H1, H2);
    if (H == NULL)
        return H;
    struct node *prev_x = NULL;
    struct node *x = H->head;
    struct node *next_x = x->s;
    while (next_x != NULL)
    {
        if ((x->deg != next_x->deg) ||
            ((next_x->s != NULL) && (next_x->s)->deg == x->deg))
        {
            prev_x = x;
            x = next_x;
        }
        else
        {
            if (x->data <= next_x->data)
            {
                x->s = next_x->s;
                link(next_x, x);
            }
            else
            {
                if (prev_x == NULL)
                {
                    H->head = next_x;
                }
                else
                {
                    prev_x->s = next_x;
                }
                link(x, next_x);
                x = next_x;
            }
        }
        next_x = x->s;
    }
    return H;
}
struct node *find(struct node *temp, int k)
{
    struct node *x = temp;
    struct node *p = NULL;
    if (x->data == k)
    {
        p = x;
        return p;
    }
    if (x->c != NULL && p == NULL)
    {
        p = find(x->c, k);
    }

    if (x->s != NULL && p == NULL)
    {
        p = find(x->s, k);
    }
    return p;
}

void decrease_key(struct heap *H, int i, int k)
{
    int temp;
    struct node *p;
    struct node *y;
    struct node *z;
    p = find(H->head, i);
    p->data = k;
    y = p;
    z = p->p;
    while (z != NULL && y->data < z->data)
    {
        temp = y->data;
        y->data = z->data;
        z->data = temp;
        y = z;
        z = z->p;
    }
}
struct heap *insert(struct heap *H, struct node *x)
{
    struct heap *H1 = makeheap();
    x->p = NULL;
    x->c = NULL;
    x->s = NULL;
    x->deg = 0;
    H1->head = x;
    H = heap_union(H, H1);
    return H;
}
struct node *revert_list(struct heap *Hr, struct node *y)
{
    if (y->s != NULL)
    {
        revert_list(Hr, y->s);
        (y->s)->s = y;
    }
    else
    {
        Hr->head = y;
    }
    return y;
}
struct heap *extract_min(struct heap *H1)
{
    struct node *t = NULL;
    struct node *x = H1->head;
    struct heap *Hr = makeheap();
    struct node *p;
    if (x == NULL)
    {
        printf("NULL");
        return NULL;
    }
    int min = x->data;
    p = x;
    while (p->s != NULL)
    {
        if ((p->s)->data < min)
        {
            min = (p->s)->data;
            t = p;
            x = p->s;
        }
        p = p->s;
    }
    if (t == NULL && x->s == NULL)
        H1->head = NULL;
    else if (t == NULL)
        H1->head = x->s;
    else if (t->s == NULL)
        t = NULL;
    else
        t->s = x->s;
    if (x->c != NULL)
    {
        // printf("%d ", x->c->data);
        struct node *temp = revert_list(Hr, x->c);
        // printf("here");
        temp->s = NULL;
        (x->c)->s = NULL;
    }
    // print(Hr);

    H1 = heap_union(H1, Hr);
    // printf("gagaga");
    // printf("%d \n", min);
    return H1;
}
int minimum(struct heap *H)
{
    struct node *temp = H->head;
    if (temp == NULL)
    {
        return 0;
    }
    int min = temp->data;
    while (temp->s != NULL)
    {
        if (temp->s->data < min)
        {
            min = temp->s->data;
        }
        temp = temp->s;
    }
    return min;
}
struct heap *delete(struct heap *H, int k)
{
    decrease_key(H, k, -1000);
    H = extract_min(H);
    return H;
}
int main()
{
    struct heap *H1, h1;
    struct heap *H2, h2;
    H1 = &h1;
    H1->head = NULL;
    H2 = &h2;
    H2->head = NULL;
    while (1)
    {
        char ch;
        scanf("%c", &ch);
        if (ch == 'i')
        {
            int k;
            scanf("%d", &k);
            struct node *x = create_node(k);
            H1 = insert(H1, x);
        }
        if (ch == 'j')
        {
            int k;
            scanf("%d", &k);
            struct node *x = create_node(k);
            H2 = insert(H2, x);
        }
        if (ch == 'p')
        {
            int k;
            scanf("%d", &k);
            if (k == 1)
            {
                print(H1);
            }
            if (k == 2)
            {
                print(H2);
            }
        }
        if (ch == 'u')
        {
            H1 = heap_union(H1, H2);
            print(H1);
        }
        if (ch == 'm')
        {
            printf("%d\n", minimum(H1));
        }
        if (ch == 'r')
        {
            int y, z;
            scanf("%d%d", &y, &z);
            if (y >= z && find(H1->head, y))
            {
                printf("%d\n", z);
                decrease_key(H1, y, z);
            }
            else
            {
                printf("-1 \n");
            }
        }
        if (ch == 'x')
        {
            printf("%d\n", minimum(H1));
            H1 = extract_min(H1);
            // print(H1);
        }
        if (ch == 'd')
        {
            int k;
            scanf("%d", &k);
            struct node *p = find(H1->head, k);
            if (p == NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n", k);
                H1 = delete (H1, k);
            }
        }
        if (ch == 'e')
        {
            break;
        }
    }
}
// i 1
// j 2
// i 3
// j 4
// i 5
// j 6
// i 7
// j 8
// i 9
// j 10
// i 11
// j 12
// i 13
// j 14
// p 1
// p 2
// m
// r 9 2
// p 1
// x
// p 1
// u
// d 7
// p 1
// e

// i 10
// i 20
// i 30
// i 40
// i 50
// p 1
// m
// x
// p 1
// r 50 46
// p 1
// r 70 5
// j 60
// j 70
// j 80
// p 2
// u
// e
