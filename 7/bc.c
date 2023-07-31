#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
  int k = 1, n1, n2, n3;
  void *shmptr;
  int shmid = shmget((key_t)1122, 4096, 0666);
  shmptr = shmat(shmid, NULL, 0666);
  printf("\nChild Printing:\n");
  int i = atoi(argv[1]);
  n3 = n1 = 0;
  n2 = 1;
  for (k = 1; k <= i; k++) {
    sprintf(shmptr, "%d ", n3);
    printf("%d ", n3);
    shmptr += strlen(shmptr);
    n1 = n2;
    n2 = n3;
    n3 = n1 + n2;
  }
  shmctl(shmid, IPC_RMID, NULL);
  return 0;
}