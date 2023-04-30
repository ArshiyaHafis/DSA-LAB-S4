#include <stdio.h>
#include <stdlib.h>
struct employee
{
    int eid;
    int rank;
    struct employee *p;
};
struct employee *make_set(int k)
{
    // printf("He");
    struct employee *new_node = (struct employee *)malloc(sizeof(struct employee));
    new_node->eid = k;
    new_node->p = new_node;
    new_node->rank = 0;
    return new_node;
}
struct employee *find_set_path(struct employee *temp)
{
    if (temp != temp->p)
    {
        temp->p = find_set_path(temp->p);
    }
    return temp->p;
}
int union_set(int x, int y, struct employee **list)
{
    struct employee *a = find_set_path(list[x]);
    struct employee *b = find_set_path(list[y]);
    if (a->rank < b->rank)
    {

        a->p = b;
        return b->eid;
    }
    else
    {
        b->p = a;
        if (a->rank == b->rank)
        {
            a->rank = a->rank + 1;
        }
        return a->eid;
    }
}
int find_teams(struct employee **list)
{
    struct employee **team = (struct employee **)malloc(1000 * sizeof(struct employee *));
    for (int i = 0; i < 1000; i++)
    {
        team[i] = NULL;
    }
    int c = 0;
    for (int i = 0; i < 1000; i++)
    {
        if (list[i] != NULL)
        {
            struct employee *a = find_set_path(list[i]);
            // printf("%d ", a->eid);
            if (c == 0)
            {
                c++;
                team[a->eid] = a;
            }
            else
            {
                int f = 0;
                for (int j = 0; j < 1000; j++)
                {
                    if (team[j] != NULL)
                    {
                        if (team[j] == a)
                        {
                            f = 1;
                            break;
                        }
                    }
                }
                if (f == 0)
                {
                    c++;
                    team[a->eid] = a;
                }
            }
        }
    }
    printf("%d\n", c);
}
int find_groups(struct employee **list)
{
    int g_count = 0;
    for (int i = 0; i < 1000; i++)
    {
        if (list[i] != NULL)
        {
            for (int j = i + 1; j < 1000; j++)
            {
                if (list[j] != NULL)
                {
                    if (find_set_path(list[i]) != find_set_path(list[j]))
                    {
                        g_count++;
                    }
                }
            }
        }
    }
    if (g_count == 0)
    {
        printf("-1\n");
    }
    else
    {
        printf("%d\n", g_count);
    }
}
int valid_group(struct employee **list, int x, int y)
{
    if (x < y)
    {
        if (find_set_path(list[x]) != find_set_path(list[y]))
        {
            return 1;
        }
        return 0;
    }
    return 0;
}
void print_set(struct employee **list)
{
    for (int i = 0; i < 1000; i++)
    {
        if (list[i] != NULL)
        {
            printf("%d %d\n", list[i]->eid, list[i]->p->eid);
        }
    }
}
int main()
{
    struct employee **list = (struct employee **)malloc(1000 * sizeof(struct employee *));
    for (int i = 0; i < 1000; i++)
    {
        list[i] = NULL;
    }
    while (1)
    {
        char ch;
        scanf("%c", &ch);

        if (ch == 't')
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if (list[x] == NULL)
            {
                list[x] = make_set(x);
            }

            if (list[y] == NULL)
            {
                list[y] = make_set(y);
            }
            union_set(x, y, list);
        }
        if (ch == 'T')
        {
            find_teams(list);
        }
        if (ch == 'd')
        {
            find_groups(list);
        }
        if (ch == 'v')
        {
            int x, y;
            scanf("%d%d", &x, &y);
            if ((list[x] != NULL && list[y] != NULL) && (valid_group(list, x, y)))
            {
                printf("1\n");
            }
            else
            {
                printf("-1\n");
            }
        }
        if (ch == 'p')
        {
            print_set(list);
        }
        if (ch == 'e')
        {
            break;
        }
    }
}