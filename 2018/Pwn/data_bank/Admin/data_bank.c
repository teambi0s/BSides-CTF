// gcc tcache.c -o data_bank
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void * table[7];
int size[7];
int count=5;

int get_inp(char *buffer, int size) {
	int retval = read(0, buffer, size);
	if (retval == -1)
		exit(0);
	if ( buffer[retval-1] == '\n')
		buffer[retval-1] = '\0';
	return retval-1;
}

int get_int() {
	char buffer[32];
	get_inp(buffer, 32);
	return atoi(buffer);
}

int  printmenu(){
	puts("1) Add data\n2) Edit data\n3) Remove data\n4) View data\n5) Exit");
	printf(">> ");
	return get_int();
}

void add(){
	int idx;
	puts("Enter the index:");
	idx=get_int();
	while(idx >= 0 && idx < 7){
		if(table[idx] != NULL){
			puts("The idx is occupied\n");
			return;
		}
		puts("Enter the size:");
		size[idx]=get_int();
		if(size[idx] < 0x00 || size[idx] > 0x400)
			puts("Invalid size");

		else{	
			table[idx]=malloc(size[idx]);
			if(!table[idx]){
				puts("malloc_error");
				return;	
			}
			puts("Enter data:");
			get_inp(table[idx],size[idx]);
			return;
		}
	}
}


void edit(){
	int idx;
	puts("Enter the index:");
	idx=get_int();
	while(idx >= 0 && idx < 7){
		if(table[idx] == NULL){
			puts("The index is empty\n");
			return;
		}
		puts("Please update the data:");
		int val=get_inp(table[idx],size[idx]);
		if(val)
			puts("update successful\n");
		else
			puts("update unsuccessful");
		return;
	}

}
	

void delete(){
	int idx;
	puts("Enter the index:");
	idx=get_int();
	while(idx >= 0 && idx < 7){
		if(table[idx] == NULL){
			puts("The index is empty");
			return;
		}
		if(count--){
			free(table[idx]);
			puts("done");
			return;
		}
		else
			puts("Sorry no more removal\n");
	}
}

void view(){
	int idx;
	puts("Enter the index:");
	idx=get_int();
	while(idx >= 0 && idx < 7){
		if(table[idx] == NULL){
			puts("The index is empty");
			return;
		}
		printf("Your data :%s\n\n",(char*)table[idx]);
		return;
	}
}

int main(){
	alarm(60);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);

	puts("----------DATA BANK----------");
	do {
		switch(printmenu()) {
			case 1: add(); break;
			case 2: edit(); break;
			case 3: delete(); break;
			case 4: view(); break;
			case 5: exit(0);
			default: puts("Invalid"); break;
		}
	} while(1);
	return 0;
}
