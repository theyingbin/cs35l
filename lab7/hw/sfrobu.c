#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>

long comparisons = 0;

int frobcmp(char const *a, char const *b){
  comparisons++;
  int tempA;
  int tempB;
  int diff;

  while(*a != ' ' && *b != ' '){     // Checks that we haven't reached the end of the encrypted string
    tempA = *a ^ 42;             // Decrypts character
    tempB = *b ^ 42;
    diff = tempA - tempB;
    if(diff == 0){                   // If the character was the same, check next character
      a++;
      b++;
    }
    else{
      return diff;                   // else return negative value if a < b and positive if a > b
    }
  }
  if(*a == ' ' && *b == ' '){        
    return 0;                        // If a and b are the exact same string, return 0
  }
  else if(*a == ' '){
    return -1;                       // If a is a prefix of b, return -1
  }
  else{                 
    return 1;                        // If b is a prefix of a, return 1
  }
}
int compare(void const* a, void const* b){
  char const* first = *(char const**)a;
  char const* second = *(char const**)b;
  return frobcmp(first, second);
}
void printWord(char const* word){
  char buffer[1];
  while(*word != ' '){
    buffer[0] = *word;
    write(1, &buffer, 1);
    word++;
  }
  buffer[0] = ' ';
  write(1, &buffer, 1);
}
int main(){
  struct stat fileStats;
  fstat(0, &fileStats);
  int size = 0;
  int space;
  if(fileStats.st_size){
    space=fileStats.st_size;
  }
  else{
    space = 1024;
  }
  char *input = (char*) malloc(sizeof(char)*space);
  if(input == NULL){
    fprintf(stderr, "can't allocate memory\n");
    fprintf(stderr, "Comparisons: %d\n", comparisons);
    exit(1);
  }
  while(1){
    int temp[1];
    int readStatus = read(0, &temp, 1);
    if(readStatus < 0){
      fprintf(stderr, "read failed\n");
      fprintf(stderr, "Comparisons: %d\n", comparisons);
    }
    if(readStatus == 0){
      break;
    }
    if(size == space){
      space*=2;
      input = (char*) realloc(input, sizeof(char)*space);
      if(input == NULL){
	fprintf(stderr, "realloc failed\n");
	fprintf(stderr, "Comparisons: %d\n", comparisons);
	exit(1);
      }
    }
    input[size] = *temp;
    size++;
  }
  if(size == 0){
    fprintf(stderr, "Comparisons: %d\n", comparisons);
    return 0;
  }
  if(input[size-1] != ' '){   // Checks if the last character is a space. This helps distinguish the last word
    if(size == space){
      space*=2;
      input = (char*) realloc(input, sizeof(char)*space);
      if(input == NULL){
	fprintf(stderr, "realloc failed\n");
	fprintf(stderr, "Comparisons: %d\n", comparisons);
	exit(1);
      }
    }
    input[size] = ' ';
    size++;
  }
  int numWords = 0;
  for(int i=0; i<size; i++){
    if(input[i] == ' '){
      numWords++;
    }
  }
  int wordIndex=0;
  char **wordPtr=(char**) malloc(sizeof(char*)*numWords);
  for(int i=0; i<size; i++){
    wordPtr[wordIndex]=input+i;
    while(*(input+i) != ' '){
      i++;
    }
    wordIndex++;
  }
  qsort(wordPtr, numWords, sizeof(char*), compare);
  for(int i=0; i<numWords; i++){
    printWord(wordPtr[i]);
  }
  free(wordPtr);
  free(input);
  fprintf(stderr, "Comparisons: %d\n", comparisons);
  exit(0);
}
