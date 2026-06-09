/*
Implementar un programa en C que genere números aleatorios en un proceso principal y delegue el cálculo intensivo de sus factoriales a un proceso hijo, el cual deberá paralelizar la tarea mediante hilos.
Requisitos técnicos:
Inicialización:
El proceso padre debe generar un array de N números enteros aleatorios (entre 1 y 20).
Debe mostrar por pantalla los números generados.
Arquitectura de Procesos (IPC):
El proceso padre debe crear una tubería (pipe) para la comunicación.
Realizar un fork() para crear un proceso hijo encargado del cálculo.
Arquitectura de Hilos (Multithreading):
Una vez creado el proceso hijo, este debe crear dos hilos de ejecución:
procesar_pares: Se encargará de calcular el factorial de los números situados en los índices pares (0, 2, 4...) del array.
procesar_impares: Se encargará de calcular el factorial de los números situados en los índices impares (1, 3, 5...) del array.
Los hilos deben escribir el resultado en un array global compartido factoriales.
Se debe utilizar un Mutex para garantizar la exclusión mutua al escribir en el array global factoriales.
Comunicación y Resultados:
El proceso hijo debe esperar a que ambos hilos terminen (join) y enviar el array factoriales completo al proceso padre a través de la tubería creada.
El proceso padre debe esperar a que el hijo finalice (wait), leer los datos de la tubería e imprimir los resultados finales formateados como: "Número: X, Factorial: Y".
*/

#include <stdio.h>    // Para printf, perror
#include <stdlib.h>   // Para exit, rand, srand
#include <unistd.h>   // Para fork, pipe, close, read, write, sleep
#include <pthread.h>  // Para funciones pthread_*
#include <sys/types.h>// Para tipos de datos como pid_t
#include <sys/wait.h> // Para la función wait()
#include <time.h>     // Para time(NULL)

#define MAX_N 20

int datos[MAX_N];
int numerosAleatorios;

pthread_t procesar_pares, procesar_impares;

pthread_mutex_t lock;

int factoriales[MAX_N];

void *numerosPares(void *arg) {
long resultado = 1;
        // Calculamos el factorial de datos[i]
        for (int i = 1; i <= datos[i]; i++) {
            resultado = resultado * i;
            // ¡ZONA CRÍTICA! Guardamos en el array global compartido
            pthread_mutex_lock(&lock);
            factoriales[i] = resultado;
            pthread_mutex_unlock(&lock);
        }
       return NULL;
}


void *numerosImpares(void *arg) {
for (int i = 1; i < numerosAleatorios; i += 2) {
        
        long resultado = 1;
        
        // Calculamos el factorial del número en esa posición
        for (int j = 1; j <= datos[i]; j++) {
            resultado = resultado * j;
        }

        // ¡ZONA CRÍTICA! Guardamos en el array global compartido
        pthread_mutex_lock(&lock);
        factoriales[i] = resultado;
        pthread_mutex_unlock(&lock);
    }
    
    return NULL;
}

int main(void) {
   
    int tuberia[2];
    pipe(tuberia);
 
    pid_t hijo;
    
    srand(time(NULL));
    numerosAleatorios = (rand() % 20) + 1;
    printf("Padre: Generando array de %d números aleatorios...\n", numerosAleatorios);
    printf("Array: [ ");
    for (int i = 0; i < numerosAleatorios; i++) {
        datos[i] = rand() % 100; 
        printf("%d ", datos[i]);
    }
    printf("]\n");
    hijo = fork();

    if(hijo < 0) {
        perror("Error durante el fork()");
        exit(EXIT_FAILURE);
    } else if (hijo == 0) {
        close(tuberia[0]);
        pthread_mutex_init(&lock, NULL);

        pthread_create(&procesar_pares, NULL, numerosPares, NULL);
        pthread_create(&procesar_impares, NULL, numerosImpares, NULL);

        pthread_join(procesar_pares, NULL);
        pthread_join(procesar_impares, NULL);

        write(tuberia[1], factoriales, sizeof(long) * numerosAleatorios);

        pthread_mutex_destroy(&lock);

        exit(0);
    } else {
        close(tuberia[1]);
        wait(NULL);

        read(tuberia[1], factoriales, sizeof(long) * numerosAleatorios);

        for (int i = 0; i < numerosAleatorios; i++) {
            printf("Número: %d | Factorial: %d\n", datos[i], factoriales[i]);
        }        
    
    close(tuberia[0]);
    }
    return 0;
}

