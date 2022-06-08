#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

define N 10
void add( int *a, int *b, int *c ) {
 int tid = 0; // Le premier indice est zéro
 while (tid < N) {
 c[tid] = a[tid] + b[tid];
 tid += 1; // Il n’y a qu’un seul CPU, donc on progresse de 1 en 1
 }
}

int main(){
    pthread_t thread1, thread2,thread3,thread4;
     int a[N], b[N], c[N];
      for (int i=0; i<N; i++) {
 a[i] = -i;
 b[i] = i * i;
 } 
}