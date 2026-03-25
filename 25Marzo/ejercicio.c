/*
Objetivo: Escribir un programa en C que utilice dos procesos (Padre e Hijo) comunicados de
forma bidireccional
utilizando dos pipes. Además, el Padre deberá evaluar cómo terminó el Hijo usando las macros del sistema.

Instrucciones:
El proceso Padre debe crear dos tuberías (pipel y pipe2) y luego generar un proceso Hijo usando fork() •
El Padre generará un array de 10 números enteros y se lo enviará al Hijo a través de la primera tubería.
Hijo deberá leer estos números, calcular la suma total de todos los elementos y, simultáneamente, contar cuántos
esos números son pares.
El Hijo enviará el resultado de la suma total de vuelta al Padre a través de la segunda tubería.
El Hijo terminará su ejecución usando exit (cantidad_de_pares). ).
El Padre leerá la suma calculada por el Hijo. Luego, usará wait()
para esperar a que el Hijo termine.
macros WIFEXITED (status) y WEXITSTATUS (status), el Padre debe verificar que el Hijo terminó de
forma normal y extraer
el numero de valores pares que el Hijo procesó, imprimiendo ambos resultados por pantalla
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <time.h>

#define SIZE 10

int main(void) {
    int pipe1[2];
    int pipe2[2];
    pid_t hijo;
    int status;

    hijo = fork();

    if (hijo == 0) { 
      
        close(pipe1[1]); 
        close(pipe2[0]); 

        int arrayRecibido[SIZE];
        int sumaTotal = 0;
        int cantidadPares = 0;

        read(pipe1[0], arrayRecibido, sizeof(arrayRecibido));
        close(pipe1[0]); 

        for (int i = 0; i < SIZE; i++) {
            sumaTotal += arrayRecibido[i];
            if (arrayRecibido[i] % 2 == 0) {
                cantidadPares++;
            }
        }

        write(pipe2[1], &sumaTotal, sizeof(sumaTotal));
        close(pipe2[1]); 

        exit(cantidadPares);

    } else { 

        close(pipe1[0]); 
        close(pipe2[1]); 

        int arrayPadre[SIZE];
        int sumaHijo;

        srand(time(NULL));

        printf("Padre: Generando array de %d números aleatorios...\n", SIZE);
        printf("Array: [ ");
        for (int i = 0; i < SIZE; i++) {
            arrayPadre[i] = rand() % 100; 
            printf("%d ", arrayPadre[i]);
        }
        printf("]\n");

        write(pipe1[1], arrayPadre, sizeof(arrayPadre));
        close(pipe1[1]); 

        read(pipe2[0], &sumaHijo, sizeof(sumaHijo));
        close(pipe2[0]);

        wait(&status);

        if (WIFEXITED(status)) {
            int paresProcesados = WEXITSTATUS(status);
            
            printf("\n--- RESULTADOS ---\n");
            printf("Padre: La suma total calculada por el Hijo es: %d\n", sumaHijo);
            printf("Padre: El Hijo procesó un total de %d números pares.\n", paresProcesados);
        } else {
            printf("\nPadre: El proceso hijo no terminó de forma normal.\n");
        }
    }

    return 0;
}