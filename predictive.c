#include<stdio.h>
#include<stdlib.h>
#include<string.h>
char prod[3][10]={"M->aCa","C->bC","C->&"};
char first[3][10]={"a","b","&"};
char follow[3][10]={"$","a","a"};
char table[3][4][10];
char name[20];
char rollno[20];
char input[10];
int top=-1;
char stack[25];
char curprod[20];
void push(char item)
{
stack[++top]=item;
}
void pop()
{
top=top-1;
}
void display()
{
int i;
for(i=top;i>=0;i--)
printf("%c",stack[i]);
}
int numeric(char c)
{
switch(c)
{
case'M': return 1;
case'C': return 2;
case'a': return 1;
case'b': return 2;
case'$': return 3;
default: return 3;
}
return 1;
}
int main()
{
printf("\nEnter the Name of the Student:");
scanf("%s",name);
printf("Enter Rollno of the Student:");
scanf("%s",rollno);
printf("\nName of the Student  is :%s",name);
printf("\nRollno of the Student is :%s",rollno);
char c;
int i,j,k,n;
for(i=0;i<3;i++)
{
for(j=0;j<4;j++)
{
strcpy(table[i][j],"EMPTY");
}
}
printf("\n\nTHE GIVEN GRAMMAR IS:\n");
for(i=0;i<3;i++)
printf("%s\n",prod[i]);
printf("\nFIRST AND FOLLOW OF THE NON TERMINAL SYMBOLS IN THE GIVEN GRAMMAR ARE:");
printf("\nFIRST={%s,%s,%s}",first[0],first[1],first[2]);
printf("\nFOLLOW={%s,%s}\n",follow[0],follow[1]);
printf("\nPREDICTIVE PARSE TABLE FOR THE GIVEN GRAMMAR IS:\n");
strcpy(table[0][0],"");
strcpy(table[0][1],"a");
strcpy(table[0][2],"b");
strcpy(table[0][3],"$");
strcpy(table[1][0],"M");
strcpy(table[2][0],"C");
for(i=0;i<3;i++)
{
if(first[i][0]!='&')
strcpy(table[numeric(prod[i][0])][numeric(first[i][0])],prod[i]);
else
strcpy(table[numeric(prod[i][0])][numeric(follow[i][0])],prod[i]);
}
printf("\n---------------------------------------------------------------------------------------------------- \n");
for(i=0;i<3;i++)
{
for(j=0;j<4;j++)
{
printf("%-30s",table[i][j]);
if(j==3)
printf("\n----------------------------------------------------------------------------------------------------\n");
}
}
printf("\n Enter the Input String Terminated with $ to Parse:");
scanf("%s",input);
for(i=0;input[i]!='\0';i++)
{
if((input[i]!='a')&&(input[i]!='b')&&(input[i]!='$'))
{
printf("\nINVALID STRING ENTERED");
exit(0);
}
}
push('$');
push('M');
i=0;
printf("\n\n");
printf("STACK\t\t INPUT\t\t\t Action");
printf("\n-----------------------------------------------------------\n");
while(stack[top]!='$')
{
display();
printf("\t\t%s\t",(input+i));
if(stack[top]==input[i])
{
printf("\tMatched %c\n",input[i]);
pop();
i++;
}
else
{
if(stack[top]>=65&&stack[top]<92)
{
strcpy(curprod,table[numeric(stack[top])][numeric(input[i])]);
if(!(strcmp(curprod,"EMPTY")))
{
printf("\n UNABLE TO PARSE THE STRING \n");
exit(0);
}
else
{
printf("\tApply Production %s\n",curprod);
if (curprod[3]=='&')
pop();
else
{
pop();
n=strlen(curprod);
for(j=n-1;j>=3;j--)
push(curprod[j]);
}
}
}
}
}
display();
printf("\t\t%s\t",(input+i));
printf("\n------------------------------------------------\n");
if(stack[top]=='$'&&input[i]=='$')
{
printf("\n STRING IS SUCCESSFULLY PARSED\n");
}
else if(stack[top]=='$' || input[i]=='$')
{
printf("\nUNABLE TO PARSE THE STRING\n");
}
}