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

int static *sumas;

int main(void) {
    int array[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    sumas = mmap(NULL, sizeof(int) * 2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,0);
    pid_t hijo;

    hijo = fork();

    if(hijo < 0) {
        perror("Error durante el fork() del hijo");
        munmap(sumas, sizeof(int) * 2);
        exit(EXIT_FAILURE);
    } else if(hijo == 0) {
        int resultado = 0;
        for (int i = N / 2; i < N; i++) {
            resultado += array[i];
        }

        sumas[1] = resultado;
        exit(0);
    } else {
        int resultadoPadre = 0;
        // Suma parte inferior del array
        for(int i = 0; i < N / 2; i++){
            resultadoPadre += array[i];
        }
        sumas[0] = resultadoPadre;
        
        wait(NULL);

        int resultadoSuma = sumas[0] + sumas[1];
        
        printf("Resultado de la primera mitad: %d \n", sumas[0]);
        printf("Resultado de la segunda mitad: %d \n", sumas[1]);
        printf("El resulta de la suma del array es: %d \n", resultadoSuma);

        munmap(sumas, sizeof(int) * 2);
        return 0;
    }

}