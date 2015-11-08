#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main () {
	int i = 1;

	setbuf(stdout,0);
	while(i<=2 && fork()){
		if(!fork()){
			fprintf(stdout, "Running Exec ...");
			execlp("echo", "echo", "i*i", NULL);
		}
		i++;
		sleep(1);
		fprintf(stdout, "Running System ...");
		system("echo i+i\n");
	}
	return (0);
}
