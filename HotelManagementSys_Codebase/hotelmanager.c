#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>


int main(){
	int numberoftables=0;
	printf("Enter the Total Number of Tables at the Hotel:");
	scanf("%d",&numberoftables);
	
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
	
	
	
	
	
	FILE *file = fopen("earnings.txt", "w");
	//Shared Memory creation
	int *SM[numberoftables];
	for(int i=0;i<numberoftables;i++){
		key_t key1 =ftok("menu.txt",i+11);
		if (key1 == -1) {
        		printf("ftok falliure");
        		return -1;
    		}
    		int shmid1 = shmget(key1, 1000*sizeof(int), 0666| IPC_CREAT);
		if (shmid1 == -1) {
        		printf("shmget falliure");
        		return -1;
    		}
    		int *shared_memory1 = (int *)shmat(shmid1, NULL, 0);
    		SM[i]=(int *)shmat(shmid1, NULL, 0);
		if (shared_memory1 == (int *)-1) {
        	printf("shmat falliure");
        	return -1;
    		}
    	}
    	
    	for(int i=0;i<numberoftables;i++){
    		SM[i][0]=0;
    	}
    	
    	int earnings[10]={0,0,0,0,0,0,0,0,0,0};
    	while(1){
    	for(int i=0;i<numberoftables;i++){
    		while(SM[i][0]==0){}
    	}
    	for(int i=0;i<numberoftables;i++){
    		earnings[i]= SM[i][1];
    	}
    	
    	const char *message = "Earning from Table ";

    
    	
    	for (int i = 0; i < numberoftables; i++) {
    	fprintf(file, "%s", message);
        fprintf(file, "%d: %d INR \n",(i+1), earnings[i]);
   	}
    	
    	
    	
    	
    	
    	while(shared_memory[0]==0){}
    	if(shared_memory[0]==2){
    		int total=earnings[0]+earnings[1]+earnings[2]+earnings[3]+earnings[4]+earnings[5]+earnings[6]+earnings[7]+earnings[8]+earnings[9];
    		printf("Total Earnings of Hotel: %d INR\n",total);
    		printf("Total Wages of Waiters: %d INR\n",((total*40)/100));
    		printf("Total Profit: %d INR\n",((total*60)/100));
    		printf("Thank you for visiting the Hotel!\n");
    		fclose(file);
    		return 0;
    	}else{
    		shared_memory[0]=0;
    	}
    	
    	}
    	printf("done");

}
