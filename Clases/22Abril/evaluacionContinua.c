#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define NUM_HIJOS 4
#define ITERACIONES 100000

int main(void) {
    // Reservamos una memoria compartida
    int *memoria_compartida = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    //Inicializamos la memoria compartida a 0
    *memoria_compartida = 0;


    // Creamos a los procesos hijos
    for(int i = 0; i < NUM_HIJOS; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("Error al hacer fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            // Código del proceso hijo
            for (int j = 0; j < ITERACIONES; j++) {
                (*memoria_compartida)++; // Incremento de la memoria compartida
            }
            // Terminar el proceso enviando su número de identificación (1 al 4)
            exit(i);
        }
    }

//===============
// PROCESO PADRE
//===============
    int estado;
    pid_t pid_hijo;
    int orden_llegada = 1;

    // wait devuelve el PID del hijo terminado o -1 si ya no hay hijos
    while ((pid_hijo = wait(&estado)) > 0) {
        // Comprobar que el hijo terminó de forma normal
        if (WIFEXITED(estado)) {
            // Extraer el valor del exit
            int id_interno = WEXITSTATUS(estado);
            
            // Imprimir el orden de llegada y su PID
            printf("Hijo finalizado en posición %d: ID interno = %d, PID = %d\n", 
                   orden_llegada, id_interno, pid_hijo);
            orden_llegada++;
        }
    }

    // Paso 4: Mostrar el resultado del contador
    printf("\n--- Resultados del Contador ---\n");
    int valor_esperado = NUM_HIJOS * ITERACIONES;
    int valor_obtenido = *memoria_compartida;
    int incrementos_perdidos = valor_esperado - valor_obtenido;

    printf("Valor esperado:       %d\n", valor_esperado);
    printf("Valor obtenido:       %d\n", valor_obtenido);
    printf("Incrementos perdidos: %d\n", incrementos_perdidos);

    // Liberamos recursos compartidos
    if (munmap(memoria_compartida, sizeof(int)) == -1) {
        perror("Error al liberar la memoria con munmap");
        exit(EXIT_FAILURE);
    }

    return 0;
}