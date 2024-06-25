#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>
int main(){
		key_t key =ftok("earnings.txt",1);
		if (key == -1) {
        		printf("ftok falliure");
        		return -1;
    		}
    		int shmid1 = shmget(key, 1000*sizeof(int), 0666| IPC_CREAT);
		if (shmid1 == -1) {
        		printf("shmget falliure");
        		return -1;
    		}
    		int *shared_memory = (int *)shmat(shmid1, NULL, 0);
		if (shared_memory == (int *)-1) {
        	printf("shmat falliure");
        	return -1;
    		}
		shared_memory[0]=0;
		while(1){
			printf("Do you want to close the hotel? Enter Y for Yes and N for No. \n");
			char input;
			scanf("%c",&input);
			if(input=='Y'||input=='y'){
				shared_memory[0]=2;
				return 0;
			}else{
				shared_memory[0]=1;
			}
			
		}
}
