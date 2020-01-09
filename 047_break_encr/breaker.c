#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

int maxInArray(int * array, int n) {
  int ind = -1;
  int max_val = -1;
  for (int i = 0; i < n; i++) {
    if (array[i] > max_val) {
      ind = i;
      max_val = array[i];
    }
  }
  //printf("val %d, ind %d\n", max_val, ind);
  return ind;
}

void breaker(FILE * f) {
  int c;
  int char_count[26] = {0};
  while ((c = fgetc(f)) != EOF) {
    if (isalpha(c)) {
      c = tolower(c);
      char_count[c - 'a'] += 1;
    }
  }
  int ind = maxInArray(char_count, 26);
  if (ind == -1) {
    fprintf(stderr, "No characters in input file");
  }
  else {
    printf("%d\n", ('a' + ind + 26 - 'e') % 26);
  }
}

int main(int argc, char ** argv) {
  if (argc != 2) {
    fprintf(stderr, "Usage: breaker inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f = fopen(argv[1], "r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  breaker(f);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
