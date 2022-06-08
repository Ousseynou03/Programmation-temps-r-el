#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void* somme(void* arr){
    int* somme = (int*) arr;
    somme = a + b;
    printf("La somme des deux nombres est = %d\n", somme);
}
void* soustraction(void* arr){
    int* soustraction = (int*) arr;
        soustraction=a - b;
        printf("La soustraction des deux nombres est = %d\n", soustraction);
}
void* multiplication(void* arr){
    int* multiplication = (int*) arr;
    multiplication=a * b;
        printf("La multiplication des deux nombres est = %d\n", multiplication);
}
void* division(void* arr){
    int* division = (int*) arr;
    division=a / b;
        printf("La division des deux nombres est = %d\n", division);
}

int main(){
    int a,b,somme,multiplication,soustraction,division;
    printf("Entrer deux nombres \n:");
    scanf("%d%d",&a,&b);
 
    pthread_create(&arr, NULL ,somme, (void*) somme);
    pthread_create(&arr, NULL ,soustraction, (void*) soustraction);
    pthread_create(&arr, NULL ,multiplication, (void*) multiplication);
    pthread_create(&arr, NULL ,division, (void*) division);

    return EXIT_SUCCESS;
}
