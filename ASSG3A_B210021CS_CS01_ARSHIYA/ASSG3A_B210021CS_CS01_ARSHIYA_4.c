#include <stdio.h>
#include <stdlib.h>
struct node
{
    int key;
    struct node *next;
};
struct ll
{
    struct node *head;
    int length;
};
struct node *newNode(int d)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->key = d;
    temp->next = NULL;
    return temp;
}
void print(struct ll *L)
{
    struct node *temp = L->head;
    while (temp != NULL)
    {
        printf("%d ", temp->key);
        temp = temp->next;
    }
    printf("\n");
}
void insert(struct ll *L, int d)
{
    struct node *temp = newNode(d);
    if (L->head == NULL)
    {
        L->head = temp;
    }
    else
    {
        struct node *temp1 = L->head;
        if (temp1->key >= d)
        {
            L->head = temp;
            temp->next = temp1;
        }
        else if (temp1->next == NULL && temp1->key < d)
        {
            temp1->next = temp;
        }
        else
        {
            struct node *temp2 = temp1;
            while (temp1 != NULL && temp1->key < d)
            {
                temp2 = temp1;
                temp1 = temp1->next;
            }
            temp2->next = temp;
            temp->next = temp1;
        }
    }
    L->length++;
}
int delete(struct ll *L)
{
    struct node *temp = L->head;
    L->head = L->head->next;
    L->length--;
    return temp->key;
}
int min_rope(struct ll *L)
{
    int cost = 0;
    struct node *temp = L->head;
    while (L->length > 1)
    {
        int min = delete (L);
        int sec_min = delete (L);
        cost += (min + sec_min);
        // printf("[%d] <%d %d>", cost, min, sec_min);
        // print(L);
        insert(L, min + sec_min);
    }
    return cost;
}
int main()
{
    struct ll l, *L;
    L = &l;
    L->length = 0;
    L->head = NULL;
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        int k;
        scanf("%d", &k);
        insert(L, k);
    }
    // print(L);
    printf("%d ", min_rope(L));

    return 0;
}
