#include <stdio.h>
#include <stdlib.h>
struct node
{
    int key;
    int rank;
    struct node *p;
};
struct count
{
    int rp;
    int nrp;
    int rnp;
    int nrnp;
};
struct node *make_set(int k)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->key = k;
    new_node->p = new_node;
    new_node->rank = 0;
    return new_node;
}
struct node *find_set_path(struct node *temp, int *c)
{
    (*c)++;
    if (temp != temp->p)
    {
        temp->p = find_set_path(temp->p, c);
    }
    return temp->p;
}
struct node *find_set_npath(struct node *temp, int *c)
{
    (*c)++;
    if (temp != temp->p)
    {
        return find_set_npath(temp->p, c);
    }
    return temp->p;
}
int union_set_both(int x, int y, struct node **list0, int *c)
{
    struct node *a = find_set_path(list0[x], c);
    struct node *b = find_set_path(list0[y], c);
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
int union_set_rank_npath(int x, int y, struct node **list1, int *c)
{
    struct node *a = find_set_npath(list1[x], c);
    struct node *b = find_set_npath(list1[y], c);
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
int union_set_neither(int x, int y, struct node **list2, int *c)
{
    struct node *a = find_set_npath(list2[x], c);
    struct node *b = find_set_npath(list2[y], c);
    if (a != b)
    {
        b->p = a;
    }
    return a->key;
}
int union_set_nrank_path(int x, int y, struct node **list3, int *c)
{
    struct node *a = find_set_path(list3[x], c);
    struct node *b = find_set_path(list3[y], c);
    if (a != b)
    {
        b->p = a;
    }
    return a->key;
}
int main()
{
    struct node **list0 = (struct node **)malloc(10000 * sizeof(struct node *));
    struct node **list1 = (struct node **)malloc(10000 * sizeof(struct node *));
    struct node **list2 = (struct node **)malloc(10000 * sizeof(struct node *));
    struct node **list3 = (struct node **)malloc(10000 * sizeof(struct node *));
    struct count *C = (struct count *)malloc(sizeof(struct count));
    C->nrnp = 0;
    C->nrp = 0;
    C->rnp = 0;
    C->rp = 0;
    for (int i = 0; i < 10000; i++)
    {
        list0[i] = NULL;
        list1[i] = NULL;
        list2[i] = NULL;
        list3[i] = NULL;
    }
    while (1)
    {
        char ch;
        scanf("%c", &ch);
        if (ch == 'm')
        {
            int k;
            scanf("%d", &k);
            struct node *temp0 = make_set(k);
            struct node *temp1 = make_set(k);
            struct node *temp2 = make_set(k);
            struct node *temp3 = make_set(k);
            if (list0[k] == NULL)
            {
                list0[k] = temp0;
                list1[k] = temp1;
                list2[k] = temp2;
                list3[k] = temp3;
                printf("%d\n", k);
            }
            else
            {
                printf("-1\n");
            }
        }
        if (ch == 'f')
        {
            int k;
            scanf("%d", &k);
            if (list0[k] == NULL)
            {
                printf("-1 -1 -1 -1\n");
                C->nrnp++;
                C->rnp++;
                C->nrp++;
                C->rp++;
            }
            else
            {
                printf("%d ", find_set_npath(list3[k], &C->nrnp)->key);
                printf("%d ", find_set_npath(list1[k], &C->rnp)->key);
                printf("%d ", find_set_path(list2[k], &C->nrp)->key);
                printf("%d\n", find_set_path(list0[k], &C->rp)->key);
                }
            
        }
        if (ch == 'u')
        {
            int x, y;
            scanf("%d%d", &x, &y);
            printf("%d ", union_set_neither(x, y, list3, &C->nrnp));
            printf("%d ", union_set_rank_npath(x, y, list1, &C->rnp));
            printf("%d ", union_set_nrank_path(x, y, list2, &C->nrp));
            printf("%d\n", union_set_both(x, y, list0, &C->rp));
        }
        if (ch == 's')
        {
            printf("%d %d %d %d\n", C->nrnp, C->rnp, C->nrp, C->rp);
            break;
        }
    }
}
