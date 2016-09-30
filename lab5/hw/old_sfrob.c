#include <stdio.h>
#include <stdlib.h>

int frobcmp(char const *a, char const *b){
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
int main(){
  int size = 0;
  int space = 1024;
  int makePtr = 1;
  int maxPointers = 32;
  int numPointers = 0;
  char *input = (char*) malloc(sizeof(char)*space);
  char **stringPointers = (char**) malloc(sizeof(char*)*maxPointers);
  if(input == NULL){
    fprintf(stderr, "can't allocate memory\n");
    exit(1);
  }
  while(1){
    char temp = getc(stdin);
    if(size == space){
      space*=2;
      input = (char*) realloc(input, sizeof(char)*space);
      if(input == NULL){
	fprintf(stderr, "realloc failed\n");
	exit(1);
      }
    }
    if(temp == EOF)       // checks if it's the end of file
      break;
    input[size] = temp;
    if(makePtr){
      if(numPointers == maxPointers){
	maxPointers *= 2;
	stringPointers = (char**)realloc(stringPointers, sizeof(char*)*maxPointers);
	if(stringPointers == NULL){
	  fprintf(stderr, "realloc failed\n");
	  exit(1);
	}
      }
      fprintf(stderr, "Location %d has %s\n", input+size, input+size);
      stringPointers[numPointers] = (input+size);
      numPointers++;
    }
    size++;
    makePtr = (temp == ' ')? 1:0; // Makes a new pointer next time if current character is a space
  }
  if(size == 0){
    return 0;
  }
  if(input[size-1] != ' '){   // Checks if the last character is a space. This helps distinguish the last word
    if(size == space){
      space*=2;
      input = (char*) realloc(input, sizeof(char)*space);
      if(input == NULL){
	fprintf(stderr, "realloc failed\n");
	exit(1);
      }
    }
    input[size] = ' ';
    size++;
  }
  for(int i=0; i<numPointers; i++){
    printf("Pointer %d: %s\n", i, *(stringPointers[i]));
  }
}
