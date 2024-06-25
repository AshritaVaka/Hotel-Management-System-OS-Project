#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<sys/types.h>


int main(){
	//Waiter Initialisation
	int waiternumber=0;
	printf("Enter Waiter ID:");
	scanf("%d",&waiternumber);
	//Shared Memory creation
	key_t key =ftok("menu.txt",waiternumber);
	if (key == -1) {
        printf("ftok falliure");
        return -1;
    	}
    	int shmid = shmget(key, 1000*sizeof(int), 0666| IPC_CREAT);
	if (shmid == -1) {
        printf("shmget falliure");
        return -1;
    	}
    	int *shared_memory = (int *)shmat(shmid, NULL, 0);
	if (shared_memory == (int *)-1) {
        printf("shmat falliure");
        return -1;
    	}
    	
    	key_t key1 =ftok("menu.txt",waiternumber+10);
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
	if (shared_memory1 == (int *)-1) {
        printf("shmat falliure");
        return -1;
    	}
    	
    	*shared_memory=10;
    	
    	*shared_memory=9;//1 Sync step
    	
    	int earnings=0;
    	
    	//Main LOOP
	while(1){
		int bill=0;
		while(*shared_memory!=10){}//4 rece num of customer
		//bill=0;
		
		int x=shared_memory[2];
		*shared_memory=9;
		
		
		int array[x][100];
	
		for(int i=0;i<x;i++){
			for(int j=0;j<100;j++){
			array[i][j]=0;
			}
		}
		int order[x][4];
		int customerincorrect[5]={0,0,0,0,0};
	
    	
    		int incorrectorder=1;
    	
    		while(incorrectorder){
    			for(int i=0;i<x;i++){
    			int wrong=0;
    			
    			
    			while(*shared_memory!=10){}
    			
    			
    			for(int j=0;j<100;j++){
				
				array[i][j]=shared_memory[j+3];
				
				
				if(array[i][j]<0){
				wrong=1;
				customerincorrect[i]=1;
				}
				if(j>3){
				if(array[i][j]>0){
				wrong=1;
				customerincorrect[i]=1;
				
				}
				}
			
			}
			
			
			
			
			if(shared_memory[1]==i){
			}else{
				printf("%d:%d",i,shared_memory[1]);
				printf("Desynchronisation");
				return -1;
			}
			
			*(shared_memory+2)=wrong;
			*shared_memory=9;//9
			
			
			if(i==x-1){
    			while(*shared_memory!=10){}//11
    			}
    			
    			
    			}
    	
    			incorrectorder=0;
    			
    			
			for(int j=0;j<5;j++){
				incorrectorder=customerincorrect[j]+incorrectorder;
			}
			
			
			
			
    		}
    		
    		
    		int total[4]={0,0,0,0};
    		
    		for(int j=0;j<x;j++){
    			for(int k=0;k<4;k++){
    				total[k]=total[k]+array[j][k];
    			}
    		}
    		
    		
    		fflush(stdout);
    		
    		bill=bill+30*total[0]+40*total[1]+25*total[2]+30*total[3];
    		earnings=bill+earnings;
    		printf("\nBill Amount for Table %d: %d INR\n",waiternumber,bill);
    		shared_memory[1]=bill;
    		
    		shared_memory[0]=9;
    		
    		while(*shared_memory!=10){}
    		x=shared_memory[2];
    		if(x==-1){
    			break;
    		}
    		shared_memory[1]=0;
    		shared_memory[2]=0;
    		
    		shared_memory[0]=9;
    		while(*shared_memory!=10){}
    	
    	
    		
    	
    	
    	}
    	shared_memory1[0]=0;
    	printf("Earnings:%d INR\n",earnings);
    	shared_memory1[1]=earnings;
    	shared_memory1[0]=1;
    	shmdt(shared_memory);
    	shmdt(shared_memory1);
	
	
	
}
