#include "outname.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * addOn = ".counts";
  int l = strlen(inputName);
  char * newName = malloc((l + 8) * sizeof(*newName));
  size_t i = 0;
  while (inputName[i] != '\0') {
    newName[i] = inputName[i];
    i++;
  }
  for (size_t j = 0; j < 7; j++) {
    newName[i] = addOn[j];
    i++;
  }
  newName[i] = '\0';
  return newName;
}
