/*
El programa reservará espacio en memoria compartida para un número entero (el saldo de una cuenta).

El padre inicializa la cuenta bancaria con $1000.

El padre crea al hijo (fork).

El hijo hace un retiro: debe restarle $200 a la cuenta y terminar (exit).

El padre debe esperar a que el hijo termine (wait). Luego, el padre hace un depósito: debe sumarle $500 a la cuenta bancaria.

Finalmente, el padre imprime el saldo total por pantalla y "destruye" la memoria compartida usando munmap().
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>


static int *memoriaParaEntero;

int main(void) {
    pid_t hijo;
    memoriaParaEntero = mmap(NULL, sizeof(*memoriaParaEntero), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *memoriaParaEntero = 1000;

    hijo = fork();

    if(hijo < 0) {
        perror("ERROR EN LA CREACION DEL FORK :( ");
        exit(0);
    } else if(hijo == 0) {
        *memoriaParaEntero -= 500;
        exit(0);
    } else {
        wait(NULL);
        *memoriaParaEntero += 200;
        printf("El saldo final de la cuenta es: %d\n", *memoriaParaEntero);
        munmap(memoriaParaEntero, sizeof(*memoriaParaEntero));
    }

    return 0;
}  