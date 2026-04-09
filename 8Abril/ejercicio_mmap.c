/*
Comunicación entre procesos con memoria compartida anónima (mmap)
El hijo calcula los 10 primeros números de Fibonacci y los escribe
en la memoria compartida. El padre los lee tras esperar al hijo y los
saca por pantalla
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>

#define N 10 // Cantidad de números de la secuencia de Fibonacci a calcular

static int *memoria_compartida;

int main(void) {
    pid_t hijo;
    
    // 1. Mapear la memoria compartida anónima
    // PROT_READ | PROT_WRITE: Permisos de lectura y escritura
    // MAP_SHARED: Visible para otros procesos
    // MAP_ANONYMOUS: No está respaldada por un archivo (memoria RAM)
    memoria_compartida = mmap(NULL, sizeof(int) * N, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    // Comprobar si hubo un error al reservar la memoria
    if (memoria_compartida == MAP_FAILED) {
        perror("Error en mmap");
        exit(EXIT_FAILURE);
    }

    // 2. Crear el proceso hijo
    hijo = fork();

    if (hijo < 0) {
        // Error al crear el proceso
        perror("Error en fork");
        munmap(memoria_compartida, sizeof(int) * N); // Liempiza básica en C
        exit(EXIT_FAILURE);
        
    } else if (hijo == 0) {
        // --- CÓDIGO DEL PROCESO HIJO ---
        
        // Calculamos la secuencia de Fibonacci y la guardamos en la memoria compartida
        if (N > 0) memoria_compartida[0] = 0; // Primer número
        if (N > 1) memoria_compartida[1] = 1; // Segundo número
        
        for (int i = 2; i < N; i++) {
            memoria_compartida[i] = memoria_compartida[i-1] + memoria_compartida[i-2];
        }
        
        // El hijo termina su ejecución con éxito
        exit(EXIT_SUCCESS);
        
    } else {
        // --- CÓDIGO DEL PROCESO PADRE ---
        
        // El padre espera a que el hijo termine su tarea
        wait(NULL);
        
        // Una vez que el hijo ha terminado, el padre lee de la memoria
        printf("Secuencia de Fibonacci calculada por el hijo (%d números):\n", N);
        for (int i = 0; i < N; i++) {
            printf("%d ", memoria_compartida[i]);
        }
        printf("\n");
        
        // 3. Liberar la memoria compartida (limpieza)
        if (munmap(memoria_compartida, sizeof(int) * N) == -1) {
            perror("Error en munmap");
            exit(EXIT_FAILURE);
        }
    }

    return 0;
}