#include <stdio.h>
#include <ctype.h>

int precedence(char c)
{
    return (c == '+' || c == '-') ? 1 : 2;
}

int main()
{
    char e[100], op[100];
    int val[100], ot = -1, vt = -1, i = 0;

    printf("Enter expression: ");
    scanf("%s", e);

    while (e[i])
    {
        if (isdigit(e[i]))
        {
            int n = 0;
            while (isdigit(e[i]))
                n = n * 10 + e[i++] - '0';
            val[++vt] = n;
            continue;
        }

        if (e[i] == '(')
            op[++ot] = e[i];

        else if (e[i] == ')')
        {
            while (op[ot] != '(')
            {
                int b = val[vt--], a = val[vt--];
                char c = op[ot--];

                if(c=='+') val[++vt]=a+b;
                if(c=='-') val[++vt]=a-b;
                if(c=='*') val[++vt]=a*b;
                if(c=='/') val[++vt]=a/b;
            }
            ot--;
        }

        else
        {
            while (ot >= 0 && op[ot] != '(' &&
                   precedence(op[ot]) >= precedence(e[i]))
            {
                int b = val[vt--], a = val[vt--];
                char c = op[ot--];

                if(c=='+') val[++vt]=a+b;
                if(c=='-') val[++vt]=a-b;
                if(c=='*') val[++vt]=a*b;
                if(c=='/') val[++vt]=a/b;
            }
            op[++ot] = e[i];
        }
        i++;
    }

    while (ot >= 0)
    {
        int b = val[vt--], a = val[vt--];
        char c = op[ot--];

        if(c=='+') val[++vt]=a+b;
        if(c=='-') val[++vt]=a-b;
        if(c=='*') val[++vt]=a*b;
        if(c=='/') val[++vt]=a/b;
    }

    printf("Result = %d", val[vt]);
    return 0;
}
