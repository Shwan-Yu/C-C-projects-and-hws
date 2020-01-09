#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "counts.h"
#include "kv.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  counts_t * c = createCounts();
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    perror("Failed to open the input file!");
    exit(EXIT_FAILURE);
  }
  char * buf = NULL;
  size_t line_cap;
  int count_unknown = 0;
  while (getline(&buf, &line_cap, f) >= 0) {
    //replace '\n' with '\0' to remove '\n'
    buf[strlen(buf) - 1] = '\0';
    char * val = lookupValue(kvPairs, buf);
    if (val != NULL) {
      addCount(c, val);
    }
    else {
      count_unknown++;
    }
  }
  for (int j = 0; j < count_unknown; j++) {
    addCount(c, NULL);
  }
  if (!feof(f)) {
    fprintf(stderr, "Invalid input\n");
    exit(EXIT_FAILURE);
  }
  free(buf);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    exit(EXIT_FAILURE);
  }

  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
  //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc < 2) {
    fprintf(stderr, "Invalid numbers of input");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kv = readKVs(argv[1]);
  //count from 2 to argc (call the number you count i)
  for (int i = 2; i < argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    counts_t * c = countFile(argv[i], kv);
    //   (call this result c)
    //compute the output file name from argv[i] (call this outName)
    char * newName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(newName, "w");
    if (f == NULL) {
      perror("Failed to open the input file!");
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      exit(EXIT_FAILURE);
    };
    //free the memory for outName and c
    freeCounts(c);
    free(newName);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
