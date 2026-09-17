//Infix to Postfix Conversion 
#include<stdio.h>
#define N 80

//stack implementation
void initstack(int *top)
{
	*top=-1;
}
void push(char *arr,char x,int *top)
{
	*top=*top+1;
	arr[*top]=x;
}
void pop(char *arr,char *x,int *top)
{
	*x=arr[*top];//popped value is stored in x
	*top=*top-1;
}
char peek(char *arr,int top){
	return arr[top];
}
int isEmpty(int top)
{
	if(top==-1)
	return 1;
	else
	return 0;
}
int isFull(int top)
{
	if(top==N-1)
	return 1;
	else
	return 0;
}
int precedence(char op)
{
	if(op=='/')
	return 4;
	if(op=='*')
	return 3;
	if(op=='+')
	return 2;
	if(op=='-')
	return 1;
	return 0;	
}

int main()
{
	char infix[N],stack[N];
	int t,i,j,k;
	char c;
	initstack(&t);
	printf("Give the input expression: ");
	scanf("%s",infix);
	i=0;
	while(infix[i]!='\0')
	{
		if(infix[i]>='a' && infix[i]<='z')
		printf("%c",infix[i]);
		else if(infix[i]=='(')
		push(stack,infix[i],&t);
		else if(infix[i]==')')
		{
			pop(stack,&c,&t);
			while(c!='(')
			{
				printf("%c",c);
				pop(stack,&c,&t);
			}
		}
		else
		{
			while(!isEmpty(t) && peek(stack,t)!='(' && precedence(peek(stack,t))>=precedence(infix[i]))
			{
				pop(stack,&c,&t);
				printf("%c",c);
			}
			push(stack,infix[i],&t);
		}
		i++;
	}
	while(!isEmpty(t))
	{
		pop(stack,&c,&t);
		printf("%c",c);
	}
	printf("\n");
}
