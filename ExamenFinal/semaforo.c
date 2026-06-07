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

int static *variable_compartida;

int main(void) {
    sem_t *semaforo = sem_open("/mi_semaforo", O_CREAT, S_IRUSR | S_IWUSR, 0);
    variable_compartida = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,0);
    pid_t lee, escribe;
    int numeroUsuario = 0;

    lee = fork();

    if(lee < 0) {
        perror("Error durante el proceso del fork()");
        munmap(variable_compartida, sizeof(int));
        return(EXIT_FAILURE);
    } else if (lee == 0) {
        puts("Ingresa un número por el teclado: ");
        scanf("%d", &numeroUsuario);
        *variable_compartida = numeroUsuario;
        sem_post(semaforo); // el semáforo esta en 0, por lo tanto con esto le añadimos una llave, nos aseguramos de que el programa lea primero lee antes que escribe
        exit(0);
    }

    escribe = fork();
    if(escribe < 0) {
        perror("Error durante el proceso del fork()");
        munmap(variable_compartida, sizeof(int));
        exit(EXIT_FAILURE);
    } else if(escribe == 0) {
        sem_wait(semaforo);
        printf("El número obtenido durante la lectura es: %d \n", *variable_compartida);
        puts("Introduce cualquier tecla para terminar el proceso: ");
        getchar();
        getchar();
        exit(0);
    }
    // Padre espera a que ambos hijos acaben
    wait(NULL); 
    wait(NULL);
    munmap(variable_compartida, sizeof(int));

    sem_close(semaforo);
    sem_unlink("/mi_semaforo");
    return 0;
}