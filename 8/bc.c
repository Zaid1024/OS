// CHILD
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
  int k = 2, n1, n2, n3;
  void *shmptr;
  int shm_fd = shm_open("OS", O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, 4096);
  shmptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
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
  return 0;
}