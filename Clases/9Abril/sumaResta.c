#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>

#define TAMAÑO 10000

int main(void) {
    pid_t hijo;
    sem_t *semaforo;
    semaforo = sem_open("/mi_semaforo", O_CREAT, S_IRUSR, | S_IWUSR, 1);
    
    int *sumas;

    sumas = mmap(NULL, sizeof(int) * 2, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,0);

    hijo = fork();

    if(hijo < 0) {
        perror("Error durante el proceso de craeción del fork");
        munmap(sumas, sizeof(int) * 2);
        exit(1);
    } else if (hijo == 0) {
        int resultadoHijo = 0;
        for(int i = 0; i < TAMAÑO; i ++){
            sem_wait(semaforo);
            resultadoHijo += i;
            sem_post(semaforo);
        }
        sumas[0] = resultadoHijo;

        exit(0);
    } else {
        int resultadoPadre = 0;
        for(int i = 0; i < TAMAÑO; i++) {
            sem_wait(semaforo);
            resultadoPadre -= i;
            sem_post(semaforo);

        }

        sumas[1] = resultadoPadre;
        wait(NULL);
        printf("Resultado guardado por el PADRE (resta): %d\n", sumas[1]);
        
        // Limpiamos la memoria compartida al terminar
        munmap(sumas, sizeof(int) * 2);
    }
    return 0;
}