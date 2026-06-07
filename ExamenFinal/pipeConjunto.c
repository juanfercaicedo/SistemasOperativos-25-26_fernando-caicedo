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
    int tuberia1[2]; // Tuberia padre, enviara los numeros al hijo
    int tuberia2[2]; // Tuberia del hijo, enviara los resultados al padre

    pipe(tuberia1);
    pipe(tuberia2);

    pid_t hijo;

    hijo = fork();
    if(hijo < 0) {
        perror("Error durante el fork()");
        exit(EXIT_FAILURE);
    } else if (hijo == 0) { // Proceso hijo
        // 1. Tiene que leer el conjunto de números que va a recibir del padre
        int numerosRecibidos[SIZE];
        close(tuberia1[1]);
        close(tuberia2[0]);
        read(tuberia1[0], &numerosRecibidos, SIZE * sizeof(int));

        // 2. Hacemos la suma de los números
        int resultado = 0;
        for (int i = 0; i < SIZE; i++) {
            resultado += numerosRecibidos[i];
        }

        // 3. Contamos los números pares
        int cantidad_de_pares = 0;
        for(int i = 0; i < SIZE; i++) {
            if(numerosRecibidos[i] % 2 == 0){
                cantidad_de_pares++;
            }
        }
        // 4. Enviamos la suma de los elementos del array al padre
        write(tuberia2[1], &resultado, sizeof(int));
        close(tuberia1[0]);
        close(tuberia2[1]);
        // El hijo muere dando la cantidad de números pares que encontró dentro del array
        exit(cantidad_de_pares);
    } else { // Proceso Padre
        int estado;
        int arrayAleatorio[SIZE];
        // 1. Creamos el array de 10 elemenos con números aleatorios
        srand(time(NULL));

        for (int i = 0; i < SIZE; i++) {
        arrayAleatorio[i] = rand() % 100;
        }
        // 2. Imprimimos el array en pantalla
        puts("El array generado es: ");
        for(int i = 0; i < SIZE; i++) {
            printf("%d. %d \n", i + 1, arrayAleatorio[i]);
        }

        // 3. Mandamos el array aleatorio al hijo
        close(tuberia1[0]);
        write(tuberia1[1], arrayAleatorio, SIZE * sizeof(int));

        // 4. Recibe el resultado de la suma del hijo
        int resultadoHijo;
        close(tuberia2[1]);
        read(tuberia2[0], &resultadoHijo, sizeof(int));

        printf("La suma de números del array es: %d \n", resultadoHijo);
        
        close(tuberia1[1]);
        close(tuberia2[0]);
        // 5. Recibimos la cantidad pares de números
        int cantidadNumerosPares = 0;
        wait(&estado);
        if(WIFEXITED(estado)) {
            cantidadNumerosPares = WEXITSTATUS(estado);
        }

        printf("Hay %d de números pares dentro del array aleatorio \n", cantidadNumerosPares);
        return 0;
    }
}