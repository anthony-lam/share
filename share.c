#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
	key_t key = ftok("share.c", 'R');
	int shmid = shmget(key, 1024, 0644 | IPC_CREAT);
	char *data = shmat(shmid, 0, 0);
	char *input = malloc(201);
	if (data[0]) {
		printf("Data: %s\n", data);
	}
	else {
		printf("Just Created\n");
	}
	
	printf("Do you want to change data?(y/n)\n");
	fgets(input,200,stdin);
	if(input[0]=='n'){
		exit(0);
	}
	if (input[0]=='y'){
		printf("Delete or modify? (type d/m)\n");
		fgets(input,200,stdin);
		if(input[0]=='d'){
			shmdt(data);
			shmctl(shmid, IPC_RMID, NULL);
			printf("deleted\n");
			return 0;
		}
		else{
			printf("Enter your modification:\n");
			fgets(data,200,stdin);
		}
	}
	else{
		exit(0);
	}
}