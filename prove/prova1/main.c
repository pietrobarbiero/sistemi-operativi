#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFSIZE 4096

int main(int argc, char *argv[]){
    int nR, nW, fdR, fdW;
    char buf[BUFFSIZE];
    
    if(argc!=3){
      fprintf(stderr, "Error in number of parameters");
    }
    
    fdR = open(argv[1], O_RDONLY);
    fdW = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if(fdR==(-1) || fdW==(-1)){
    	  fprintf(stdout, "Error Opening a File.\n");
	  exit(1);
    }
    
    while((nR = read(fdR, buf, BUFFSIZE)) > 0){
    	  nW = write (fdW, buf, nR);
    	  if (nR != nW)
    	     fprintf(stderr,"Error: Read %d, Write %d).\n", nR, nW);
    }
    if (nR < 0)
       fprintf(stderr, "Write Error.\n");
    
    close(fdR);
    close(fdW);
    exit(0);
}
