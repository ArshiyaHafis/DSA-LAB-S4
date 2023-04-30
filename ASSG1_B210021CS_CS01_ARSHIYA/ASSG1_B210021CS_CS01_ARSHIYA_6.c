#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct bst
{
    int key;
    struct bst *parent;
    struct bst *right;
    struct bst *left;
};
struct bstroot
{
    struct bst *root;
};
struct stack
{
    char key;
    struct stack *next;
};
struct stacktop
{
    struct stack *top;
};
struct bst *create_node(int key)
{
    struct bst *node = (struct bst *)malloc(sizeof(struct bst));
    node->key = key;
    node->parent = NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}
struct stack *create_nodes(char key)
{
    struct stack *nodes = (struct stack *)malloc(sizeof(struct stack));
    nodes->key = key;
    nodes->next = NULL;
    return nodes;
}
int stack_empty(struct stacktop *S)
{
    if (S->top == NULL)
    {
        return 1;
    }
    return 0;
}
void push(struct stacktop *S, char key)
{
    struct stack *nodes = create_nodes(key);
    if (S->top == NULL)
    {
        S->top = nodes;
    }
    else
    {
        nodes->next = S->top;
        S->top = nodes;
    }
}
void pop(struct stacktop *S)
{
    S->top = S->top->next;
}
int close_para(char s[], int o, int c)
{
    struct stacktop *S, ss;
    S = &ss;
    S->top = NULL;
    for (int i = o; i < c; i++)
    {
        if (s[i] == '(')
        {
            push(S, 1);
        }
        if (s[i] == ')')
        {
            pop(S);
            if (stack_empty(S))
            {
                return i;
            }
        }
    }
}
struct bst *build_tree(char s[], int o, int c)
{
    o = o + 2;
    if (o >= c)
    {
        return NULL;
    }
    char num[8];
    for (int i = 0; i < 8; i++)
    {
        num[i] = '\0';
    }
    int k = 0;
    while (s[o] != ' ')
    {
        num[k] = s[o];
        k++;
        o++;
    }
    o++;
    int dig = atoi(num);
    struct bst *node = create_node(dig);
    int index = close_para(s, o, c);
    node->left = build_tree(s, o, index);
    node->right = build_tree(s, index + 2, c - 2);
    return node;
}
void pre_order(struct bst *node, int x, int y)
{
    if (node == NULL)
    {
        return;
    }
    pre_order(node->left, x, y);
    if (node->key >= x && node->key <= y)
    {
        printf("%d ", node->key);
    }
    pre_order(node->right, x, y);
}
int main()
{
    struct bstroot *T, tt;
    T = &tt;
    T->root = NULL;
    char s[10000];
    scanf("%[^\n]%*c", s);
    T->root = build_tree(s, 0, strlen(s) - 2);
    int x, y;
    scanf("%d%d", &x, &y);
    pre_order(T->root, x, y);
}