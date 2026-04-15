/*
Creamos dos procesos, uno se llama lee y el otro escribe. (3 procesos, el padre y los otros dos mencioandos)
Tenemos una variable compartida que almacena un numero.
Se crea ambos procesos uno atras de otro. Una vez los dos estan creados, un preceso lee un numero por teclado.
Una vez que el proceso a leido el numero por teclado, el proceso escribe, accede a la memoria compartida y muestra el numero por pantalla.
Ese mismo proceso escribe muestra un mensaje que dice: Pulsa una tecla para finalizar(Espera a que pulsemos una tecla para que muera).
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>

static int *variable_compartida;

int main(void) {
    int numeroUsuario;
    pid_t lee, escribe;
    sem_t *semaforo;
    semaforo = sem_open("/mi_semaforo", O_CREAT, S_IRUSR | S_IWUSR, 0);
    variable_compartida = mmap(NULL, sizeof(*variable_compartida), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,0);
    
    lee = fork();

    if(lee < 0) {
        perror("error en el fork");
        exit(1);
    } else if(lee == 0) {
        puts("Introduce un número: ");
        scanf("%d", &numeroUsuario);
        *variable_compartida = numeroUsuario;

        sem_post(semaforo); // desbloquea sem_wait(semaforo);

        exit(0);
    } else {
        escribe = fork();

        if(escribe < 0) {
            perror("Error en el fork");
            exit(1);
        } else if (escribe == 0) {
            sem_wait(semaforo); // permite que el proceso escribir se ejecute por el valor de semaforo = 0
            printf("El número introducido es: %d\n", *variable_compartida);
            printf("Pulsa una tecla para finalizar...");
            getchar();
            exit(0);
        }

        // Esperamos a que los dos hijos acaben
        wait(NULL);
        wait(NULL);
        munmap(variable_compartida, sizeof(*variable_compartida));

        sem_close(semaforo);
    }
    return 0;
}