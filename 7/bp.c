// PARENT
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int i, k, n1, n2, n3;
  pid_t pid;
  const int SIZE = 4096;
  void *shmptr;
  int shmid = shmget((key_t)1122, 4096, 0666 | IPC_CREAT);
  shmptr = shmat(shmid, NULL, 0666);
  if (argc > 1) {
    sscanf(argv[1], "%d", &i);
    if (i < 1) {
      printf("\nWrong input is passed:\n");
      return 0;
    }
  } else {
    printf("\nN is not passed in the command line\n");
    return 1;
  }
  pid = fork();
  if (pid == 0) {
    // This is the child process part
    execlp("./fib", "fib", argv[1], NULL);
  } else if (pid > 0) {
    wait(NULL);
    printf("\n[PARENT] Child completed\n");
    printf("\nParent printing:\n");
    printf("%s\n", (char *)shmptr);
    shmdt(shmptr);
  }
  return 0;
}