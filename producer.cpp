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
#include <time.h>
struct timespec ts;
char buff[100];
#define SEM_KEY 0x12345678888
using namespace std;
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
int sleeping_time;
struct stuff stf,stfold;
struct tow_stuff *tw_stuff;
void delete_sema();
float c_price;
char t_name[11];
int counter;
float no_std;
int bufferSize;
int buffsize=1;
int main(int argc, char *argv[])
{   
   // strcpy(t_name,argv[1]);
   // c_price=atof(argv[2]);
   // no_std=atof(argv[3]);
   // sleeping_time=atof(argv[4]);
   // bufferSize=atof(argv[5]);
    printf("Enter the Item name:: ");
    scanf("%s",t_name);
    printf("Enter the Item price: ");
    scanf("%f",&c_price);
      printf("Enter the std :");
      scanf("%f",&no_std);
        printf("Enter the waiting time:");
          scanf("%d",&sleeping_time);

  printf("Enter the buffer size:");
       scanf("%d",&bufferSize);
  default_random_engine generator;
  normal_distribution<float> distribution(c_price,no_std);
    // ftok to generate unique key
    key_t key = ftok("shmfile",65);
   while (1)
   {  timespec_get(&ts, TIME_UTC);
     strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
    
     fprintf(stderr,"[%s.%09ld] %s : generating a new value %f\n", buff, ts.tv_nsec,t_name,c_price);
    // shmget returns an identifier in shmid
    int shmid = shmget(key,sizeof(struct tow_stuff)*buffsize ,0666|IPC_CREAT);
  
    // shmat to attach to shared memory
    tw_stuff = (struct tow_stuff *) shmat(shmid,NULL,0);

   semid = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
   //printf("errno is %d and semid is %d\n", errno, semid);
   timespec_get(&ts, TIME_UTC);
     strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
    
     fprintf(stderr,"[%s.%09ld] %s : trying to get mutex on shared buffer\n", buff, ts.tv_nsec,t_name);
   /* Got the semaphore */
   if (semid >= 0) {
      // printf("Execution\n");
      sem_buf.sem_op = 1;
      sem_buf.sem_flg = 0;
      sem_buf.sem_num = 0;
      retval = semop(semid, &sem_buf, 1);
      if (retval == -1) {
         perror("Semaphore Operation: ");
        exit(1);
      }
   } else if (errno == EEXIST) { // Already other process got it
      int ready = 0;
      printf("Waiting\n");
      semid = semget(SEM_KEY, 1, 0);
      if (semid < 0) {
         perror("Semaphore GET: ");
         exit(1);
      }
      
      /* Waiting for the resource */
      sem_buf.sem_num = 0;
      sem_buf.sem_op = 0;
      sem_buf.sem_flg = SEM_UNDO;
      retval = semop(semid, &sem_buf, 1);
      if (retval == -1) {
         perror("Semaphore Locked: ");
         exit(1);
      }
   }
    stf=tw_stuff->st[1];
     strcpy(stf.it[4].name,"GOLD");
     strcpy(stf.it[9].name,"SILVER");
     strcpy(stf.it[3].name,"CRUDEOIL");
     strcpy(stf.it[7].name,"NATURALGAS");
     strcpy(stf.it[0].name,"ALUMINIUM");
     strcpy(stf.it[1].name,"COPPER");
     strcpy(stf.it[8].name,"NICKEL");
     strcpy(stf.it[5].name,"LEAD");
     strcpy(stf.it[10].name,"ZINC");
     strcpy(stf.it[6].name,"MENTHAOIL");
     strcpy(stf.it[2].name,"COTTON");
    stfold=stf;
    //  printf("Enter the Item name:: ");
    // scanf("%s",t_name);
    // printf("Enter the Item price: ");
    // scanf("%f",&c_price);
    for(int i=0; i< 11; i++){
     if(strcmp(t_name,stf.it[i].name)==0)
     {
    //  printf("Data written in memory Name : %s\n",stf.it[i].name);
      stf.it[i].price[stf.it[i].index]=c_price;
      stf.it[i].index= (stf.it[i].index+1)%5;
      break;
     }
    }
    float avg=0;
    float sum;
    int count=0;
    // calculate average new
    for(int i=0 ;i<11 ;i++){
      sum=0;
      count=0;
      avg=0;
      for(int j=0; j<5 ;j++)
      {   if(stf.it[i].price[j] != 0){
            count+=1;
      }
        sum=sum+stf.it[i].price[j];
      }
    if(count !=0){
    avg=sum/count;
    stf.it[i].avgPrice=avg;}

    }
     timespec_get(&ts, TIME_UTC);
     strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
    
     fprintf(stderr,"[%s.%09ld] %s :  placing %f on shared buffer\n", buff, ts.tv_nsec,t_name,c_price);
    tw_stuff->st[1]=stf;
    tw_stuff->st[2]=stfold;
    // cout<<"Write Data : ";
    // strcpy(it->name, argv[1]);
    // it->price=  atof(argv[2]);
    // it->avgPrice = atof(argv[3]);
    
//       printf("new\n \n \n");
//      for(int i=0 ;i<11 ;i++){
    
//   printf("Data written in memory Name : %s\n",stf.it[i].name);
//     printf("Data written in memory Price: %f %f %f %f %f\n",stf.it[i].price[0],stf.it[i].price[1],stf.it[i].price[2],stf.it[i].price[3],stf.it[i].price[4]);
//     printf("Data written in memory avg price: %f\n",stf.it[i].avgPrice);
//     printf("\n");

//      }printf("old \n \n \n");
//        for(int i=0 ;i<11 ;i++){
        
//   printf("Data written in memory Name : %s\n",stfold.it[i].name);
//     printf("Data written in memory Price: %f %f %f %f  %f\n",stfold.it[i].price[0],stfold.it[i].price[1],stfold.it[i].price[2],stfold.it[i].price[3],stfold.it[i].price[4]);
//     printf("Data written in memory avg price: %f\n",stfold.it[i].avgPrice);
//     printf("\n");

//      }
   sem_buf.sem_op = 1; /* Releasing the resource */
   retval = semop(semid, &sem_buf, 1);
   
   if (retval == -1) {
      perror("Semaphore Locked\n");
      exit(1);
   }
    delete_sema();  
    //detach from shared memory 
    shmdt(tw_stuff);
    c_price= distribution(generator);
    timespec_get(&ts, TIME_UTC);
     strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
    
     fprintf(stderr,"[%s.%09ld] %s :  sleeping for %d s\n", buff, ts.tv_nsec,t_name,sleeping_time);
    usleep(sleeping_time*1000000);
   }
    return 0;
  
}

