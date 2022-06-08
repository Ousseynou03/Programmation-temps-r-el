#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

int main(){
    int a,b,somme,multiplication,soustraction,division;
    printf("Entrer deux nombres \n:");
    scanf("%d%d",&a,&b);
    if(fork()!=0){
        somme=a + b;
        printf("La somme des deux nombres est = %d\n", somme);
    }else{
        soustraction=a - b;
        printf("La soustraction des deux nombres est = %d\n", soustraction);

    }
    if(fork()!=0){
        multiplication=a * b;
        printf("La multiplication des deux nombres est = %d\n", multiplication);
    }else{
        division=a / b;
        printf("La division des deux nombres est = %d\n", division);
    }
   

    return 0;
    
    
}