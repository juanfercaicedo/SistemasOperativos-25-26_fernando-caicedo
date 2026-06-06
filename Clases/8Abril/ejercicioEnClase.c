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

int main(void){
    pid_t hijo;
    int numeroUsuario;
    puts("Introduce un número entero");
    scanf("%d", &numeroUsuario);
    
    // mmap siempre va antes del fork
    memoria_compartida = mmap(NULL, sizeof(*memoria_compartida), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    
    *memoria_compartida = (long)numeroUsuario;
    
    hijo = fork();
    
    if (hijo < 0) {
        perror("Error en fork");
        return 1;
    }
    
    if(hijo == 0) { // proceso hijo
        usleep(2);
        
        long n = *memoria_compartida;
        long unsigned int factorial = 1;
        while(*memoria_compartida == 0) {
            usleep(2);
        }
        
        for(int i = 1; i <= n; i++){
            factorial = factorial * i;
        }
        
        *memoria_compartida = factorial;
        exit(0);
    } else if (hijo > 0) { // proceso padre
        wait(NULL);
        printf("El hijo ha terminado. El factorial de %d es %ld \n", numeroUsuario, *memoria_compartida);
    }

    munmap(memoria_compartida, sizeof(int));

    return 0;
}