#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>
#define MAXSIZE 10000

typedef union
{
    float fdata;
    char cdata;
} Item;
typedef struct
{
    Item items[MAXSIZE];
    int top;
} stack;
stack*initialize()
{
    stack*s;
    s=(stack*) malloc(sizeof(stack));
    s->top=0;
    return s;
}
void push(stack*s,Item value)
{
    s->items[s->top]=value;
    s->top++;

}
Item pop (stack*s)
{
    Item get;
    s->top--;
    get=s->items[s->top];
    return get;
}
Item top (stack*s)
{
    return s->items[s->top-1];

}
int isEmpty(stack*s)
{
    if (s->top==0)
        return 1;
    else
        return 0;
}
int isFull(stack*s)
{
    if (s->top==MAXSIZE)
        return 1;
    else
        return 0;
}
float evaluate (char x, float operant1, float operant2 )
{
    if (x=='*')
        return ( operant1 * operant2);
    if (x=='/')
        return ( operant1 / operant2);
    if (x=='+')
        return ( operant1 + operant2);
    if (x=='-')
        return ( operant1 - operant2);
    if (x=='^')
        return pow(operant1,operant2);


}
float evaluatePostfix(char* exp)
{
    int i;
    float operant1,operant2,value;
    stack*s=initialize();
    char* token;
    Item res;
    token=strtok(exp, " ");

    while(token!=NULL)
    {

        if (isdigit(token[0]))
        {
            res.fdata=atof(token);

            push(s,res);

        }
        else if(token[0]=='-'&&token[1]!='\0')
        {
            res.fdata=atof(token);

            push(s,res);

        }
        else
        {
            operant2=pop(s).fdata;
            operant1=pop(s).fdata;
            value=evaluate(token[0],operant1, operant2);
            res.fdata=value;
            push(s,res);
        }
        token=strtok(NULL," ");
    }

    value=pop(s).fdata;

    return value;
}
int priority (char c)
{
    switch (c)
    {
    case '*':
    case '/':
    case '%':
        return 1;
        break;
    case '+':
    case '-':
        return 0;
        break;
    case '(':
        return 3;
        break;
    case '^':
        return 2;
        break;
    default :
        printf ("-----------Invalid Operator-----------\n");
        break;

    }
}
void infixToPostfix(char* infix,char* postfix)
{
    postfix[0]='\0';
    int i;
    Item res;
    stack*s=initialize();
    char* token;
    char test[10]="";
    token=strtok(infix," ");
    while(token!=NULL)
    {

        if (isdigit(token[0]))
        {

            strcat(postfix,token);
            strcat(postfix," ");

        }
        else if(token[0]=='-'&&token[1]!='\0')
        {
            strcat(postfix,token);
            strcat(postfix, " ");

        }


        else if (token[0]==')')
        {
            while (!isEmpty(s)&&top(s).cdata!='(')
            {

                test[0]=pop(s).cdata;
                test[1]='\0';
                strcat(postfix,test);
                strcat(postfix, " ");
            }
            pop(s);
        }

        else if (isEmpty(s))
        {

            res.cdata=token[0];
            push(s,res);


        }

        else

        {

            while (!isEmpty(s)&&priority(top(s).cdata) >= priority(token[0]) && top(s).cdata!='(')
            {
                char arr [2];
                arr[0]=pop(s).cdata;
                arr[1]='\0';
                strcat(postfix,arr);
                strcat(postfix, " ");

            }

            res.cdata=token[0];
            push(s,res);

        }
        token=strtok(NULL," ");
    }

    while (!isEmpty(s))
    {
        test[0]=pop(s).cdata;
        test[1]='\0';
        strcat(postfix,test);
        strcat(postfix, " ");

    }

}

void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}

int main(int argc, char**argv)
{
    printf("\t\t\t\t\t---------------PROJECT[ 1 ]-----------------\n\n");
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Result: %.3f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");

    }
printf("\n\n\t\t\t\t\t---------------Thank You-----------------\n\n");    return 0;
}
