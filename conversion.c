// Implemnting The conversion of expression from
// 1. infix to postfix
// 2. infix to Prefix
// author : Zaid Inamdar


#include <stdio.h>
#include <ctype.h>
#define max 20
char stack[max];
char outExp[max];
char infix[max];
int top = -1;

int outTop = -1;
void push(char x)
{
    if (top == max - 1)
        printf("\nStack Overflow...");
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

void outPush(char x)
{
    if (outTop == max - 1)
        printf("\nStack Overflow!");

    else
    {
        outExp[++outTop] = x;
    }
}

void revs(char str[])
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

void printPrefix()
{
    revs(outExp);
    printf("\nPrefix expression : %s\n", outExp);
    outTop = -1;
}
void convertExp()
{
    top = -1;
    outTop = -1;

    char *e, x;

    e = infix;

    while (*e != '\0')
    {
        if (isalnum(*e))
            outPush(*e);
        else if (*e == '(')
            push(*e);
        else if (*e == ')')
        {
            while (top != -1 && (x = pop()) != '(')
            {
                outPush(x);
            }
        }
        else
        {
            while (top != -1 && priority(stack[top]) >= priority(*e))
            {
                char ch = pop();

                outPush(ch);
            }
            push(*e);
        }
        e++;
    }
    while (top != -1)
    {
        char ch = pop();

        outPush(ch);
    }
    outExp[outTop + 1] = '\0';
}
int main()
{
    int ch;

    do
    {
        printf("\nEnter Your Choice\n1.Enter Expression\n2.Exit: ");
        scanf("%d", &ch);
        if (ch == 1)
        {
            printf("\nEnter Your Expression : ");
            scanf("%s", infix);
            printf("\nChoose Output Epxression Format\n1.prefix\n2.postfix\n3.exit: ");
            scanf("%d", &ch);
            if (ch == 1)
            {
                revs(infix);
                for (int i = 0; infix[i] != '\0'; i++)
                {
                    if (infix[i] == ')')
                    {
                        infix[i] = '(';
                    }
                    else if (infix[i] == '(')
                    {
                        infix[i] = ')';
                    }
                    else
                    {
                        continue;
                    }
                }
                convertExp();
                printPrefix();
            }
            else if (ch == 2)
            {
                convertExp();
                printf("\nPostfix Expression : %s\n", outExp);
            }
        }
        else
        {
            break;
        }

    } while (ch != 3);
    printf("----------Code Executed successfully------------");

    return 0;
}
