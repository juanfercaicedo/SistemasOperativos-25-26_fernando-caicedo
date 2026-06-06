#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>

#define SIZE 10

int main(void) {
    int numeros[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int numeroObjetivo;
    puts("Introduce el número que quieres buscar dentro del array del [1 - 10]\n");
    scanf("%d", &numeroObjetivo);

    pid_t hijo1, hijo2;

    hijo1 = fork();
    if(hijo1 == 0) {
        for(int i = 0; i < SIZE/2 ; i++) {
            if(numeros[i] == numeroObjetivo) {
                printf("El hijo 1 tiene el número objetivo: %d\n", numeroObjetivo);
                exit(0);
            } 
        }
        
        exit(1);
    }

    hijo2 = fork();
    if(hijo2 == 0) {
        for(int i = SIZE / 2; i < SIZE; i++) {
            if(numeros[i] == numeroObjetivo) {
                printf("El hijo 2 tiene el número objetivo: %d\n", numeroObjetivo);
                exit(0);
            }
        }

        exit(1);
    }

    int estado;
    int numeroEncontrado = 0;
    for (int i = 0; i < 2; i++) {
        wait(&estado);
        if(WIFEXITED(estado)) {
            if(WEXITSTATUS(estado) == 0) {
                numeroEncontrado = 1;
            }
        }
    }
    return 0;
}