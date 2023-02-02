#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <unistd.h>
#include<sys/sem.h>
#include<errno.h>
#include<sys/types.h>
#include<stdlib.h>
#include <random>
using namespace std;

#define SEM_KEY 0x123456788
struct item{
char name[11];
float price[5]={0,0,0,0,0};
float avgPrice=0;
int index=0;
};
struct stuff{
struct item it[11];

};
struct tow_stuff
{
 struct stuff st[2];
};
struct sembuf sem_buf;
   struct semid_ds buf;
   int semid;
  int retval;
int bufferSize;
int buffsize=1;
void remove_semaphore();
struct stuff stf,stfold;
struct tow_stuff *tw_stuff;
int main(int argc, char *argv[])
{    
   bufferSize=atof(argv[1]);
   // scanf("%d",&bufferSize);
      while(1){
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key,sizeof(struct tow_stuff)*buffsize,0666|IPC_CREAT);
   
    // shmat to attach to shared memory
  tw_stuff = (struct tow_stuff *) shmat(shmid,(void*)0,0);
  // tw_stuff->st[2].it[2].price[3]=20;
//    semid = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
//    //printf("errno is %d and semid is %d\n", errno, semid);

// /* Got the semaphore */
//    if (semid >= 0) {
//       printf("First execution\n");
//       sem_buf.sem_op = 1;
//       sem_buf.sem_flg = 0;
//       sem_buf.sem_num = 0;
//       retval = semop(semid, &sem_buf, 1);
//       if (retval == -1) {
//          perror("Semaphore Operation: ");
//         exit(1);
//       }
//    } else if ((errno == EEXIST)) { // Already other process got it
//       int ready = 0;
//       printf("unwaiting\n");
//       semid = semget(SEM_KEY, 1, 0);
//       if (semid < 0) {
//          perror("Semaphore GET: ");
//          exit(1);
//       }
      
//       /* Waiting for the resource */
//       sem_buf.sem_op = 1; /* Releasing the resource */
//    retval = semop(semid, &sem_buf, 1);
//    }

   // if (semid >= 0) {
   //    printf("First Process\n");
   //    sem_buf.sem_op = 1;
   //    sem_buf.sem_flg = 0;
   //    sem_buf.sem_num = 0;
   //    retval = semop(semid, &sem_buf, 1);
   //    if (retval == -1) {
   //       perror("Semaphore Operation: ");
   //      exit(1);
   //    }
   // } else if (errno == EEXIST) { // Already other process got it
   //    int ready = 0;
   //    printf("Second Process\n");
   //    semid = semget(SEM_KEY, 1, 0);
   //    if (semid < 0) {
   //       perror("Semaphore GET: ");
   //       exit(1);
   //    }
      
   //    /* Waiting for the resource */
   //    sem_buf.sem_num = 0;
   //    sem_buf.sem_op = 0;
   //    sem_buf.sem_flg = SEM_UNDO;
   //    retval = semop(semid, &sem_buf, 1);
   //    if (retval == -1) {
   //       perror("Semaphore Locked: ");
   //       exit(1);
   //    }
   // }
  stf=tw_stuff->st[1];
  stfold=tw_stuff->st[2];
  // float avg=0;
  //   float sum;
  //   int count=0;
  //   // calculate average new
  //   for(int i=0 ;i<11 ;i++){
  //     sum=0;
  //     count=0;
  //     avg=0;
  //     for(int j=0; j<4 ;j++)
  //     {   if(stf.it[i].price[j] != 0){
  //           count+=1;
  //     }
  //       sum=sum+stf.it[i].price[j];
  //     }
  //   if(count !=0){
  //   avg=sum/count;
  //   stf.it[i].avgPrice=avg;}

  //   }
   
  //   // calculate average new
  //   for(int i=0 ;i<11 ;i++){
  //     sum=0;
  //     count=0;
  //     avg=0;
  //     for(int j=0; j<4 ;j++)
  //     {   if(stfold.it[i].price[j] != 0){
  //           count+=1;
  //     }
  //       sum=sum+stfold.it[i].price[j];
  //     }
  //   if(count !=0){
  //   avg=sum/count;
  //   stfold.it[i].avgPrice=avg;}

  //   }
    // printf("Data read from memory: %s\n",it->name);
    //  printf("Data read from memory: %f\n",it->price);
      
    //    printf("Data read from memory: %f\n",it->avgPrice);
  
     int oldindex,newindex;
    printf("\033[0;34m+----------------------------------+\033[0m\n");
    printf("\033[0;34m| Currency   | Price    | AvgPrice |\033[0m\n");
    printf("\033[0;34m+----------------------------------+\033[0m\n");
    for(int i=0 ;i<11 ;i++){
      newindex= (stf.it[i].index+4)%5;
      oldindex= (stf.it[i].index+3)%5;
      // if(newindex <0){
      //    newindex=0;
      // }
      // printf("%d   %d\n",oldindex,newindex);
     if(stf.it[i].price[newindex] > stfold.it[i].price[oldindex]) {
      printf("\033[0;32m| %-10s | %07.2f↑ | %07.2f↑ |\033[0m\n",stf.it[i].name,stf.it[i].price[stf.it[i].index-1],stf.it[i].avgPrice);

     } else if(stf.it[i].price[newindex] < stfold.it[i].price[oldindex]) {

      printf("\033[0;31m| %-10s | %07.2f↓ | %07.2f↓ |\033[0m\n",stf.it[i].name,stf.it[i].price[stf.it[i].index-1],stf.it[i].avgPrice);
     }  else {
      printf("\033[0;34m| %-10s | %08.2f | %08.2f |\033[0m\n",stf.it[i].name,stf.it[i].price[stf.it[i].index-1],stf.it[i].avgPrice);
     }
    //  printf("Data written in memory Name : %s\n",stf.it[i].name);
    // printf("Data written in memory Price: %f %f %f %f \n",stf.it[i].price[0],stf.it[i].price[1],stf.it[i].price[2],stf.it[i].price[3]);
    // printf("Data written in memory avg price: %f\n",stf.it[i].avgPrice);
    // printf("\n");

     }
      printf("\033[0;34m+----------------------------------+\033[0m\n");
    
  //   printf("new\n \n \n");
  //    for(int i=0 ;i<11 ;i++){
    
  // printf("Data written in memory Name : %s\n",stf.it[i].name);
  //   printf("Data written in memory Price: %f %f %f %f \n",stf.it[i].price[0],stf.it[i].price[1],stf.it[i].price[2],stf.it[i].price[3]);
  //   printf("Data written in memory avg price: %f\n",stf.it[i].avgPrice);
  //   printf("\n");

  //    }printf("old \n \n \n");
  //      for(int i=0 ;i<11 ;i++){
        
  // printf("Data written in memory Name : %s\n",stfold.it[i].name);
  //   printf("Data written in memory Price: %f %f %f %f \n",stfold.it[i].price[0],stfold.it[i].price[1],stfold.it[i].price[2],stfold.it[i].price[3]);
  //   printf("Data written in memory avg price: %f\n",stfold.it[i].avgPrice);
  //   printf("\n");

  //    }
// sem_buf.sem_op = 1; /* Releasing the resource */
//    retval = semop(semid, &sem_buf, 1);
   
   if (retval == -1) {
      perror("Semaphore Locked\n");
      exit(1);
   }
   //  remove_semaphore(); 
   //   sem_buf.sem_op = 1; /* Releasing the resource */
   // retval = semop(semid, &sem_buf, 1);
    //detach from shared memory 
    shmdt(tw_stuff);
    
    // destroy the shared memory
    shmctl(shmid,IPC_RMID,NULL);
     usleep(1000000);
    }
    return 0;
}
void remove_semaphore() {
   int semid;
   int retval;
   semid = semget(SEM_KEY, 1, 0);
      if (semid < 0) {
         perror("Remove Semaphore: Semaphore GET: ");
         return;
      }
   retval = semctl(semid, 0, IPC_RMID);
   if (retval == -1) {
      perror("Remove Semaphore: Semaphore CTL: ");
      return;
   }
   return;
}