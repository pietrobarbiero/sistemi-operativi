#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(){
    pid_t pid, cpid;
    int status;

    printf("S1\n");
    pid = fork();
    if(pid == 0){
    	   sleep(1);
    	   printf("S2-child\n");
	   exit(0);
    }
    else{
	sleep(3);
	printf("S2-father\n");
	wait(NULL);
    }
    printf("S4\n");
    pid = fork();
    if(pid == 0){
           int status1 = 5;
    	   sleep(4);
    	   printf("S5-child\n");
	   printf("CHILD: fpid: %d; mypid: %d; mystatus: %d\n", getppid(), pid, status1);
	   status = -34;
	   exit(status1);
    }
    else{
	sleep(1);
	printf("S5-father\n");
	cpid = wait(&status);
	printf("FATHER: mypid=%d; cpid: %d; status: %x; ", getpid(), cpid, status);
	printf("WIFEXITED: %d; WEXITSTATUS: %d\n", WIFEXITED(status), WEXITSTATUS(status));
    }
    sleep(4);
    printf("S7\n");
    return 0;
}
