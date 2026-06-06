/*
Suma paralela de un array usando memoria compartida
Implenta un programa en c que calcule, de forma colaborativa entre un proceso padre y un proceso hijo, la suma de todos los elementos de un array de enteros. El array
tendrá N elementos (con N par). 
Cada proceso calculará la suma de su mital del array y escribirá los resultados en una zona de memoria compartida. 
Al final, el proceso padre leerá ambos resultados y mostrará la suma total

PASOS / REQUISITOS
1. Reservar la zona de memoria compartida antes de llamar al fork
2. La zona compartida debe contener un array de dos enteros: sumas[0] para el padre y sumas[1] para el hijo
3. El proceso hijo calculará la suma de la mitad superior del array y la guardará en sumas [1]
Después terminará con exit(0)

4. El proceso padre calculará la suma de la mitad inferior, la guardará en sumas[0] y esperará al hijo con wait() antes de leer sumas[1]
5. Liberar la memoria con munmap() al terminar
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>

#define N 10 // Cantidad de elementos(debe ser par)

int main(void) {
    int datos[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int *sumas;
    pid_t hijo;

    sumas = mmap(NULL, sizeof(int) * 2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,0);

    if (sumas == MAP_FAILED) {
        perror("Error al reservar memoria compartida");
        exit(EXIT_FAILURE);
    }

    hijo = fork();

    if(hijo < 0) {
        perror("Error en la creación del fork");
        munmap(sumas, sizeof(int) * 2); // Liempiza básica en C
        exit(EXIT_FAILURE);
    } else if(hijo == 0) { // proceso hijo
       int sumaPrimeraMitad = 0;
       int primeraMitad = N / 2;

       for(int i = primeraMitad; i < N; i++) {
            sumaPrimeraMitad += datos[i];
       }

        sumas[1] = sumaPrimeraMitad;

        exit(0);
    } else { // proceso padre
        int sumaSegundaMitad = 0;
        int segundaMitad = N / 2;

        for(int i = 0; i < segundaMitad; i++) {
            sumaSegundaMitad += datos[i];
        }

        sumas[0] = sumaSegundaMitad;

        wait(NULL);
        int suma_total = sumas[0] + sumas[1];
        printf("Datos del array: ");
        for(int i=0; i<N; i++) printf("%d ", datos[i]);
        printf("\n\n");
        
        printf("Suma mitad inferior (Padre): %d\n", sumas[0]);
        printf("Suma mitad superior (Hijo):  %d\n", sumas[1]);
        printf("Suma TOTAL: %d\n", suma_total);
        
        // --- PASO 5: Liberar la memoria con munmap() ---
        if (munmap(sumas, 2 * sizeof(int)) == -1) {
            perror("Error al liberar memoria (munmap)");
            exit(EXIT_FAILURE);
        }
    }
    return 0; 
}