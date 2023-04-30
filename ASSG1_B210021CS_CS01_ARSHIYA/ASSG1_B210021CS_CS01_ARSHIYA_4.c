#include <stdio.h>
#include <stdlib.h>
struct bst
{
    int key;
    struct bst *p;
    struct bst *left;
    struct bst *right;
};
struct bstroot
{
    struct bst *root;
};
struct bst *create_node(int k)
{
    struct bst *new_node = (struct bst *)malloc(sizeof(struct bst));
    new_node->key = k;
    new_node->p = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

struct bst *maxvalue(struct bst *temp)
{
    struct bst *temp1;
    while (temp != NULL) // traverse to leaf node of left
    {
        temp1 = temp;
        temp = temp->right;
    }
    return temp1;
}
struct bst *minvalue(struct bst *temp)
{
    struct bst *temp1;
    while (temp != NULL) // traverse to leaf node of right
    {
        temp1 = temp;
        temp = temp->left;
    }
    return temp1;
}
void transplant(struct bstroot *T, struct bst *a, struct bst *b)
{
    if (a->p == NULL)
    {
        T->root = b;
    }
    else if (a == a->p->left)
    {
        a->p->left = b;
    }
    else
    {
        a->p->right = b;
    }
    if (b != NULL)
    {
        b->p = a->p;
    }
}
void insert(int k, struct bstroot *T)
{
    struct bst *new_node = create_node(k);
    if (T->root == NULL)
    {
        T->root = new_node;
    }
    else
    {
        struct bst *temp = T->root, *temp1;
        while (temp != NULL)
        {
            temp1 = temp;
            if (k > temp->key)
            {
                temp = temp->right;
            }
            else
            {
                temp = temp->left;
            }
        }
        if (k > temp1->key)
        {
            temp1->right = new_node;
            new_node->p = temp1;
        }
        else
        {
            temp1->left = new_node;
            new_node->p = temp1;
        }
    }
}
struct bst *search(struct bst *node, int k)
{
    // printf("hrer %d", node->key);
    if (node->key == k || node == NULL)
    {
        return node;
    }
    else
    {
        if (k > node->key)
        {
            if (node->right == NULL)
            {
                return NULL;
            }
            search(node->right, k);
        }
        else
        {
            // printf(":l:");
            if (node->left == NULL)
            {
                return NULL;
            }
            search(node->left, k);
        }
    }
}
int delete(struct bstroot *T, struct bst *node)
{
    int y = node->key;
    if (node->left == NULL)
    {
        transplant(T, node, node->right);
    }
    else if (node->right == NULL)
    {
        transplant(T, node, node->left);
    }
    else
    {
        struct bst *temp = minvalue(node->right);
        if (temp->p != node)
        {
            transplant(T, temp, temp->right);
            temp->right = node->right;
            temp->right->p = temp;
        }
        transplant(T, node, temp);
        temp->left = node->left;
        temp->left->p = temp;
    }
    return y;
}
int successor(struct bst *node)
{
    if (node->right != NULL)
    {
        return minvalue(node->right)->key;
    }
    struct bst *temp = node->p;
    while (temp != NULL && node == temp->right)
    {
        node = temp;
        temp = temp->p;
    }
    if (temp == NULL)
    {
        return 0;
    }
    return temp->key;
}
int predecessor(struct bst *node)
{
    if (node->left != NULL)
    {
        return maxvalue(node->left)->key;
    }
    struct bst *temp = node->p;
    while (temp != NULL && node == temp->left)
    {
        node = temp;
        temp = temp->p;
    }
    if (temp == NULL)
    {
        return 0;
    }
    return temp->key;
}
int level(struct bst *node, struct bst *temp, int l)
{
    if (node == NULL)
    {
        // printf("A");
        return 0;
    }
    if (node == temp)
    {
        // printf("B");
        return l;
    }
    if (node->left == NULL && node->right == NULL)
    {
        // printf("C");
        return 0;
    }
    int left = level(node->left, temp, l + 1);
    if (left != 0)
    {
        // printf("D");
        return left;
    }
    int right = level(node->right, temp, l + 1);
    // printf("E");
    return right;
}
void preorder(struct bst *node)
{
    if (node == NULL)
    {
        return;
    }
    printf("%d ", node->key);
    preorder(node->left);
    preorder(node->right);
}
void postorder(struct bst *node)
{
    if (node == NULL)
    {
        return;
    }
    postorder(node->left); // left - right - root
    postorder(node->right);
    printf("%d ", node->key);
}
void inorder(struct bst *node)
{
    if (node == NULL)
    {
        return;
    }
    inorder(node->left); // left - root - right
    printf("%d ", node->key);
    inorder(node->right);
}

int main()
{
    struct bstroot *T, tt;
    T = &tt;
    T->root = NULL;
    struct bst *temp;
    temp = NULL;
    while (1)
    {
        char ch;
        int k;
        scanf("%c", &ch);
        if (ch == 'a')
        {
            scanf("%d", &k);
            insert(k, T);
        }
        if (ch == 'p')
        {
            if (T->root == NULL)
            {
                printf("-1\n");
            }
            else
            {
                preorder(T->root);
                printf("\n");
            }
        }
        if (ch == 'i')
        {
            if (T->root == NULL)
            {
                printf("-1\n");
            }
            else
            {
                inorder(T->root);
                printf("\n");
            }
        }
        if (ch == 't')
        {
            if (T->root == NULL)
            {
                printf("-1\n");
            }
            else
            {
                postorder(T->root);
                printf("\n");
            }
        }
        if (ch == 'l')
        {
            scanf("%d", &k);
            if (T->root == NULL || search(T->root, k) == NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("%d\n", level(T->root, search(T->root, k), 0) + 1);
            }
        }
        if (ch == 'm')
        {
            printf("%d\n", minvalue(T->root)->key);
        }
        if (ch == 'x')
        {
            printf("%d\n", maxvalue(T->root)->key);
        }
        if (ch == 'u')
        {
            scanf("%d", &k);
            if (T->root == NULL || search(T->root, k) == NULL )
            {
                printf("-1\n");
            }
            else
            {
                if (successor(search(T->root, k)) == 0)
                {
                    printf("-1\n");
                }
                else
                {
                    printf("%d\n", successor(search(T->root, k)));
                }
            }
        }
        if (ch == 'r')
        {
            scanf("%d", &k);
            if (T->root == NULL || search(T->root, k) == NULL)
            {
                printf("-1\n");
            }
            else
            {
                if (predecessor(search(T->root, k)) == 0)
                {
                    printf("-1\n");
                }
                else
                {
                    printf("%d\n", predecessor(search(T->root, k)));
                }
            }
        }
        if (ch == 'd')
        {
            scanf("%d", &k);
            if (T->root == NULL || search(T->root, k) == NULL)
            {
                printf("-1\n");
            }
            else
            {
                delete (T, search(T->root, k));
            }
        }
        if (ch == 's')
        {
            int k;
            scanf("%d", &k);
            if (T->root == NULL || search(T->root, k) == NULL)
            {
                printf("-1\n");
            }
            else
            {
                printf("1\n");
            }
        }
        if (ch == 'e')
        {
            break;
        }
    }
}
