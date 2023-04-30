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
int balance(struct bst *a)
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
struct bst *search(struct bst *root, int key)
{
    if (root == NULL || root->key == key)
        return root;

    if (root->key < key)
        return search(root->right, key);

    return search(root->left, key);
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
    int bl = balance(temp);
    if (bl > 1 && key < temp->left->key)
    {
        // printf("rr");
        return rr(temp);
    }
    if (bl < -1 && key > temp->right->key)
    {
        // printf("lr");
        return lr(temp);
    }
    if (bl > 1 && key > temp->left->key)
    {
        // printf("lrrr");
        temp->left = lr(temp->left);
        return rr(temp);
    }
    if (bl < -1 && key < temp->right->key)
    {
        // printf("rrlr");
        temp->right = rr(temp->right);
        return lr(temp);
    }
    return temp;
}
struct bst *min(struct bst *node)
{
    struct bst *temp = node;
    while (temp->left != NULL)
        temp = temp->left;

    return temp;
}
struct bst *delete(struct bst *temp, int key)
{

    if (temp == NULL)
    {
        return temp;
    }
    if (key < temp->key)
    {
        temp->left = delete (temp->left, key);
    }
    else if (key > temp->key)
    {
        temp->right = delete (temp->right, key);
    }
    else
    {
        if ((temp->left == NULL) || (temp->right == NULL))
        {
            struct bst *temp1 = temp->left ? temp->left : temp->right;
            if (temp1 == NULL)
            {
                temp1 = temp;
                temp = NULL;
            }
            else
            {
                *temp = *temp1;
            }
            free(temp1);
        }
        else
        {
            struct bst *temp1 = min(temp->right);
            temp->key = temp1->key;
            temp->right = delete (temp->right, temp1->key);
        }
    }
    if (temp == NULL)
    {
        return temp;
    }
    temp->height = 1 + max(height(temp->left), height(temp->right));

    int bl = balance(temp);
    if (bl > 1 && balance(temp->left) >= 0)
    {
        return rr(temp);
    }
    if (bl > 1 && balance(temp->left) < 0)
    {
        temp->left = lr(temp->left);
        return rr(temp);
    }
    if (bl < -1 && balance(temp->right) <= 0)
    {
        return lr(temp);
    }
    if (bl < -1 && balance(temp->right) > 0)
    {
        temp->right = rr(temp->right);
        return lr(temp);
    }

    return temp;
}

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
void preh(struct bst *node)
{
    if (node == NULL)
    {
        return;
    }
    printf("%d %d\n", node->key, node->height);
    preh(node->left);
    preh(node->right);
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
        if (ch == 'i')
        {
            scanf("%d", &k);
            T->root = insert(T->root, k);
        }
        if (ch == 'p')
        {
            preorder(T->root);
            printf("\n");
            // preh(T->root);
        }
        if (ch == 'd')
        {
            scanf("%d", &k);
            struct bst *node = search(T->root, k);
            if (node == NULL)
            {
                printf("False\n");
            }
            else
            {
                T->root = delete (T->root, k);
                printf("%d\n", k);
            }
        }
        if (ch == 'b')
        {
            scanf("%d", &k);
            struct bst *node = search(T->root, k);
            if (node == NULL)
            {
                printf("False\n");
            }
            else
            {
                printf("%d\n", balance(node));
            }
        }
        if (ch == 's')
        {
            scanf("%d", &k);
            struct bst *node = search(T->root, k);
            if (node == NULL)
            {
                printf("False\n");
            }
            else
            {
                printf("True\n");
            }
        }
        if (ch == 'e')
        {
            break;
        }
    }
}