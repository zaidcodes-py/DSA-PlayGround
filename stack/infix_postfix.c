#include <stdio.h>
#include <ctype.h>
#define max 20
char stack[max];
int top = -1;
void push(char x)
{
    if (top == max - 1)
        printf("\nStack Overflow!");

    else
    {
        stack[++top] = x;
    }
}

char pop()
{
    if (top == -1)
        return -1;
    else
        return stack[top--];
}

int priority(char x)
{
    if (x == '(')
        return 0;
    if (x == '+' || x == '-')
        return 1;
    if (x == '*' || x == '/')
        return 2;
    return 0;
}

int main()
{
    char exp[max];
    char *e, x;

    printf("Enter Your Expression : ");
    scanf("%s", exp);

    e = exp;

    while (*e != '\0')
    {
        if (isalnum(*e))
            printf("%c", *e);
        else if (*e == '(')
            push(*e);
        else if (*e == ')')
        {
            while ((x = pop()) != '(')
            {
                printf("%c", x);
            }
        }
        else
        {
            while (top != -1 && priority(stack[top]) >= priority(*e))
            {
                printf("%c", pop());
            }
            push(*e);
        }
        e++;
    }
    while (top != -1)
    {
        printf("%c", pop());
    }

    return 0;
}
