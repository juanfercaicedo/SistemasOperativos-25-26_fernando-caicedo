/*
El padre pide un número al usuario. El hijo evalúa si es par o impar: si es par hace exit(0), si es impar hace exit(1). 
El padre usa WIFEXITED + WEXITSTATUS para leer el resultado e imprime "el número es PAR" o "el número es IMPAR".
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>

int main(void){
    int valorUsuario;
    pid_t hijo;
    int estadoHijo;
    puts("Introduce un número para determinar si es par o impar: ");
    scanf("%d", &valorUsuario);

    hijo = fork();

    if(hijo < 0) {
        perror("Error en la creación del fork");
        return 0;
    } else if(hijo == 0) {
        if(valorUsuario % 2 == 0){
            exit(0);
        } else {
            exit(1);
        }
    } else {
        wait(&estadoHijo);
        if (WIFEXITED(estadoHijo)) {
            // Extraemos el valor del exit (0 o 1)
            int resultado = WEXITSTATUS(estadoHijo);

            if (resultado == 0) {
                printf("El padre dice: el número %d es PAR.\n", valorUsuario);
            } else {
                printf("El padre dice: el número %d es IMPAR.\n", valorUsuario);
            }
        }
    }
    return 0;
}