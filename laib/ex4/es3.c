#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

#define M 100
#define CMD 10

int copy(char *cmds, char **cmde, char *buf, int i, int last, int count){
	int j, k, t, m;
	
	for(j=last, m=0, k=0, t=0; j<i; j++, m++){
		if(buf[j] == ' '){
			t++;
			k = 0;
		}
		else{
			cmde[t][k] = buf[j];
			k++;
		}
		cmds[m] = buf[j];
	}
	return 0;
}

int execution(char *cmds, char **cmde, int count){
	if(!fork()){
		printf("system: %s\n", cmds);
		//system(cmds);
		exit(9);
	}
	else{
		int i=0;
		sleep(3);
		printf("exec: ");
		for(i=0; i < count; i++)
			printf("%s ", cmde[i]);
		//execlp(cmde[0], cmde[0], cmde[1], NULL);
		//execlp(cmde[0], cmde[0], cmde[1], cmde[2], cmde[3], cmde[4], cmde[5],
		 //cmde[6], cmde[7], cmde[8], NULL);
	}
	return 0;
}

int find(char *buf, int length){
	int i, last = 0, k=0, t, count=0;
	
	for(i=0; i<length; i++){
		if(buf[i] == ' ')
			count++;
		if(buf[i]=='e' && buf[i+1]=='n' && buf[i+2]=='d'){
			char *cmds = (char*)calloc(40, sizeof(char));
			char **cmde = (char**)malloc(count*sizeof(char*));
			for(t=0; t<CMD; t++)
				cmde[t] = (char*)malloc(40*sizeof(char));
			printf("\n%d\n", ++k);
			copy(cmds, cmde, buf, i, last, count);
			execution(cmds, cmde, count);
			printf("\n");
			last = i+4;
			i=i+4;
		}
	}
	return 0;
}

int main(int argc, char *argv[]){
	int f, length;
	char *buf;
	
	if(argc != 2){
		printf("Errore\n");
		exit(1);
	}
	if((f=open(argv[1], O_RDONLY)) < 0){
		printf("Errore\n");
		exit(2);
	}
	
	buf = calloc(M, sizeof(char));
	if(read(f, buf, M) > 0){
		length = strlen(buf);
		find(buf, length);
	}
	
	return 0;
}
