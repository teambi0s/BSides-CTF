// Note : the program has been patched to start from check after compilation

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int key;

int strcmp_(char *a, char *b) {
        int x = 0;
        for(int i=0;i<22;i++) {
                x++;
                x = x^23;
        }
        for(int i=0; i<strlen(a);i++){
                a[i]=a[i]^key;
        }
        return strncmp(a,b,24);
}

int main(int argc, char **argv) {
        char x[24];
        char y[24] = {97, 107, 102, 96, 124, 51, 116, 88, 98, 51, 50, 126, 88, 51, 116, 88, 54, 115, 88, 96, 52, 115, 116, 122};
        printf("Enter your input:\n");
        scanf("%s", x);
        int d = strcmp_(x,y);
        if(!d)
                printf("Good game\n");
        else
                printf("Always dig deeper\n");
        return 0;
}

void check(int argc, char **argv){
        int x = atoi(argv[1]);
        if((x*x - 14*x + 49 )==0)
            key = x;
        else
            key = 0;    
        main(argc, argv);
}


