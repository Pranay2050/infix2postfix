#include<stdio.h>
#include<stdlib.h>
#define N 20

int isoperand(char c)
{
    if((c>='a' && c<='z') || (c>='A' && c<='Z') || (c>='0' && c<='9'))
        return 1;
    else
        return 0;

}
void PUSH(char s[],int *top,char val)
{
    if((*top)<(N-1))
        s[++(*top)]=val;
    else
        printf("Stack Overflow\n");
}
int POP(char s[],int *top)
{   char val;
    if((*top)>-1)
        {
            val=s[(*top)--];
            return val;
        }
    else
        {
            printf("Stack Underflow\n");
            exit(-1);
        }
}
int READ(char s[],int *top)
{
    if((*top)>-1)
        {
             return s[(*top)];
        }
    else
    {
        printf("Stack Underflow\n");
        exit(-1);
    }
}
int prec(char j)
{
    if(j=='^')
        return (3);
    else if(j=='*'||j=='/')
        return(2);
    else if(j=='+' || j=='-')
        return(1);
        else return 0;
}

int associativity(char ch)
{
	if((ch == '+')||(ch == '-')||(ch == '*')||(ch == '/'))
		return 1;

	else
		return 2;
}
void infixtopostfix(char infix[])
{
    char s[N]; char postfix[N]={0};
    int top=-1;
    int i=0,p=0;

    while(infix[i]!='\0')
{
    if(isoperand(infix[i]))
    {
        postfix[p]=infix[i];
        p++;
        i++;


    }
    else if(infix[i]=='(')
            {
                        PUSH(s,&top,infix[i]);
                        i++;

            }
    else if(infix[i]==')')
            {
                while(READ(s,&top)!='(')
                {
                    postfix[p++]=POP(s,&top);
                }
                POP(s,&top);
                i++;

            }

    else
         {
            if(top==-1 || READ(s,&top)=='(')
                {
                    PUSH(s,&top,infix[i++]);

                }

                else if(prec(infix[i])>prec(READ(s,&top)))
                       {
                         PUSH(s,&top,infix[i]);
                        i++;
                       }
                    else
			{
			if(READ(s,&top)!=infix[i])
                        	postfix[p++]=POP(s,&top);

			else
				{
				if(associativity(infix[i])==1)
					postfix[p++]=POP(s,&top);

				else
					PUSH(s,&top,infix[i++]);
				}

        		}
	}
}

while(top!=-1)
    postfix[p++]=POP(s,&top);
printf("The Postfix expression : %s \n",postfix);
}



int main()
{

    char infix[80];

    printf("Enter the infix equation :");
	scanf("%s",infix);

    infixtopostfix(infix);
}

/*
OUTPUT
Enter the infix equation :a+b*(c^d-e)^(f+g*h)-i
The Postfix expression : abcd^e-fgh*+^*+i-

Enter the infix equation :a+b+c
The Postfix expression : ab+c+
*/

