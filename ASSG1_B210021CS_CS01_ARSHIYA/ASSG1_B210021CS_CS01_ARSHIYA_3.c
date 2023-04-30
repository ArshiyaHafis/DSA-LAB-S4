#include <stdio.h>
#include <string.h>
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
struct stack
{
    char data;
    struct stack *next;
};
struct stacktop
{
    struct stack *top;
};
struct stack *create_nodes(char ch)
{
    struct stack *new_node = (struct stack *)malloc(sizeof(struct stack));
    new_node->data = ch;
    new_node->next = NULL;
    return new_node;
}
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
struct bst *create_node(int k)
{
    struct bst *new_node = (struct bst *)malloc(sizeof(struct bst));
    new_node->key = k;
    new_node->p = NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}
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
    l = l + 2;
    // printf("%d %d ", l, h);
    if (l >= h)
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
    num = atoi(dig);
    struct bst *node = create_node(num);
    int index = 0;
    index = close_para(s, l, h);
    node->left = build_tree(s, l, index);
    node->right = build_tree(s, index + 2, h - 2);
    return node;
}
int sum(struct bst *t, int *c, int k)
{
    if (t == NULL)
    {
        return 0;
    }
    int sl = sum(t->left, c, k);
    int sr = sum(t->right, c, k);
    if (t->right == NULL && t->left == NULL)
    {
    	if(t->key == k){
    		(*c)++;
    	}
        return t->key;
    }
    // printf("[%d+%d+%d = %d]\n", sl, sr, t->key, sl + sr + t->key);
    if (sl + sr + t->key == k)
    {
        (*c)++;
    }
    return sl + sr + t->key;
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
    int k;
    scanf("%d", &k);
    sum(T->root, &count, k);
    printf("%d", count);
}
// ( 1 ( 2 ( 4 ( 8 ( ) ( ) ) ( 9 ( ) ( ) ) ) ( 5 ( 10 ( ) ( ) ) ( 11 ( ) ( ) ) ) ) ( 3 ( 6 ( 12 ( ) ( ) ) ( 13 ( ) ( ) ) ) ( 7 ( 14 ( ) ( ) ) ( 15 ( ) ( ) ) ) ) )
// ( 1 ( 2 ( 4 ( 8 ( ) ( ) ) ( 9 ( ) ( ) ) ) ( 5 ( 10 ( ) ( ) ) ( 11 ( ) ( ) ) ) ) ( 3 ( 6 ( 12 ( ) ( ) ) ) ) )
// ( 1 ( 3 ( 5 ( ) ( ) ) ( 9 ( ) ( ) ) ) ( 6 ( 11 ( ) ( ) ) ( ) ) )
// ( 1 ( 3 ( 5 ( ) ( ) ) ( 9 ( ) ( ) ) ) ( 6 ( ) ( 11 ( ) ( ) ) ) )
// ( 5 ( 2 ( 1 ( ) ( ) ) ( 3 ( ) ( ) ) ) ( 12 ( 9 ( ) ( ) ) ( 21 ( ) ( ) ) ) )
