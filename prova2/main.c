#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]){
  struct stat buff;
  char *s;
  s = malloc(25*sizeof(char));

  if(stat(argv[1],&buff) < 0){
    fprintf(stdout, "stat error\n");
  }
  if(S_ISREG(buff.st_mode))
    strcpy(s, "un file");
  else if(S_ISDIR(buff.st_mode))
    strcpy(s, "una directory");
    
  printf("\n\n**********\nL'oggetto \"%s\" e': %s\n**********\n\n", argv[1], s);

  return 0;
}
