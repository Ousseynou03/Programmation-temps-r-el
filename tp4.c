/*On cherche à réaliser un programme qui détermine le minimum et le maximum d’un tableau de 10 entiers d’une 
façon parallèle et non séquentielle. C.à.d. que le minimum et le maximum doivent être calculés d’une façon 
concurrentielle. 
Réaliser le programme en utilisant plusieurs processus.
Penser à utiliser scanf.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
int main(){
    int t[10];
    for(int i=0;i<10;i++){
        printf('Saisir le nb %d\n': i + 1);
        scanf('%d',&t[i]);
    }
    if(fork()==0){
        int max =t[0];
        for(int i=1;i<10;i++){
            if(t[i]>max]){
                max=t[i];
            }
        }
        printf("le max est %d\n",max);
    }
     int min =t[0];
        for(int i=1;i<10;i++){
            if(t[i]<min]){
                min=t[i];
            }
        }
        printf("le min est %d\n",min);
return 0;
}