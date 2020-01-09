#include <stdio.h>
#include <stdlib.h>

void rotate(int m, int n, int matrix[][n]) {
  for (int j = 0; j < n; j++) {
    for (int i = m - 1; i >= 0; i--) {
      printf("%c", matrix[i][j]);
    }
    printf("\n");
  }
}

void readFile(FILE * f) {
  int c;
  int matrix[10][10] = {0};
  int i = 0;
  int j = 0;
  int count = 0;
  while ((c = fgetc(f)) != EOF) {
    count++;
    //printf("%d, char = %c\n", count, c);
    if (count % 11 == 0) {
      if (c != '\n') {
        fprintf(stderr, "more than 10 characters a row\n");
        exit(EXIT_FAILURE);
      }
      else {
        continue;
      }
    }
    else if (count > 110) {
      fprintf(stderr, "more than 10 characters a column\n");
      exit(EXIT_FAILURE);
    }
    matrix[i][j] = (char)c;
    j++;
    if (j >= 10) {
      j = j % 10;
      i++;
    }
  }
  if (count < 110) {
    fprintf(stderr, "less than 10 * 10 characters\n");
    exit(EXIT_FAILURE);
  }
  rotate(10, 10, matrix);
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: rot inputFileName\n");
    exit(EXIT_FAILURE);
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    exit(EXIT_FAILURE);
  }
  readFile(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
  exit(EXIT_SUCCESS);
}
