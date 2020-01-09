#include "counts.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
counts_t * createCounts(void) {
  //WRITE ME
  counts_t * c = malloc(sizeof(*c));
  c->c_array = NULL;
  c->sz = 0;
  return c;
}
void addCount(counts_t * c, const char * name) {
  //WRITE ME
  const char * n;
  if (name == NULL) {
    n = "<unknown>";
  }
  else {
    n = name;
  }
  for (size_t i = 0; i < c->sz; i++) {
    if (strcmp(c->c_array[i].str, n) == 0) {
      (c->c_array[i].count)++;
      return;
    }
  }
  one_count_t o_c;
  o_c.str = n;
  o_c.count = 1;

  c->c_array = realloc(c->c_array, (c->sz + 1) * sizeof(*(c->c_array)));
  c->c_array[c->sz] = o_c;
  (c->sz)++;
}
void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  for (size_t i = 0; i < c->sz; i++) {
    fprintf(outFile, "%s: %zd\n", c->c_array[i].str, c->c_array[i].count);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  free(c->c_array);
  free(c);
}
