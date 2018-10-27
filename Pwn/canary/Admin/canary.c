#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

char flag[40];

int main() {

	alarm(30);
	setvbuf(stdin,NULL,_IONBF,0);
	setvbuf(stdout,NULL,_IONBF,0);
	char name[128];
	FILE *fd;
	fd = fopen("flag","r");
	if(fd==0) {
 	    printf("Error in opening file");
 	    exit(0);	
	}
	fgets(flag,30,fd);
	puts("Hey!! What's your name ?");
	scanf("%s",name);
	printf("Hello %s, can you find my name ?",name);
	return 0;

}


