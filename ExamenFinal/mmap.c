#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>

int static *memoria_compartida;

int main(void) {
    memoria_compartida = mmap(NULL, sizeof(*memoria_compartida), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,0 );
    
    pid_t hijo;
    hijo = fork();

    if(hijo < 0) {
        perror("Error durante el fork()");
        exit(EXIT_FAILURE);
    } else if(hijo == 0) {
        puts("Ingresa un valor para la variable compartida: ");
        scanf("%d", &*memoria_compartida);
        munmap(memoria_compartida, sizeof(memoria_compartida));
        exit(0);
    } else {
        puts("Hola soy el padre y estoy esperando a que mi hijo haga su trabajo");
        wait(NULL);
        printf("Soy el padre, y mi hijo acabo su proceso y cambio el valor de la variable memoria_compartida a: %d \n", *memoria_compartida);
        munmap(memoria_compartida, sizeof(memoria_compartida));
    }

    return 0;
}
