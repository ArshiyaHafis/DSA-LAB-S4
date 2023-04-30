#include <stdio.h>
#include <stdlib.h>
struct node
{
    struct node *left;
    struct node *right;
    int color;
    int key;
};
struct rbt
{
    struct node *root;
};
struct node *create_node(int k)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->key = k;
    new_node->color = 1;
    return new_node;
};
struct node *left_rotate(struct node *temp)
{
    struct node *right_child = temp->right;
    temp->right = right_child->left;
    right_child->left = temp;

    return right_child;
}

struct node *right_rotate(struct node *temp)
{
    struct node *left_child = temp->left;
    temp->left = left_child->right;
    left_child->right = temp;

    return left_child;
}

struct node *rbt_insert(struct node *r, struct node *x)
{
    if (r == NULL)
    {
        return x;
    }
    else
    {
        if (x->key < r->key)
        {
            r->left = rbt_insert(r->left, x);
            if (r->left->color == 1)
            {
                if ((r->left->left != NULL && r->left->left->color == 1) ||
                    (r->left->right != NULL && r->left->right->color == 1))
                {
                    if (r->right != NULL && r->right->color == 1)
                    {
                        r->color = 1;
                        r->left->color = 0;
                        r->right->color = 0;
                        return r;
                    }
                    else
                    {
                        if (r->left->right != NULL && r->left->right->color == 1)
                        {
                            r->left = left_rotate(r->left);
                        }
                        r = right_rotate(r);
                        r->right->color = 1;
                        r->color = 0;
                        return r;
                    }
                }
                else
                {
                    return r;
                }
            }
            else
            {
                return r;
            }
        }
        else
        {
            r->right = rbt_insert(r->right, x);
            if (r->right->color == 1)
            {
                if ((r->right->right != NULL && r->right->right->color == 1) ||
                    (r->right->left != NULL && r->right->left->color == 1))
                {
                    if (r->left != NULL && r->left->color == 1)
                    {
                        r->color = 1;
                        r->right->color = 0;
                        r->left->color = 0;
                        return r;
                    }
                    else
                    {
                        if (r->right->left != NULL && r->right->left->color == 1)
                        {
                            r->right = right_rotate(r->right);
                        }

                        r = left_rotate(r);
                        r->left->color = 1;
                        r->color = 0;
                        return r;
                    }
                }
                else
                {
                    return r;
                }
            }
            else
            {
                return r;
            }
        }
    }
}
void print(struct node *temp)
{
    if (temp == NULL)
    {
        printf("( ) ");
        return;
    }
    printf("( ");
    printf("%d ", temp->key);
    if (temp->color == 1)
    {
        printf("R ");
    }
    else
    {
        printf("B ");
    }
    print(temp->left);
    print(temp->right);
    printf(") ");
}
int main()
{
    char key[8];
    struct rbt *R, r;
    R = &r;
    R->root = NULL;
    for (int i = 0; i < 8; i++)
    {
        key[i] = '\0';
    }
    scanf("%s", key);
    while (key[0] != 't')
    {
        int num = atoi(key);
        struct node *temp = create_node(num);
        R->root = rbt_insert(R->root, temp);
        R->root->color = 0;
        print(R->root);
        printf("\n");
        scanf("%s", key);
    }
    return 0;
}