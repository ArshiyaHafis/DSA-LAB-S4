#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
struct node
{
    char fname[1000];
    char lname[1000];
    char gender[1];
    char dob[10];
    char dept[50];
    float cgpa;
    struct node *l;
    struct node *r;
    struct node *p;
};
// struct bst
// {
//     struct node *root;
// };
struct hashmap
{
    struct node **info;
};
struct node *create_node(char fname[], char lname[], char g[], char dob[], char dept[], float cgpa)
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    strcpy(temp->fname, fname);
    strcpy(temp->lname, lname);
    strcpy(temp->gender, g);
    strcpy(temp->dob, dob);
    strcpy(temp->dept, dept);
    temp->cgpa = cgpa;
    temp->p = NULL;
    temp->l = NULL;
    temp->r = NULL;
    return temp;
}
int hash(char a)
{
    return (a - 97) % 26;
}

int insert(char fname[], char lname[], char g[], char dob[], char dept[], float cgpa, struct hashmap *h)
{
    int hindex;
    int c = 0;
    if (isupper(fname[0]))
    {
        char a = tolower(fname[0]);
        // printf("%c %d ", a, a);
        hindex = hash(a);
    }
    else
    {
        hindex = hash(fname[0]);
    }
    // printf("%d %d", hindex, fname[0]);
    struct node *temp = create_node(fname, lname, g, dob, dept, cgpa);
    // printf("-->%f [%f]", cgpa, temp->cgpa);
    if (h->info[hindex] == NULL)
    {
        h->info[hindex] = temp;
        c = 0;
    }
    else
    {
        struct node *root = h->info[hindex], *temp1;
        while (root != NULL)
        {
            temp1 = root;
            if (strcmp(temp->fname, root->fname) > 0 || (strcmp(temp->fname, root->fname) == 0 && strcmp(temp->lname, root->lname) > 0))
            {
                // printf("r");
                root = root->r;
                c++;
            }
            else
            {
                // printf("l");
                root = root->l;
                c++;
            }
        }
        // printf("%s %s", temp->lname, temp1->lname);
        if (strcmp(temp->fname, temp1->fname) > 0 || (strcmp(temp->fname, temp1->fname) == 0 && strcmp(temp->lname, temp1->lname) > 0))
        {
            // printf("R");
            temp1->r = temp;
            temp->p = temp1;
        }
        else
        {
            // printf("L");
            temp1->l = temp;
            temp->p = temp1;
        }
    }
    return c;
}
void pre_order(struct node *temp)
{
    if (temp == NULL)
    {
        return;
    }
    printf("%s %s %f\n", temp->fname, temp->lname, temp->cgpa);
    pre_order(temp->l);
    pre_order(temp->r);
}
void print(struct hashmap *h)
{
    for (int i = 0; i < 26; i++)
    {
        if (h->info[i] != NULL)
        {
            // printf("[%d]", i);
            pre_order(h->info[i]);
        }
    }
}
struct node *search(struct node *temp, char fname[], char lname[], int *count)
{
    if ((strcmp(temp->fname, fname) == 0 && strcmp(temp->lname, lname) == 0) || temp == NULL)
    {
        return temp;
    }
    else
    {
        if (strcmp(fname, temp->fname) > 0 || (strcmp(fname, temp->fname) == 0 && strcmp(lname, temp->lname) > 0))
        {
            if (temp->r == NULL)
            {
                return NULL;
            }
            (*count)++;
            search(temp->r, fname, lname, count);
        }
        else
        {
            if (temp->l == NULL)
            {
                return NULL;
            }
            (*count)++;
            search(temp->l, fname, lname, count);
        }
    }
}
void locate(struct node *temp, char fname[], char lname[])
{
    if ((strcmp(temp->fname, fname) == 0 && strcmp(temp->lname, lname) == 0) || temp == NULL)
    {
        return;
    }
    else
    {
        // printf("%s %s\n", temp->lname, lname);
        if (strcmp(fname, temp->fname) > 0 || (strcmp(fname, temp->fname) == 0 && strcmp(lname, temp->lname) > 0))
        {
            if (temp->r == NULL)
            {
                return;
            }
            printf("R");
            locate(temp->r, fname, lname);
        }
        else
        {
            if (temp->l == NULL)
            {
                return;
            }
            printf("L");
            locate(temp->l, fname, lname);
        }
    }
}
int update(char fname[], char lname[], float cgpa, struct hashmap *h)
{
    int c = 0;
    int hindex;
    if (isupper(fname[0]))
    {
        char a = tolower(fname[0]);
        // printf("%c %d ", a, a);
        hindex = hash(a);
    }
    else
    {
        hindex = hash(fname[0]);
    }
    if (h->info[hindex] == NULL)
    {
        c=-1;
    }
    else
    {
        struct node *temp = search(h->info[hindex], fname, lname, &c);
        if (temp == NULL)
        {
            c=-1;
        }
        else
        {
            temp->cgpa = cgpa;
        }
    }
    return c;
}
void transplant(struct hashmap *h, int hindex, struct node *a, struct node *b)
{
    // printf("%s", T->lname);
    if (a->p == NULL)
    {
        // printf("p");
        h->info[hindex] = b;
    }
    else if (a->p->r == a)
    {
        // printf("r");
        a->p->r = b;
    }
    else
    {
        // printf("T");
        a->p->l = b;
    }
    if (b != NULL)
    {
        // printf("hy");
        b->p = a->p;
    }
    // printf("T->l : %s", T->lname);
}
struct node *min_value(struct node *node)
{
    while (node->l != NULL)
    {
        node = node->l;
    }
    return node;
}
int delete(struct hashmap *h, int hindex, struct node *node)
{
    int c = 0;
    if (node->r == NULL)
    {
        transplant(h, hindex, node, node->l);
        c = 1;
    }
    else if (node->l == NULL)
    {
        transplant(h, hindex, node, node->r);
        c = 1;
    }
    else
    {
        struct node *temp = min_value(node->r);
        // printf("H %s", temp->lname);
        if (temp->p != node)
        {
            // printf("r");
            transplant(h, hindex, temp, temp->r);
            temp->r = node->r;
            temp->r->p = temp;
            c++;
        }
        // printf("l %s", L->lname);
        transplant(h, hindex, node, temp);
        temp->l = node->l;
        temp->l->p = temp;
        c++;
        // printf("[%s]", L->lname);
    }
    return c;
}
int main()
{
    struct hashmap *h = (struct hashmap *)malloc(sizeof(struct hashmap));
    h->info = (struct node **)malloc(26 * sizeof(struct node *));
    for (int i = 0; i < 26; i++)
    {
        h->info[i] = NULL;
    }
    while (1)
    {
        char ch;
        scanf("%c", &ch);
        int k;
        if (ch == 'i')
        {
            char fname[1000];
            char lname[1000];
            char g[1];
            char dob[10];
            char dept[50];
            float cgpa;
            scanf("%s", fname);
            scanf("%s", lname);
            scanf("%s", g);
            scanf("%s", dob);
            // printf("^^%s^^", dob);
            scanf("%s", dept);
            scanf("%f", &cgpa);
            // printf("^^%f^^", cgpa);
            printf("%d\n", insert(fname, lname, g, dob, dept, cgpa, h));
        }
        if (ch == 'u')
        {
            char fname[1000];
            char lname[1000];
            float cgpa;
            scanf("%s%s%f", fname, lname, &cgpa);
            printf("%d\n", update(fname, lname, cgpa, h));
        }
        if (ch == 'l')
        {
            char fname[1000];
            char lname[1000];
            scanf("%s%s", fname, lname);
            int hindex;
            if (isupper(fname[0]))
            {
                char a = tolower(fname[0]);
                // printf("%c %d ", a, a);
                hindex = hash(a);
            }
            else
            {
                hindex = hash(fname[0]);
            }
            if (h->info[hindex] == NULL)
            {
                printf("-1\n");
            }
            if (search(h->info[hindex], fname, lname, &k) == NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d-", hindex);
                locate(h->info[hindex], fname, lname);
                printf("\n");
            }
        }
        if (ch == 'd')
        {
            char fname[1000];
            char lname[1000];
            scanf("%s%s", fname, lname);
            int hindex;
            if (isupper(fname[0]))
            {
                char a = tolower(fname[0]);
                // printf("%c %d ", a, a);
                hindex = hash(a);
            }
            else
            {
                hindex = hash(fname[0]);
            }
            if (h->info[hindex] == NULL)
            {
                printf("-1\n");
            }
            if (search(h->info[hindex], fname, lname, &k) == NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n", delete (h, hindex, search(h->info[hindex], fname, lname, &k)));
                // printf("%s", h->info[hindex]->lname);
            }
        }
        if (ch == 'p')
        {
            print(h);
        }
        if (ch == 'e')
        {
            break;
        }
    }
}
// i
// Ram Kumar F 18-05-2022 CSED 6.3
// i
// Ram Charan F 19-07-2022 CSED 6.3
// i
// Arshiya Hafis F 03-01-2004 CSED 5.4
// i
// Ram Path F 01-02-2021 MECH 6.7
// i
// Abin Mathew M 08-09-2003 CIVIL 8.9
// i
// Athif Khan M 01-02-2003 EEE 4.5