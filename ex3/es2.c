#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int recursive(pid_t pidf, int *end, int *n, int *t){
	int i = 0;
	pid_t pid;
	
	if(*end == *n){
		return 0;
	}
	else{
		*end += 1;
		printf("\nPadre: %d\n", pidf);
		if((pid = fork()) > 0){
			printf("F1: %d->%d\n", getpid(), pid);
			if((pid = fork()) > 0){
				printf("F2: %d->%d\n", getpid(), pid);
			}
			else{
				sleep(*t);
				recursive(getpid(), end, n, t);
				return 0;
			}
			return 0;
		}
		else{
			sleep(*t);
			recursive(getpid(), end, n, t);
			return 0;
		}
	}
	return 0;
}

int main(int argc, char *argv[]){
	int end = 0, n, t;
	
	n = atoi(argv[1]);
	t = atoi(argv[2]);
	
	if(argc != 3){
		printf("Errore\n");
		exit(1);
	}
	
	recursive(getpid(), &end, &n, &t);
	
	return 0;
}
