#include <stdio.h>
#include <stdlib.h>
struct bst
{
    int key;
    struct bst *left;
    struct bst *right;
    int height;
};
struct bstroot
{
    struct bst *root;
};
struct bst *create_node(int k)
{
    struct bst *new_node = (struct bst *)malloc(sizeof(struct bst));
    new_node->key = k;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->height = 1;
    return new_node;
}
int max(int a, int b)
{
    return (a > b) ? a : b;
}
int height(struct bst *a)
{
    if (a == NULL)
    {
        return 0;
    }
    return a->height;
}
int getBalance(struct bst *a)
{
    if (a == NULL)
    {
        return 0;
    }
    return height(a->left) - height(a->right);
}
struct bst *rr(struct bst *node)
{
    // printf("-%d ", node->key);
    struct bst *x = node->left;
    struct bst *T2 = x->right;
    x->right = node;
    node->left = T2;

    node->height = max(height(node->left), height(node->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // printf("%d", x->key);
    // printf("hehe");
    return x;
}

struct bst *lr(struct bst *node)
{
    // printf("-%d ", node->key);
    struct bst *x = node->right;
    struct bst *T2 = x->left;

    x->left = node;
    node->right = T2;

    node->height = max(height(node->left), height(node->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    // printf("%d %d", x->left, x->right);
    return x;
}
struct bst *insert(struct bst *temp, int key)
{
    if (temp == NULL)
    {
        return create_node(key);
    }
    if (key < temp->key)
    {
        temp->left = insert(temp->left, key);
    }
    else if (key > temp->key)
    {
        temp->right = insert(temp->right, key);
    }
    else
    {
        return temp;
    }
    temp->height = 1 + max(height(temp->left), height(temp->right));
    int balance = getBalance(temp);
    if (balance > 1 && key < temp->left->key)
    {
        // printf("rr");
        return rr(temp);
    }
    if (balance < -1 && key > temp->right->key)
    {
        // printf("lr");
        return lr(temp);
    }
    if (balance > 1 && key > temp->left->key)
    {
        // printf("lrrr");
        temp->left = lr(temp->left);
        return rr(temp);
    }
    if (balance < -1 && key < temp->right->key)
    {
        // printf("rrlr");
        temp->right = rr(temp->right);
        return lr(temp);
    }
    return temp;
}
struct bst *minValueNode(struct bst *node)
{
    struct bst *current = node;

    /* loop down to find the leftmost leaf */
    while (current->left != NULL)
        current = current->left;

    return current;
}

// Recursive function to delete a node with given key
// from subtree with given root. It returns root of
// the modified subtree.

void preorder(struct bst *node)
{
    if (node == NULL)
    {
        printf("( ) ");
        return;
    }
    printf("( ");
    printf("%d ", node->key);
    preorder(node->left);
    // printf("(");
    preorder(node->right);
    printf(") ");
}
void check(struct bst *node, int k, int *c, int arr[])
{
    if (node == NULL)
    {
        return;
    }
    check(node->left, k, c, arr);
    if (node->key > k)
    {
        arr[*c] = node->key;
        // printf("%d ", node->key);
        (*c)++;
    }
    check(node->right, k, c, arr);
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
        int count = 0;
        scanf("%c", &ch);
        if (ch == 'i')
        {
            scanf("%d", &k);
            T->root = insert(T->root, k);
        }
        if (ch == 'c')
        {
            int arr[1000];
            scanf("%d", &k);
            for (int i = 0; i < 1000; i++)
            {
                arr[i] = '\0';
            }
            check(T->root, k, &count, arr);
            printf("%d\n", count);
            for (int i = 0; arr[i] != '\0'; i++)
            {
                printf("%d ", arr[i]);
            }
            printf("\n");
        }
        if (ch == 'e')
        {
            break;
        }
    }
}