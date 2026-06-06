/*
Crea un entero en mmap inicializado a 0. El hijo suma 10 veces 1 en un bucle y termina. 
El padre espera, luego suma 5 veces 1 en un bucle. Al final el padre imprime el valor total (debe ser 15) y llama a munmap.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>

static int *memoria_compartida;

int main(void){
    pid_t hijo;
    int valorHijo;

    memoria_compartida = mmap(NULL, sizeof(*memoria_compartida), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,0);

    hijo = fork();

    if(hijo < 0) {
        perror("Error en la creación del fork");
        exit(1);
    } else if(hijo == 0) {
        for(int i = 0; i < 10; i++){
            (*memoria_compartida)++;
        }
        printf("Hijo: He terminado de sumar, mi resultado es: %d\n", *memoria_compartida);
        exit(0);
    } else {
        wait(NULL);

        for(int i = 0; i < 5; i++) {
            (*memoria_compartida)++;
        }
        printf("Valor total final: %d\n", *memoria_compartida);
    }
    return 0;
}