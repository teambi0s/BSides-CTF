#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stddef.h>
#include <string.h>
#include <errno.h>


#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/prctl.h>
#include <sys/types.h>
#include <sys/prctl.h>
#include <sys/syscall.h>
#include <sys/socket.h>

#include <linux/seccomp.h>
#include <linux/filter.h>
#include <linux/audit.h>


#define ArchField offsetof(struct seccomp_data, arch)
#define Allow(syscall)                                  \
  BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, SYS_##syscall, 0, 1), \
    BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL)

/* Returns the processors time stamp counter */
uint64_t rdtsc(){
  unsigned int lo,hi;

  /* CPUID instruction is used to serialize instruction execution. Serializing instruction execution
     guarantees that any modifications to flags, registers, and memory for previous instructions are completed before
     the next instruction is fetched and executed. */

  __asm__ __volatile__ ("cpuid");

  /* rdtsc instruction Reads the current value of the processor’s time-stamp counter (a 64-bit MSR) into the EDX:EAX registers.
     The EDX register is loaded with the high-order 32 bits of the MSR and the EAX register is loaded with the low-order 32 bits.*/

  __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
  return ((uint64_t)hi << 32) | lo;
}

/* Sleep Time */
struct timespec sleep_time={0,199998};

char * flag;
char user[0x100];
uint64_t t1;

void exit_(int ret)
{
  __asm__ ("movq 60,%rax");
  __asm__ ("syscall");
  __asm__ ("ret");
}

int get_inp(char *buffer, int size) {
  int retval = read(0, buffer, size);
  if (retval == -1)
    exit(0);
  if ( buffer[retval-1] == '\n')
    buffer[retval-1] = '\0';
  return retval-1;
}

int check(char * inp)
{
  struct timespec remaining_time;
  t1 = rdtsc();

  size_t i;
  for(i = 0 ; flag[i] != '\x00'; i++)
    {
      if(inp[i] != flag[i])
        {
          return 0;
        }
      nanosleep(&sleep_time,&remaining_time);
    }
  return 1;

}

void initialize()
{
  int fp;
  alarm(30);
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stdin, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  fp = open("/home/secureauth/flag.txt",0);
  if(fp==-1)
    exit(0);

  flag = mmap(NULL,0x1000,PROT_READ,MAP_PRIVATE,fp,0);
  close(fp);

  /* Seccomp filter */
  struct sock_filter filter[] = {
                                 /* validate arch */
                                 BPF_STMT(BPF_LD+BPF_W+BPF_ABS, ArchField),
                                 BPF_JUMP(BPF_JMP+BPF_JEQ+BPF_K, AUDIT_ARCH_X86_64, 1, 0),
                                 BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL),

                                 /* load syscall */
                                 BPF_STMT(BPF_LD+BPF_W+BPF_ABS, offsetof(struct seccomp_data, nr)),
                                 BPF_JUMP(0x35, 0x40000000, 0, 1),
                                 BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_KILL),

                                 /* list of allowed syscalls */
                                 Allow(open),  /* exits a processs */
                                 Allow(clone),     /* for malloc(), inside libc */
                                 Allow(fork),       /* called by printf */
                                 Allow(vfork),      /* for free(), inside libc */
                                 Allow(execve),       /* called by printf */
                                 Allow(creat),       /* called by printf */
                                 Allow(openat),       /* called by printf */
                                 Allow(execveat),       /* called by printf */

                                 /* and if we don't match above, die */
    BPF_STMT(BPF_RET+BPF_K, SECCOMP_RET_ALLOW),
  };
  struct sock_fprog filterprog = {
    .len = sizeof(filter)/sizeof(filter[0]),
    .filter = filter
  };

  if (prctl(PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0)) {
    perror("Could not start seccomp:");
    exit(1);
  }

  if (prctl(PR_SET_SECCOMP, SECCOMP_MODE_FILTER, &filterprog) == -1) {
    perror("Could not start seccomp:");
    exit(1);
  }

}

int main()
{
  initialize();
  printf("Enter Username: ");
  get_inp(user, 0x100);
  char buf[0x100]={0};
  printf("Enter the flag : ");
  get_inp(buf,0x500);
  int ret =  check(buf);

  if(ret == 1)
      write(1,"Correct flag!\n",14);

  munmap(flag,0x1000);
  flag = NULL;

  return 0 ;
}
