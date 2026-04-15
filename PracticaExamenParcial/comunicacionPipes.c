/*
Objetivo: Manejar múltiples descriptores de archivos, lectura/escritura y paso de arrays entre procesos.
Enunciado:
Crea un programa con dos tuberías (pipe1 y pipe2) para lograr comunicación bidireccional.

El Padre: Genera un array de 5 números aleatorios usando srand() y rand() e imprime el array original. Envía este array al hijo a través de la primera tubería.

El Hijo: Lee el array, y ejecuta un algoritmo para invertir el orden de los números del array (el primero pasa a ser el último, etc.). Una vez invertido, envía el array de vuelta al padre por la segunda tubería. Termina su ejecución.

El Padre: Lee el array de la segunda tubería, hace un wait(NULL) para limpiar al hijo, e imprime el array resultante modificado.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>


int main(void) {
    pid_t hijo;
    int arrayAleatorio[5];
    int mi_tuberia1[2];
    int mi_tuberia2[2];

    srand(time(NULL));

    puts("Array aleatorio: ");
    for(int i = 0; i < 5; i++) {
        arrayAleatorio[i] = rand() % 100;
        printf("[%d]", arrayAleatorio[i]);
    }
    printf("\n");

    pipe(mi_tuberia1); // Padre
    pipe(mi_tuberia2); // Hijo


    hijo = fork();

    if(hijo < 0) {
        perror("Error durante el proceso del fork");
        exit(1);
    } else if(hijo == 0) {
        int arrayRecibido[5];

        close(mi_tuberia1[1]);
        close(mi_tuberia2[0]);

        read(mi_tuberia1[0], arrayRecibido, sizeof(arrayRecibido));

        int invertir;
        for(int i = 0; i < 5 / 2; i++){
            invertir = arrayRecibido[i];
            arrayRecibido[i] = arrayRecibido[4 - i];
            arrayRecibido[4 - i] = invertir;
        }

        write(mi_tuberia2[1], arrayRecibido, sizeof(arrayRecibido));
        close(mi_tuberia1[0]);
        close(mi_tuberia2[1]);

        exit(0);
    } else {
        int arrayFinal[5];
        close(mi_tuberia1[0]);
        close(mi_tuberia2[1]);

        write(mi_tuberia1[1], arrayAleatorio, sizeof(arrayAleatorio));
        read(mi_tuberia2[0], arrayFinal, sizeof(arrayFinal));

        wait(NULL);
        printf("El array final es: \n");
        for(int i = 0; i < 5; i++) {
            printf("[%d]", arrayFinal[i]);
        }

        close(mi_tuberia1[1]);
        close(mi_tuberia2[0]);
    }
    return 0;
}