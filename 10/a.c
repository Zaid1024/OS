#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
  FILE *fp;
  char ch;
  if (argc < 2) {
    printf("\nThe file name is not passed\n");
    exit(1);
  }
  f p = fopen(argv[1], "r");
  if (fp == NULL) {
    printf("\nThe file does not exist.\n");
    exit(1);
  }
  while ((ch = fgetc(fp)) != EOF) {
    printf("%c", ch);
  }
  f close(fp);
  return 0;
}