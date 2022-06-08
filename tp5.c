#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include<pthread.h>

void* f1(void* i)

{
    printf("Bonjour, je suis le thread1 %d\n", (int) i);
    pthread_exit(NULL);
}
void* f2(){
     printf("Bonjour, je suis le thread2 %d\n");
     pthread_exit(NULL);
}
void* f3(){
     for(int i=0;i<10000000;i++){
        
      } 
      printf("Bonjour, je suis le thread3 %d\n");
         pthread_exit(NULL);
     
}
int main(){
    //int i=2;
    pthread_t thread1;
    pthread_t thread2;
    pthread_t thread3;
    printf("Je suis le pere\n");
    pthread_create(&thread1, NULL ,f1, (void*) i); // Le premier élément est le nom du thread,le deuxiéme argument est la priorité(NULL), le troiséme argument est la fonction a éxécuté et le 4é argument est la valeur dans la fonction elle mm
    pthread_join(thread1, NULL);
    pthread_create(&thread2, NULL ,f2, NULL);
    pthread_join(thread2,NULL);
    pthread_create(&thread3, NULL ,f3, NULL);
    pthread_join(thread3,NULL); // Le pthread_join attend le résultat du thread précédent avant de commencer.
    
    
    return EXIT_SUCCESS;
}

