#include<iostream>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
# define d1 "h3y_m4n_g0n3_c4s3"
# define d2 "h33_m4n_g0n3_c4s3"
# define s1 "f`c(I>fJZb5BrQZQL"
# define s2 "-gsM!T;:Q?S>9K0A2"

using namespace std;

int function1(int, char*);
int check_one(char *, char *);
int check_two(char *, char *);

int length(int, char **,char *);

int function2(int,char **);

int check_one_2(char *,char **);

int main(int argc, char**argv)
	{
	int i;
	int c;
	char input[18];
	fgets(input,18, stdin);	
	int ret1= function1(argc,input);
	int ret2= function2(argc,argv);
	
	c=length(argc,argv,input);

	if(((ret1+9)%15 + ((ret2+11)%19)+c)==(((ret1+ret2)%24)*2+1))
	{cout<<"C0ngr4tzz !! "<<endl;
	cout<<"flag{";
	for(i=0;i<34;i++)
		{
		if(i%2==0)
			cout<<argv[1][i/2];
		
		else 
			cout<<input[i/2];	
		
		}
	cout<<"}"<<endl;
	
	}	
	else 
	cout<<"Wr0ng input!!!"<<endl;
	
	return 0;
	}
	
	
int function1(int c, char *inputf)
	{
	int x=0;
	int j=0;
	int k=0; 
	int i;
	char random_one[34];
	if(c!=2)
		{
		for (i=0;i<34;i++)
			{
			if(i%2!=0)
				{
				random_one[i]=(((s1[k])^2)+4);
				k++;
				}
				
			else
				{
				random_one[i]=(((d1[j])^3)-9);
				j++;
				}
			}
			
		x= check_two(random_one,inputf);
		}
		
	else 
		{
		int k=0;
		for (i=0;i<34;i++)
			{
			if(i%2!=0)
				{
				random_one[i]=(((s1[k])^4)+3);
				k++;
				}
			else
				{
				random_one[i]=(((d1[j])^4)-1);
				j++;
				}
			}
		
		x= check_one(random_one,inputf);
		}
		
	return x;
	}
	
	
int check_one(char * random_one, char *inputf)

	{
	
	int flag=0;
	int i =0;
	char inputM[18];
	int k =16;	
	
	for (i=0;i<17;i++)
		{
		inputM[i]=(inputf[k]^3)-4;
		
		k=k-1;
		}
	inputM[17]=0;
	
	for (i=0;i<17;i++)
		{
		inputM[i]=(inputM[i]^8);
		i++;
		}
	inputM[17]=0;
	
	for (i=0;i<35;i++)
		{
		if(i%2!=0)
			{
			if(random_one[i]==inputM[i/2])
				{
				flag++;
				}
			}
		}
	

	return flag;
	}
		
int check_two(char *random_one, char *inputf)

	{
	int flag=0;
	int i =0;
	char inputM[35];
	int k=0;
	for (i=0;i<35;i++)
		{
		inputM[i]=(((inputf[k])^7)-12);
		
		k++;
		}
	for (i=0;i<=35;i++)
		{
		if(i%2!=0)
			{
			random_one[i]==inputM[i/2];
			flag=flag+2;
			}
		}
	
	return flag;
	}

	
	
int length(int x,char **a, char *c)
	{
	
	int i;
	int j;
	int flag=1;
	int sum=0;
	
	if(x>1 && x<3)
	
		{
		for(i=10;i>1;i--)
			{
			int d=i-1;
			for(j=d;j>1;j--)
				{
				if((i%j)==0)
					{
					flag=0;
					}
				else
					{
					continue;
					}
				}
		
			if(flag!=0)
				{
				sum=sum+i;
				}
			else 
				{
				}
			
			flag=1;		
			}
		
		if(2*sum==strlen(a[1])+strlen(c))
			{
			return 1;
			}
		else
			{
			return 0;
			}
		
		
	
		}
	else
		{cout<<"Wr0ng input!!!"<<endl;
		exit(0);
		}
	
	}
	
	
	

int function2(int c, char **inputA)
	{
	int x=0;
	int j=0;
	int k=0; 
	int i;
	char random_two[35];
	if(c!=2)
		{cout<<"Wr0ng input!!!"<<endl;
		exit(0);
		}
	
		
	else 
		{
		int k=0;
		for (i=0;i<34;i++)
			{
			if(i%2!=0)
				{
				random_two[i]=(((d2[k])^4)+3);
				k++;
				}
			else
				{
				random_two[i]=(((s2[j])^5)+8);
				j++;
				}
			}
		random_two[34]=0;
		
		
		x= check_one_2(random_two,inputA);
		}
	
	return x;
	}
	
int check_one_2(char *random_two,char **inputA)
	{
	char inputAM[18];
	int i=0;
	int z=0;
	int p=21;
	int flag=0;
	int k=0;

	for(i=0;i<=16;i++)
		{
		inputAM[i]=((inputA[1][16-i])^(21-i));
		inputAM[i+1]=0;
		}
	
	for (i=0;i<17;i++)
		{
		inputAM[i]=(inputAM[i]+10);
		}

	for (i=0;i<34;i++)
		{
		if(i%2==0)
			{
			if(random_two[i]==inputAM[i/2])
				{
				flag++;
				}
			}
		}
	
	return flag;
	}
