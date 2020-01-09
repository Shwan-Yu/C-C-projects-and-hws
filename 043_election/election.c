#include "election.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//include any other headers you need here...

//helper function for function "parseLine", use this to find the character we want.
void helper_findChar(size_t * i,
                     const char * input,
                     size_t inp_size,
                     char output[],
                     size_t out_size,
                     char charToFind) {
  // index for filling in output array
  size_t ind_output = 0;
  while (input[*i] != charToFind) {
    if (ind_output >= out_size - 1) {
      //too many characters for the output, invalid
      fprintf(stderr, "Too many characters for the output\n");
      exit(EXIT_FAILURE);
    }
    // copy each character before we find the character
    output[ind_output] = input[*i];
    //increase both index
    (*i)++;
    ind_output++;
    // if not find : or \0, format incorrect
    if (*i > inp_size) {
      fprintf(stderr,
              "Incorrect format for the input - not finding the char we want to find\n");
      exit(EXIT_FAILURE);
    }
  }
  //add string ending to the output
  output[ind_output] = '\0';
  // move i pass the char we find
  (*i)++;
}

// parseLine function, parse the input lines into three parts.
state_t parseLine(const char * line) {
  //STEP 1: write me
  state_t state;
  // array for the name
  char name[MAX_STATE_NAME_LENGTH] = "";
  // array of uint64_t for the population, should not be more than 21 chars long(considering \0), max is 18446744073709551615.
  const int size_uint64 = 21;
  char pop[size_uint64];
  // array of unsigned int for the votes, should not be more than 11 chars long (considering \0), max is 4294967295.
  const int size_uint = 11;
  char votes[size_uint];
  size_t i = 0;
  // find the first column
  helper_findChar(&i, line, strlen(line), name, MAX_STATE_NAME_LENGTH, ':');
  // find the second column
  helper_findChar(&i, line, strlen(line), pop, size_uint64, ':');
  // find the ending of the string
  helper_findChar(&i, line, strlen(line), votes, size_uint, '\0');
  //update state variable
  strncpy(state.name, name, MAX_STATE_NAME_LENGTH);
  // since atoi cannot handle unsigned int and unsigned long int (atoi overflows when reach 2^31-1), we use strtoul.
  uint64_t p = strtoul(pop, NULL, 10);
  unsigned v = strtoul(votes, NULL, 10);

  //all code below checks for overflow for both p and v

  //check if overflows, cast int back to string and compare
  char castback_p[size_uint64];
  char castback_v[size_uint];
  //cast back from uint64_t
  sprintf(castback_p, "%lu", p);
  //cast back from unsigned int
  sprintf(castback_v, "%u", v);
  //check if overflows by comparing the string casted back with the original string, if not equals, then detected overflows.
  if (strcmp(castback_p, pop) != 0) {
    fprintf(stderr, "Input value of the population or electrical votes overflows\n");
    exit(EXIT_FAILURE);
  }
  if (strcmp(castback_v, votes) != 0) {
    fprintf(stderr, "Input value of the electrical votes overflows\n");
    exit(EXIT_FAILURE);
  }

  //assign the values
  state.electoralVotes = v;
  state.population = p;
  return state;
}

//count electrical votes for candidate A
unsigned int countElectoralVotes(state_t * stateData,
                                 uint64_t * voteCounts,
                                 size_t nStates) {
  //STEP 2: write me
  unsigned int totalVotesRecieved = 0;
  //go through all states.
  for (size_t i = 0; i < nStates; i++) {
    state_t state = stateData[i];
    uint64_t totalPop = state.population;
    unsigned int votes = state.electoralVotes;
    //if counts * 2 > population, get all electoral votes
    if (voteCounts[i] * 2 > totalPop) {
      totalVotesRecieved += votes;
    }
  }
  return totalVotesRecieved;
}

//print out the states that need recount
void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  //go through all states.
  for (size_t i = 0; i < nStates; i++) {
    state_t state = stateData[i];
    uint64_t totalPop = state.population;
    //if counts / population between 49.5~50.5, recount
    double percent = voteCounts[i] * 100 / (long double)(totalPop);
    if ((percent >= 49.5) && (percent <= 50.5)) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             state.name,
             percent);
    }
  }
}

//print out the states that A wins the largest proportion of votes.
void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  double largestVotes = 0.0;
  char largestWinningState[MAX_STATE_NAME_LENGTH] = "";
  //go through all states.
  for (size_t i = 0; i < nStates; i++) {
    state_t state = stateData[i];
    uint64_t totalPop = state.population;
    //calculate counts / population
    double percent = voteCounts[i] * 100 / (long double)(totalPop);
    // if find larger percentage
    if (percent > largestVotes) {
      //store all the info needed
      largestVotes = percent;
      strncpy(largestWinningState, state.name, MAX_STATE_NAME_LENGTH);
    }
  }
  printf(
      "Candidate A won %s with %.2f%% of the vote\n", largestWinningState, largestVotes);
}
