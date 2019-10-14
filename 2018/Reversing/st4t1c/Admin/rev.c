#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void trap() __attribute__((always_inline));

void print_flag (char input []) {
    trap();
    printf("The flag is: flag{%s}", input);
}

void trap() {
    int flag = 0;
	if (flag == 1) {
        asm volatile ("int3\n\t"
                    "int3\n\t");
    }
}

int check(char team_name [4], char input []) {
    int i, key = 0, cnt = 0;
    // l34rn_7h3_b451c5_f1r57
    char str [] = "?5b9no=k!5<jW;h7W~b4#|";
    char enc [22];

    if (strlen(input) != 22) {
        return 0;
    }

    for(i=0; i<strlen(team_name); i++) {
        key += team_name[i];
    }

    trap();

    key /= 30; //12

    while (1) {
        if (cnt == 22) {
            break;
        }
        if (cnt % 2 == 0) {
            enc[cnt] = input[cnt] + 4;
        }
        else {
            enc[cnt] = input[cnt] - 4;
        }
        enc[cnt] ^= key;
        cnt++;
    }

    trap();
    
    for (i=strlen(enc)-1; i>=0; i--) {
        if (enc[strlen(enc)-1-i] != str[i]) {
            return 0;
        }
    }

    trap();

    return 1;
}

int main(int argc, char **argv) {
    const char* team_name;
    int ret;
	trap();
    team_name = getenv("team_name");
    if (team_name != NULL && strncmp(team_name, "bi0s", 4) == 0) {
        if (argc != 2) {
            printf("usage: chall <input>");
        }
        else {
            ret = check(team_name, argv[1]);
            if (ret == 1) {
                print_flag(argv[1]);
            }
            else {
                printf("Better luck next time!");
            }
        }
    }
    else {
        printf("Nope.");
    }
    trap();
    return 0;
}