void delete_sema() {
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


// #include <iostream>
// #include <sys/ipc.h>
// #include <sys/shm.h>
// #include <stdio.h>
// #include <string>
// #include <cstring>
// #include <unistd.h>
// #include<sys/sem.h>
// #include<errno.h>
// #include<sys/types.h>
// #include<stdlib.h>
// #include <random>
// #define SEM_KEY 0x12345678899
// using namespace std;
// struct item{
// char name[11];
// float price[5]={0,0,0,0,0};
// float avgPrice=0;
// int index=0;
// };
// struct stuff{
// struct item it[11];

// };
// struct tow_stuff
// {
//  struct stuff st[2];
// };
// struct sembuf sem_buf;
//    struct semid_ds buf;
//  int semid;
//   int retval;
// int sleeping_time;
// struct stuff stf,stfold;
// struct tow_stuff *tw_stuff;
// void delte_semaphore();
// float c_price;
// char t_name[11];
// int counter;
// float no_std;
// int bufferSize;
//  printf("Enter the Item name:: ");
//     scanf("%s",t_name);
//     printf("Enter the Item price: ");
//     scanf("%f",&c_price);
//       printf("Enter the std :");
//       scanf("%f",&no_std);
//         printf("Enter the waiting time:");
//       scanf("%d",&sleeping_time);
//        printf("Enter the buffer size:");
//       scanf("%d",&bufferSize);
// // struct multi_tow_stuff
// // {
// //  struct stuff mst[bufferSize];
// // };
// // struct multi_tow_stuff *mul_st;
// int main(int argc, char *argv[])
// {   
   
   

//   default_random_engine generator;
//   normal_distribution<float> distribution(c_price,no_std);
//     // ftok to generate unique key
//     key_t key = ftok("shmfile",65);
//    while (1)
//    {
     
//     // shmget returns an identifier in shmid
//     int shmid = shmget(key,sizeof(struct tow_stuff),0666|IPC_CREAT);
//    //  int shmid = shmget(key,sizeof(struct multi_tow_stuff),0666|IPC_CREAT);
//     // shmat to attach to shared memory
//    //  mul_st = (struct multi_tow_stuff *) shmat(shmid,NULL,0);
//    tw_stuff = (struct tow_stuff *) shmat(shmid,(void*)0,0);
//    semid = semget(SEM_KEY, 1, IPC_CREAT | IPC_EXCL | 0666);
//    //printf("errno is %d and semid is %d\n", errno, semid);
   
//    /* Got the semaphore */
//    if (semid >= 0) {
//       printf("First Process\n");
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
//       printf("Un waiting\n");
//       semid = semget(SEM_KEY, 1, 0);
//       if (semid < 0) {
//          perror("Semaphore GET: ");
//          exit(1);
//       }
      
//       /* Waiting for the resource */
//       sem_buf.sem_num = 0;
//       sem_buf.sem_op = 0;
//       sem_buf.sem_flg = SEM_UNDO;
//       retval = semop(semid, &sem_buf, 1);
//       if (retval == -1) {
//          perror("Semaphore Locked: ");
//          exit(1);
//       }
//    }
//    //  stf=mul_st->mst[1]->st[1];
//   stf=tw_stuff->st[1];
//      strcpy(stf.it[4].name,"GOLD");
//      strcpy(stf.it[9].name,"SILVER");
//      strcpy(stf.it[3].name,"CRUDEOIL");
//      strcpy(stf.it[7].name,"NATURALGAS");
//      strcpy(stf.it[0].name,"ALUMINIUM");
//      strcpy(stf.it[1].name,"COPPER");
//      strcpy(stf.it[8].name,"NICKEL");
//      strcpy(stf.it[5].name,"LEAD");
//      strcpy(stf.it[10].name,"ZINC");
//      strcpy(stf.it[6].name,"MENTHAOIL");
//      strcpy(stf.it[2].name,"COTTON");
//     stfold=stf;
//     //  printf("Enter the Item name:: ");
//     // scanf("%s",t_name);
//     // printf("Enter the Item price: ");
//     // scanf("%f",&c_price);
//     for(int i=0; i< 11; i++){
//      if(strcmp(t_name,stf.it[i].name)==0)
//      {
//     //  printf("Data written in memory Name : %s\n",stf.it[i].name);
//       stf.it[i].price[stf.it[i].index]=c_price;
//       stf.it[i].index= (stf.it[i].index+1)%5;
//       break;
//      }
//     }
//     float avg=0;
//     float sum;
//     int count=0;
//     // calculate average new
//     for(int i=0 ;i<11 ;i++){
//       sum=0;
//       count=0;
//       avg=0;
//       for(int j=0; j<5 ;j++)
//       {   if(stf.it[i].price[j] != 0){
//             count+=1;
//       }
//         sum=sum+stf.it[i].price[j];
//       }
//     if(count !=0){
//     avg=sum/count;
//     stf.it[i].avgPrice=avg;}

//     }
//     tw_stuff->st[1]=stf;
//     tw_stuff->st[2]=stfold;
//     // cout<<"Write Data : ";
//     // strcpy(it->name, argv[1]);
//     // it->price=  atof(argv[2]);
//     // it->avgPrice = atof(argv[3]);
    
//       printf("new\n \n \n");
//      for(int i=0 ;i<11 ;i++){
    
//   printf("Data written in memory Name : %s\n",stf.it[i].name);
//     printf("Data written in memory Price: %f %f %f %f %f\n",stf.it[i].price[0],stf.it[i].price[1],stf.it[i].price[2],stf.it[i].price[3],stf.it[i].price[4]);
//     printf("Data written in memory avg price: %f\n",stf.it[i].avgPrice);
//     printf("\n");

//      }printf("old \n \n \n");
//        for(int i=0 ;i<11 ;i++){
        
//   printf("Data written in memory Name : %s\n",stfold.it[i].name);
//     printf("Data written in memory Price: %f %f %f %f %f\n",stfold.it[i].price[0],stfold.it[i].price[1],stfold.it[i].price[2],stfold.it[i].price[3],stfold.it[i].price[4]);
//     printf("Data written in memory avg price: %f\n",stfold.it[i].avgPrice);
//     printf("\n");

//      }
//    sem_buf.sem_op = 1; /* Releasing the resource */
//    retval = semop(semid, &sem_buf, 1);
   
//    if (retval == -1) {
//       perror("Semaphore Locked\n");
//       exit(1);
//    }
//     delte_semaphore();  
//     //detach from shared memory 
//     shmdt(tw_stuff);
//     c_price= distribution(generator);
//     usleep(sleeping_time*1000000);
//    }
//     return 0;
  
// }

// void delte_semaphore() {
//    int semid;
//    int retval;
//    semid = semget(SEM_KEY, 1, 0);
//       if (semid < 0) {
//          perror("Remove Semaphore: Semaphore GET: ");
//          return;
//       }
//    retval = semctl(semid, 0, IPC_RMID);
//    if (retval == -1) {
//       perror("Remove Semaphore: Semaphore CTL: ");
//       return;
//    }
//    return;
// }