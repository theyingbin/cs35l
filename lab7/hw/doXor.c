#include <stdio.h>

int main(){
  for(int i=0; i<=255; i++){
    int j = i^42;
    printf("\\%03o", j);
    //printf("\\%03o", i);
  }
}
