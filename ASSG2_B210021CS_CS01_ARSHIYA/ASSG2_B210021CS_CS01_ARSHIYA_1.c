#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node
{
    char name[1000];
    char rno[9];
    int age;
    struct node *next;
};
struct hashmap
{
    struct node **info;
};
int hash(char a[], int age)
{
    int sum = age;
    for (int i = 0; i < strlen(a); i++)
    {
        sum = sum + a[i];
    }
    return sum % 4;
}
struct node *create_node(char name[], char rno[], int age)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->age = age;
    strcpy(temp->name, name);
    strcpy(temp->rno, rno);
    temp->next = NULL;
    return temp;
}
void insert(char name[], char rno[], int age, struct hashmap *h)
{
    int hindex = hash(name, age);
    // printf("hindex : %d", hindex);
    struct node *temp = create_node(name, rno, age);
    if (h->info[hindex] == NULL)
    {
        h->info[hindex] = temp;
    }
    else
    {
        // printf("o");
        h->info[hindex]->next = temp;

        // temp->next = h->info[hindex];
        // h->info[hindex] = temp;
    }
    // printf("%s %s\n", h->info[hindex]->name, h->info[hindex]->rno);
}
void count(int k, struct hashmap *h)
{
    // printf("%d f %d", k, h->info[k]->age);
    if (h->info[k] == NULL)
    {
        printf("0");
    }
    else
    {
        struct node *temp = h->info[k];
        int c = 0;
        while (temp != NULL)
        {
            c++;
            temp = temp->next;
        }
        printf("%d ", c);
        temp = h->info[k];
        while (temp != NULL)
        {
            printf("%s ", temp->name);
            temp = temp->next;
        }
    }
}
void group(int k, char a[], struct hashmap *h)
{
    if (h->info[k] == NULL)
    {
        printf("Empty");
    }
    else
    {
        struct node *temp = h->info[k];
        int c = 0;
        while (temp != NULL)
        {
            if (temp->rno[7] == toupper(a[0]) && temp->rno[8] == toupper(a[1]))
            {
                printf("%s ", temp->name);
                c++;
            }
            temp = temp->next;
        }
        if (c == 0)
        {
            printf("-1");
        }
    }
}
int main()
{
    int n;
    scanf("%d", &n);
    struct hashmap *h = (struct hashmap *)malloc(sizeof(struct hashmap));
    h->info = (struct node **)malloc(4 * sizeof(struct node *));
    struct node input[n];
    for (int i = 0; i < 4; i++)
    {
        h->info[i] = NULL;
    }
    for (int i = 0; i < n; i++)
    {
        char name[1000];
        char rno[9];
        int age;
        scanf("%s%s%d", input[i].name, input[i].rno, &input[i].age);
        insert(input[i].name, input[i].rno, input[i].age, h);
    }
    // for (int i = 0; i < n; i++)
    // {
    //     printf(" %d %d ", i, h->info[i]->age);
    // }
    while (1)
    {
        char ch;
        scanf("%c", &ch);
        if (ch == 'c')
        {
            int k;
            scanf("%d", &k);
            count(k, h);
            printf("\n");
        }
        if (isdigit(ch))
        {
            int num = ch - '0';
            // printf("%d", num);
            char a[2];
            scanf("%s", a);
            group(num, a, h);
            printf("\n");
        }
        if (ch == 'e')
        {
            break;
        }
    }
}