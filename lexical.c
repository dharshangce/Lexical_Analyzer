
#include <stdio.h>
#include <ctype.h>
#include <string.h>


enum bool
{
	e_success,
	e_failure
};

int check_keyword(char *str)
{
	char key_word[32][50]={"auto","double","int","struct","break","else","long","switch","case","enum","register","typedef","char","extern","return","union","const","float","short","unsigned","continue","for","while","signed","void","default","goto","sizeof","volatile","do","if","static"};
   for(int i=0;i<32;i++)
   {
	   if(strcmp(key_word[i],str)==0)
	   {
		   return e_success;
	   }
		   
   }
   return e_failure;	
}
int check_operator(char *str)
{
	char operators[60][20]={"()","[","]","->",".","!","~","++","--","-","+","*","&","/","%","<<",">>","<","<=",">",">=","==","!=","^","|","&&","||","?",":","=","+=","-=","*=","/=","%=","&=","^=","|=","<<=",">>=",",",";"};
	for(int i=0;i<60;i++)
	{
		if(strcmp(operators[i],str)==0)
		{
			return e_success;
        }
	}
	return e_failure;
}

int main(int argc,char *argv[])
{
   char c;
   FILE *fp;
   char id[20];
   char num[20];
   char op[20];
   char lit[20];
   char dir[40];
   int state=0;
   int i=0;
   int j=0;
   int k=0;
   int x=0;
   int y=0;
   if(argc==2)
   {
	    fp=fopen(argv[1],"r");
        while((c=getc(fp))!=EOF)
       {
		   switch(state)
		   {
			   case 0:
				   {
					   if(isalpha(c))
				       {
					     state=1;
					     id[i++]=c;
				       }
				       else if(isdigit(c))
				       {
					     state=2;
					     num[j++]=c;
				       }

					   else if(c=='('|| c==')'||c=='{'||c=='}')
					   {
						   printf("Operator  : %c\n",c);
						   state=0;
					   }
                       else if(c=='#')
					   {
						   state=5;
						   dir[y++]=c;
					   }
					   else if(c=='"')
					   {
						   state=4;
					   }
					  else if(ispunct(c))
					  {
						  state=3;
						  op[k++]=c;
					   }
				
				   }
				   break;
			   case 1:
				   {
					   if(isalnum(c))
					   {
						   state=1;
						   id[i++]=c;
					   }
					   else
					   {
						   id[i]='\0';
						   int res=check_keyword(id);
						   if(res==e_success)
						   {
							   printf("Keyword : %s\n",id);
						   }
						   else
						   {
							   printf("Identifier : %s\n",id);
						   }
						   i=0;
						   state=0;
						  
					   }
					   if(c=='('||c==')'||c=='{'|| c=='}')
					   {
						   printf("Operator : %c\n",c);
						   state=0;
					   }
					   else if(ispunct(c))
					   {
						   state=3;
						   op[k++]=c;
					   }

				   }
				   break;
			   case 2:
				   {
					   if(isdigit(c))
					   {
						   state=2;
						   num[j++]=c;
					   }
					   else
					   {
						   num[j]='\0';
						   state=0;
						   printf("constant : %s\n",num);
						   j=0;
						   state=0;
					   }
					   if(ispunct(c))
					   {
						   state=3;
						   op[k++]=c;
					   }
				   }
				   break;
			   case 3:
				   {
					  if(ispunct(c))
					  {
						  state=3;
						  op[k++]=c;
					  }
					  else
					  {
						  op[k]='\0';
						  state=0;
						  k=0;
						  if(check_operator(op)==e_success)
						  {
							  printf("Operator : %s\n",op);
						  }

					  }
					  if(isalpha(c))
					  {
						state=1;
						id[i++]=c;
					  }
					  if(isdigit(c))
					  {
					     state=2;
						 num[j++]=c;
					  }

				   }
				   break;
			   case 4:
				   {
					   if(c!='"')
					   {
						   lit[x++]=c;
						   state=4;

					   }
					   else
					   {
					   lit[x]='\0';
					   printf("Literals :  %s\n",lit);
					   state=0;
                       x=0;
					   }
				   }
				   break;
			   case 5:
				   {
					   if(c!='\n')
					   {
						   dir[y++]=c;
						   state=5;
					   }
					   else
					   {
						   dir[y]='\0';
						   printf("Preprocessor directive : %s\n",dir);
						   state=0;
						   y=0;
					   }
				   }
				   
         	   }
   }
   }
   else
   {
	   printf("Please pass valid arguments\n");
	   return e_failure;
   }
	
  return 0;
}

