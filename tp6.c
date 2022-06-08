#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void* f1(){
     for(int i=0;i<20;i++){
        
      } 
      printf("Bonjour, je suis le thread1\n");
         pthread_exit(NULL);
     
}
int main(){
    for(int i=0;i<20;i++){ } 
    pthread thread1;
    printf("Je suis le pére \n");
    pthread_create(&thread1, NULL ,f1, NULL);
    //pthread_join(thread1[20], NULL);

    return EXIT_SUCCESS;
}
