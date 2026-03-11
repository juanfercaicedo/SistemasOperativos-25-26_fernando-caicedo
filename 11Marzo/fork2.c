#include<stdio.h>
#include<unistd.h>

int main(void){
    printf("Esta línea la ejecuta el proceso padre, con PID: %d\n", getpid());
    fork();
    printf("Esta línea ejecuta al prceso que tiene PID: %d\n", getpid());
    return 0;
}

// getpid(); Obtiene el proceso