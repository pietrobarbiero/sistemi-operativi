#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

#define SIZE 4096

int mycopyf(char *rpath, char *wpath){
  int rF, wF, rbytes, wbytes;
  char *buf;
  buf = calloc(SIZE, sizeof(char));

  if((rF = open(rpath, O_RDONLY)) < 0){
    fprintf(stdout, "Errore in apertura\n");
    exit(10);
  }
  if((wF = open(wpath, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) < 0){
    fprintf(stdout, "Errore in apertura\n");
    exit(11);
  }

  while((rbytes = read(rF, buf, SIZE)) > 0){
    if((wbytes = write(wF, buf, strlen(buf))) != rbytes)
      fprintf(stderr, "Errore in scrittura %d/%d\n", wbytes, rbytes);
  }
  
  close(rF);
  close(wF);
  
  return 0;
}

int mycopy(char *spath, char *dpath){
  DIR* pdirs; //directory source
  DIR* pdird; //directory dest
  struct dirent *pstdir;
  struct stat pstat;
  char *rfilename, *wfilename;
  rfilename = malloc(SIZE*sizeof(char));
  wfilename = malloc(SIZE*sizeof(char));
  
  if((pdirs = opendir(spath)) == NULL){
    fprintf(stdout, "Errore\n");
    exit(2);
  }

  while((pstdir = readdir(pdirs)) != NULL){
    sprintf(rfilename, "%s/%s", spath, pstdir->d_name);
    sprintf(wfilename, "%s/%s", dpath, pstdir->d_name);
    if(stat(rfilename, &pstat) < 0){
      fprintf(stdout, "Errore\n");
      exit(3);
    }
    if(S_ISDIR(pstat.st_mode) && strcmp(".", pstdir->d_name) && strcmp("..", pstdir->d_name)){
      if(mkdir(wfilename, S_IRUSR | S_IWUSR | S_IXUSR) < 0){
	fprintf(stdout, "Errore %s\n", rfilename);
	exit(4);
      }
      fprintf(stdout, "%-30s %-30s\n", rfilename, wfilename);
      mycopy(rfilename, wfilename);
    }
    else if(S_ISREG(pstat.st_mode)){
      fprintf(stdout, "%-30s %-30s\n", rfilename, wfilename);
      mycopyf(rfilename, wfilename);
    }
  }

  return 0;
};

int main(int argc, char *argv[]){
  if(argc != 3){
    fprintf(stdout, "Errore\n");
    exit(1);
  }

  fprintf(stdout, "%-30s%-30s\n", "\nSOURCE", "DEST");
  if(!mycopy(argv[1], argv[2]))
    fprintf(stdout, "\nYUPPY!!!\n");

  return 0;
}
