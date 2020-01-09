#include "kv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");

  kvarray_t * kvarray = malloc(sizeof(*kvarray));
  kvarray->length = 0;
  kvarray->kvarray = NULL;
  size_t kvarray_cap = 0;
  char * buf = NULL;
  size_t line_cap;
  while (getline(&buf, &line_cap, f) >= 0) {
    char * p1 = strchr(buf, '=');
    if (p1 == NULL) {
      fprintf(
          stderr,
          "Incorrect format for the input - not finding the '=' that we want to find\n");
      exit(EXIT_FAILURE);
    }
    char * k;
    k = strndup(buf, (p1 - buf));
    p1++;

    char * p2 = strchr(p1, '\n');
    if (p2 == NULL) {
      fprintf(stderr,
              "Incorrect format for the input - not finding the ending sign that we want "
              "to find\n");
      exit(EXIT_FAILURE);
    }
    char * v;
    v = strndup(p1, (p2 - p1));

    kvpair_t kvpair;
    kvpair.key = k;
    kvpair.val = v;

    kvarray->kvarray =
        realloc(kvarray->kvarray, (kvarray_cap + 1) * sizeof(*kvarray->kvarray));
    kvarray->kvarray[kvarray_cap] = kvpair;
    kvarray_cap++;
  }
  free(buf);
  if (!feof(f)) {
    fprintf(stderr, "Invalid input\n");
    exit(EXIT_FAILURE);
  }
  kvarray->length = kvarray_cap;
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }
  return kvarray;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t l = pairs->length;
  for (size_t i = 0; i < l; i++) {
    free(pairs->kvarray[i].key);
    free(pairs->kvarray[i].val);
  }
  free(pairs->kvarray);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t l = pairs->length;
  for (size_t i = 0; i < l; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvarray[i].key, pairs->kvarray[i].val);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  size_t l = pairs->length;
  for (size_t i = 0; i < l; i++) {
    if (strcmp(pairs->kvarray[i].key, key) == 0) {
      return pairs->kvarray[i].val;
    }
  }
  return NULL;
}
