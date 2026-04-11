/*
El padre le pedirá al usuario un número pequeño (del 1 al 10) por teclado.

El padre enviará ese número al hijo a través de una tubería.

El hijo leerá el número de la tubería y le sumará 15.

El hijo enviará ese resultado final de vuelta al padre a través de su exit() (su última voluntad).

El padre esperará a que el hijo muera, usará sus "lupas" (WIFEXITED y WEXITSTATUS) para leer el resultado, y lo imprimirá por pantalla.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    pid_t hijo;
    int numeroPedidoPorPadre;
    int resultadoHijo;
    int estadoHijo;
    int mi_tuberia[2];

    printf("Introduce un numero del [0 - 10]: ");
    scanf("%d", &numeroPedidoPorPadre);

    pipe(mi_tuberia);

    hijo = fork();

    if(hijo < 0) {
        perror("ERROR EN LA CREACION DEL FORK \n");
    } else if(hijo == 0) {
        close(mi_tuberia[1]);
        read(mi_tuberia[0], &resultadoHijo, sizeof(resultadoHijo));
        close(mi_tuberia[0]);

        resultadoHijo += 15;
        exit(resultadoHijo);
    } else {
        close(mi_tuberia[0]);
        write(mi_tuberia[1], &numeroPedidoPorPadre, sizeof(numeroPedidoPorPadre));
        close(mi_tuberia[1]);

        wait(&estadoHijo);

        if(WIFEXITED(estadoHijo)){
            int resultadoFinal = WEXITSTATUS(estadoHijo);
            printf("El resultado final es: %d \n", resultadoFinal);
        }
    }
}