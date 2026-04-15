/*
El padre pide al usuario una palabra (máx. 20 caracteres). La envía al hijo por una tubería. 
El hijo la imprime por pantalla y termina con exit(0). El padre espera con wait(NULL) e imprime "Transmisión completada".
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

int main(void) {
    pid_t hijo;
    char palabraUsuario[SIZE];
    int mi_tuberia[2];


    puts("Introduce una palabra: ");
    scanf("%s", palabraUsuario);

    pipe(mi_tuberia);

    hijo = fork();

    if(hijo < 0) {
        perror("Error en la creación del fork");
        exit(1);
    } else if(hijo == 0) {
        char bufferHijo[SIZE];
        close(mi_tuberia[1]);
        read(mi_tuberia[0], bufferHijo, SIZE);
        close(mi_tuberia[0]);  
        printf("%s \n", bufferHijo);
        exit(0);
    } else {
        close(mi_tuberia[0]);
        write(mi_tuberia[1], palabraUsuario, strlen(palabraUsuario) + 1);
        close(mi_tuberia[1]);

        wait(NULL);
        puts("Proceso Completado");
    }
    return 0;
} 