#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
	pid_t pid;
	
	printf("P1: %d->%d\n", getppid(), getpid());
	
	pid = fork();
	if(pid==0){
		sleep(5);
		printf("P3: %d->%d\n", getppid(), getpid());
		pid = fork();
		if(pid==0){
			sleep(2);
			printf("P6: %d->%d\n", getppid(), getpid());
			exit(6);
		}
		else{
			wait(NULL);
		}
		printf("P8: %d->%d\n", getppid(), getpid());
		exit(8);
	}
	else{
		printf("P2: %d->%d\n", getppid(), getpid());
		if(fork()==0){
			sleep(2);
			printf("P5: %d->%d\n", getppid(), getpid());
			exit(5);
		}
		else{
			printf("P4: %d->%d\n", getppid(), getpid());
			wait(NULL);
		}
		printf("P7: %d->%d\n", getppid(), getpid());
		waitpid(pid, NULL, 0);
	}
	printf("P9: %d->%d\n", getppid(), getpid());
	
	
	return 0;
}
