/*
On cherche à réaliser un programme qui détermine le minimum et le maximum d’un tableau de 10 entiers d’une
façon parallèle et non séquentielle. C.à.d. que le minimum et le maximum doivent être calculés d’une façon 
concurrentielle. 
Réaliser le programme en utilisant les threads. 
*/

#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void* max(void* arr){
    int* tab = (int*) arr;
    int max =tab[0],i;
    for(i=0;i<10;i++){
        if(tab[i]>max)
        max=tab[i];
    }
    printf("max=%d\n",max);
}
void* min(void *arr){
    int* tab = (int*) arr;
    int min =tab[0],i;
    for(i=0;i<10;i++){
        if(tab[i]<min)
        min=tab[i];
    }
    printf("min=%d\n",min);
}
int main(){
    pthread_t thread1, thread2;
    int tab[10],i;
    for(i=0;i<10;i++){
        printf("Saisir l'entier N° %d:",i+1);
        scanf("%d",&tab[i]);
    }
    pthread_create(&thread1, NULL ,max, (void*) tab);
    pthread_create(&thread2, NULL ,min, (void*) tab);
    pthread_join(thread1, NULL);
    pthread_join(thread2,NULL);

    return EXIT_SUCCESS;
}


//Cette nouvelle solution donne le même résultat

/*
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void min(int tab[]){
    int min=tab[0];
    for(int i=0;i<10;i++){
        if(min>tab[i]){
            min = tab[i];
        }
    }
    print("min = %d\n", min);
}

void max( int tab[]){
    int max=tab[0];
    for(int i=0;i<10;i++){
        if(max<tab[i]){
            max = tab[i]
        }
    }
    print("max = %d\n", max);
}
int main(){
    
    int tab[10],i;
    for(i=0;i<10;i++){
        printf("Saisir la valeur %d SVP\n:",i+1);
        scanf("%d",&tab[i]);
    }
    pthread_t thread1; 
    pthread_t thread2;

            pthread_create(&thread1, NULL ,min, (int*) tab);
            pthread_create(&thread2, NULL ,max, (int*) tab);
            pthread_join(thread1, NULL);
            pthread_join(thread2,NULL);

    pthread_exit(NULL);

*/