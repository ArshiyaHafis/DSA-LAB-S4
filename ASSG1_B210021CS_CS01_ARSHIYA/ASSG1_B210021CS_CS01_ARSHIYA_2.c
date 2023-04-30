#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// structure of bst
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
// structure for stack for close paranthesis

struct stack
{
    char data;
    struct stack *next;
};
struct stacktop
{
    struct stack *top;
};

// create_nodes for stack
struct stack *create_nodes(char ch)
{
    struct stack *new_node = (struct stack *)malloc(sizeof(struct stack));
    new_node->data = ch;
    new_node->next = NULL;
    return new_node;
}

// driver functions of stack
int stack_empty(struct stacktop *S)
{
    if (S->top == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
void push(struct stacktop *S, char ch)
{
    struct stack *new_node = create_nodes(ch);
    if (stack_empty(S))
    { // empty list
        S->top = new_node;
    }
    else
    {
        struct stack *temp = S->top;
        S->top = new_node;
        S->top->next = temp;
    }
}
int pop(struct stacktop *S)
{
    struct stack *temp1 = S->top;
    struct stack *temp = S->top->next;
    S->top = temp;
    return temp1->data;
}

// create nodes for bst

struct bst *create_node(int k)
{
    struct bst *new_node = (struct bst *)malloc(sizeof(struct bst));
    new_node->key = k;
    new_node->p = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// function to find corresponding closing bracket of opening bracket
int close_para(char ch[], int l, int h)
{
    if (l > h)
    {
        return -1;
    }
    struct stacktop *s, ss;
    s = &ss;
    s->top = NULL;
    for (int i = l; i <= h; i++)
    {
        if (ch[i] == '(')
        {
            push(s, ch[i]);
        }
        else if (ch[i] == ')')
        {
            if (s->top->data == '(')
            {
                pop(s);
                if (stack_empty(s))
                {
                    return i;
                }
            }
        }
    }
    return -1;
}
struct bst *build_tree(char s[], int l, int h)
{
    l = l + 2; // eliminate space and (
    // printf("%d %d ", l, h);
    if (l >= h) // base case
    {
        return NULL;
    }
    int num = 0;
    int c = 0;
    char dig[8];
    for (int i = 0; i < 8; i++)
    {
        dig[i] = '\0';
    }
    while (s[l] != 32)
    {
        dig[c] = s[l];
        c++;
        l++;
    }
    l++;
    num = atoi(dig);                     // convert '1' to 1
    struct bst *node = create_node(num); // index of close )
    int index = 0;
    index = close_para(s, l, h);
    // printf("g");
    node->left = build_tree(s, l, index); // left of node
    if (node->left != NULL)
    {
        node->left->p = node;
    }
    // printf("l");
    node->right = build_tree(s, index + 2, h - 2); // right of node
    if (node->right != NULL)
    {
        node->right->p = node;
    }
    // printf("r");
    return node;
}
int check(struct bst *t)
{
    // if (t->p)
    // {
    //     printf("Yes");
    // }
    if (t->p != NULL)
    {
        // printf("-p1-");
        if (t->p->p != NULL)
        {
            // printf("-p2-");
            if (t->p->p->left != NULL && t->p->p->right != NULL)
            {
                if ((t->p->p->left->right == NULL && t->p->p->left->left == NULL) || (t->p->p->right->left == NULL && t->p->p->right->right == NULL))
                {
                    // printf("-p3-");
                    return 1;
                }
            }
        }
    }
    return 0;
}
void preorder(struct bst *t, int *c)
{
    if (t == NULL)
    {
        return;
    }
    // printf("%d ", t->key);
    // if (t->p != NULL)
    // {
    //     printf("[p%d]", t->p->key);
    // }
    if (check(t))
    {
        (*c)++;
        // printf("*%d8*", t->key);
    }
    // printf("Left");
    preorder(t->left, c);
    // printf("Right");
    preorder(t->right, c);
}
int main()
{
    struct bstroot *T, tt;
    T = &tt;
    T->root = NULL;
    int count = 0;
    char ch[1000];
    scanf("%[^\n]%*c", ch);
    T->root = build_tree(ch, 0, strlen(ch) - 2);
    preorder(T->root, &count);
    printf("%d\n", count);
}
// ( 50 ( 90 ( 30 ( ) ( ) ) ( ) ) ( 40 ( 80 ( ) ( ) ) ( 10 ( ) ( ) ) ) )
// ( 20 ( 6 ( 7 ( 10 ( ) ( ) ) ( 11 ( ) ( ) ) ) ( 8 ( ) ( ) ) ) ( 12 ( 2 ( ) ( ) ) ( 5 ( 9 ( ) ( ) ) ( 4 ( ) ( ) ) ) )
// ( 1 ( 2 ( 4 ( 8 ( ) ( ) ) ( 9 ( ) ( ) ) ) ( 5 ( ) ( ) ) ) ( 3 ( 6 ( ) ( ) ) ( ) ) )
