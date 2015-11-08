#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>

int myread(char *path){
  struct dirent *structdir;
  DIR* pdir;
  struct stat buff;
  char *fullpath;
  fullpath = malloc(100*sizeof(char));
  
  //fprintf(stdout, "path: %s\n", path);
  if((pdir = opendir(path)) == NULL){
    fprintf(stdout, "Errore\n");
    exit(2);
  }
  
  while((structdir = readdir(pdir)) != NULL){
    if(stat(path, &buff) < 0){
      fprintf(stdout, "Errore\n");
      exit(3);
    }
    if(S_ISDIR(buff.st_mode)){
      sprintf(fullpath, "%s/%s", path, structdir->d_name);
      stat(fullpath, &buff);
      if(S_ISDIR(buff.st_mode)){
	fprintf(stdout, "DIR:  %s\n", fullpath);
	if(strcmp(".", structdir->d_name) && strcmp("..", structdir->d_name))
	  myread(fullpath);
      }
      else if(S_ISREG(buff.st_mode))
	fprintf(stdout, "FILE: %s\n", fullpath);
    }
    else{
      fprintf(stdout, "FILE: %s/%s\n", path, structdir->d_name);
    }
  }

  return 0;
};

int main(int argc, char *argv[]){
  if(argc != 2){
    fprintf(stdout, "Errore nei parametri\n");
    exit(1);
  }
  
  fprintf(stdout, "************\n\nTYPE  FILENAME\n");

  if(!myread(argv[1]))
    fprintf(stdout, "\nYUPPY!!!\n");

  fprintf(stdout, "\n\n************\n");

  return 0;
}
