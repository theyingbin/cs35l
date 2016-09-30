#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( int argc, char* argv[] ){
  if(argc != 3){
    fprintf(stderr, "%s should take 2 strings as input\n", argv[0]);
    exit(1);
  }
  if( strlen(argv[1]) != strlen(argv[2]) ){
    fprintf(stderr, "input strings are not the same length\n");
    exit(1);
  }
  // check for duplicate bytes in from before processing
  int len = strlen(argv[1]);
  for(int i=0; i<len; i++){
    for(int j=i+1; j<len; j++){
      if(argv[1][i] == argv[1][j]){
	fprintf(stderr, "%s has duplicate bytes\n", argv[1]);
	exit(1);
      }
    }
  }
  while(1){
    int temp = getchar();
    if(temp == EOF)
      break;
    int index = -1;
    for(int i=0; i<strlen(argv[1]); i++){
      if(argv[1][i] == temp){
	index = i;
	break;
      }
    }
    if(index != -1){
      temp = argv[2][index];
    }
    putchar(temp);
  }
  exit(0);
}
