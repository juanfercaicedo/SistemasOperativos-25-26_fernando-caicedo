/*
Tenemos dos procesos al menos uno con la variable compartida, el padre apenas crea al hijo el padre lee un número. Cuando el padre lee el número el hijo va a calcular su 
factorial y el padre una vez que el hijo a terminado de calcular el factorial, saca el valor de ese factorial por pantalla
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>

static long *memoria_compartida;

int main(void) {
    int numeroUsuario;
    int resultado;
    memoria_compartida = mmap(NULL, sizeof(*memoria_compartida), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    puts("Introduce un número para calcular su factorial");
    scanf("%d", &numeroUsuario);

    pid_t hijo;

    hijo = fork();

    if(hijo < 0) {
        perror("Error durante el fork()");
        exit(EXIT_FAILURE);
    } else if (hijo == 0) {
        long factorial = 1;
        for(int i = 1; i <= numeroUsuario; i++) {
            factorial = factorial * i;
        }
        *memoria_compartida = factorial;
        exit(EXIT_SUCCESS);
    } else {
        wait(NULL);

        printf("El factorial de: %d es: %ld \n", numeroUsuario, *memoria_compartida);
        munmap(memoria_compartida, sizeof(memoria_compartida));
    }

    return 0;
}