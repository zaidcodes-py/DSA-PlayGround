#include <stdio.h>
#include <ctype.h>
#define max 20
char stack[max];
char expr[max];
char prefixExpr[max];

int top = -1;
int pretop = -1;

void push(char e)
{
    if (top == max - 1)
    {
        printf("\nStack Overflow!!");
    }
    else
    {
        stack[++top] = e;
    }
}

char pop()
{
    if (top == -1)
    {
        printf("\nStack Underflow!");
        return '\0';
    }
    else
    {
        return stack[top--];
    }
}

int priority(char e)
{
    if (e == '(')
    {
        return 0;
    }
    else if (e == '+' || e == '-')
    {
        return 1;
    }
    else if (e == '*' || e == '/')
    {
        return 2;
    }
    return 0;
}

void prepush(char e)
{
    if (pretop == max - 1)
    {
        printf("\nExpression Stack Overflow");
    }
    else
    {
        prefixExpr[++pretop] = e;
    }
}

void revsExpr(char str[])
{
    int i, j;
    char temp;
    for (j = 0; str[j] != '\0'; j++)
        ;

    for (i = 0, j = j - 1; i < j; i++, j--)
    {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
    }
}

void convertExpr()
{
    top = -1;
    pretop = -1;

    char *e, x;
    e = expr;
    while (*e != '\0')
    {

        if (isalnum(*e))
        {
            prepush(*e);
        }
        else if (*e == '(')
        {
            push(*e);
        }
        else if (*e == ')')
        {
            while (top != -1 && (x = pop()) != '(')
            {
                prepush(x);
            }
        }
        else
        {
            while (top != -1 && (priority(stack[top]) >= priority(*e)))
            {
                char ch = pop();
                prepush(ch);
            }
            push(*e);
        }
        e++;
    }
    while (top != -1)
    {
        char ch = pop();
        prepush(ch);
    }
    prefixExpr[pretop + 1] = '\0';
}

int main()
{
    int ch;
    do
    {
        printf("\n1.Enter Expression\n2.Exit: ");
        scanf("%d", &ch);
        if (ch == 1)
        {

            printf("\nEnter Your Expression: ");
            scanf("%s", expr);
            revsExpr(expr);
            for (int i = 0; expr[i] != '\0'; i++)
            {
                if (expr[i] == '(')
                {
                    expr[i] = ')';
                }
                else if (expr[i] == ')')
                {
                    expr[i] = '(';
                }
                else
                {
                    continue;
                }
            }

            convertExpr();
            revsExpr(prefixExpr);
            printf("\nPrefix expression: %s", prefixExpr);
        }
        else if (ch != 2)
        {
            printf("\nInvalid option!\nChoose again\n");
            continue;
        }
    } while (ch != 2);
}
