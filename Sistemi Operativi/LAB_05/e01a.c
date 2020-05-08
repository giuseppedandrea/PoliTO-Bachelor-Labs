#include <stdio.h>

int main(int argcc, char *argv[]) {
  int val;
  
  while (fscanf(stdin, "%d", &val)) {
    if (val==0) {
      return 0;
    } else {
      if ((val%2)==0) { // pari
        fprintf(stdout, "%d\n", val);
      } else { // dispari
        fprintf(stderr, "%d\n", val);
      } 
    }
  }
    
  return 0;
}
