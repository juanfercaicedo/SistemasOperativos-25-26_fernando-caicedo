#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int mi_tuberia[2];
    pid_t hijo;
    
    int numeroHijo = 42;
    int numeroRecibidoPorPadre;

    pipe(mi_tuberia);
    hijo = fork();

    if(hijo < 0) {
        perror("ERROR EN LA CREACION DEL HIJO!!!!");
        exit(0);
    } else if(hijo == 0) {
        close(mi_tuberia[0]);
        write(mi_tuberia[1], &numeroHijo, sizeof(numeroHijo));
        close(mi_tuberia[1]);

        exit(0);
    } else {
        close(mi_tuberia[1]);
        read(mi_tuberia[0], &numeroRecibidoPorPadre, sizeof(numeroRecibidoPorPadre));
        close(mi_tuberia[0]);

        printf("El numero que dio el hijo al padre es: %d \n", numeroRecibidoPorPadre);
        wait(NULL);
    }

    return 0;
}