#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void readFile(FILE * f) {
  char ** inputs = NULL;
  char * curr = NULL;
  size_t line_cap;
  size_t i = 0;
  while (getline(&curr, &line_cap, f) >= 0) {
    inputs = realloc(inputs, (i + 1) * sizeof(*inputs));
    inputs[i] = curr;
    curr = NULL;
    i++;
  }
  free(curr);
  sortData(inputs, i);
  for (size_t j = 0; j < i; j++) {
    printf("%s", inputs[j]);
    free(inputs[j]);
  }
  free(inputs);
}

int main(int argc, char ** argv) {
  if (argc == 1) {
    readFile(stdin);
  }
  else {
    for (int i = 1; i < argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could not open file\n");
        return EXIT_FAILURE;
      }
      readFile(f);
      if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
      }
    }
  }
  return EXIT_SUCCESS;
}
