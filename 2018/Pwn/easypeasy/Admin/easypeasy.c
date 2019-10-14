/*
 * =====================================================================================
 *
 *       Filename:  text.c
 *
 *    Description:  InCTF challenge using forks
 *
 *        Version:  1.0
 *        Created:  Monday 02 April 2018 11:37:24  PDT
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jayakrishna Menon (4rbit3r), jkrshnmenon@gmail.com
 *        Company:  
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>
#include <string.h>

#define SYS_READ 0
#define SYS_WRITE 1
#define SYS_OPEN 2
#define SYS_CLOSE 3
#define SYS_EXIT 60


typedef struct {
    long rax;
    long rdi;
    long rsi;
    long rdx;
    long rcx;
    long r8;
    long r9;
} syscall_obj;

syscall_obj obj;


void exec_syscall_obj ( syscall_obj *obj) {
    __asm__ volatile( "mov %rdi, %rbx\n"
             "mov (%rbx), %rax\n"
             "mov 8(%rbx), %rdi\n"
             "mov 16(%rbx), %rsi\n"
             "mov 24(%rbx), %rdx\n"
             "mov 32(%rbx), %rcx\n"
             "mov 40(%rbx), %r8\n"
             "mov 48(%rbx), %r9\n"
             "syscall");
}


void handler(int signum) {
    exec_syscall_obj(&obj);
}


int get_inp(char *buffer, int size) {
    int retval = read(0, buffer, size);
    if (retval == -1)
        exit(0);
    if ( buffer[retval-1] == '\n')
        buffer[retval-1] = '\0';
    return retval-1;
}


long get_ll() {
    char buffer[32];
    get_inp(buffer, 32);
    return atol(buffer);
}


int get_obj(syscall_obj *obj) {
    printf("RAX: ");
    obj->rax = get_ll();
    printf("RDI: ");
    obj->rdi = get_ll();
    printf("RSI: ");
    obj->rsi = get_ll();
    printf("RDX: ");
    obj->rdx = get_ll();
    printf("RCX: ");
    obj->rcx = get_ll();
    printf("R8: ");
    obj->r8 = get_ll();
    printf("R9: ");
    obj->r9 = get_ll();
    return 0;
}


int validate_syscall_obj(long syscall_num) {
    int retval;
    switch ( syscall_num) {
        case SYS_READ: retval = 0; break;
        case SYS_WRITE: retval = 0; break;
        case SYS_OPEN: retval = 0; break;
        case SYS_CLOSE: retval = 0; break;
        case SYS_EXIT: retval = 0; break;
        default: retval = 1; break;
    }
    return retval;
}


int child() {
    signal(SIGALRM, handler);
    syscall_obj tmp;
    while(1) {
        get_obj(&tmp);
        memcpy(&obj, &tmp, sizeof(syscall_obj));
        if ( validate_syscall_obj(tmp.rax) != 0)
            continue;
        raise(SIGALRM);
    }   
}


int main() {
    alarm(30);
    setvbuf(stdout, NULL, _IONBF, 0);
    child();
}
