#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>  
#include <sys/wait.h>

#define NUM_HIJOS    4
#define INCREMENTOS  100000

int main(void) {
    int *contador = mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE,MAP_SHARED | MAP_ANONYMOUS, -1,0);
    *contador = 0;
    int estadoHijos;
    pid_t hijos[NUM_HIJOS];
    for(int i = 0; i < NUM_HIJOS; i++) {
        hijos[i] = fork();
        if(hijos[i] < 0) {
            perror("Error durante el fork()");
            munmap(contador, sizeof(int));
            exit(EXIT_FAILURE);
        } else if(hijos[i] == 0) {
            for (int j = 0; j < INCREMENTOS; j++) {
                *contador += 1;
            }
            exit(i + 1);
        } 
    }
    // === PROCESO PADRE === 
    int ordenLlegada = 1;
    for(int i = 0; i < NUM_HIJOS; i++) {
        int id_hijo = wait(&estadoHijos);
        if(WIFEXITED(estadoHijos)){
            int num_hijo = WEXITSTATUS(estadoHijos);
            ordenLlegada++;
            // IMPRIMOS LOS RESULTADOS
            printf("El hijo %d, llegó en la posición %d y tiene un pid: %d y tiene el valor de contador: %d\n", num_hijo, ordenLlegada, id_hijo, *contador);
        }
    }

    // === RESULTADOS ESPERADOS ===
    int resultadoEsperado = NUM_HIJOS * INCREMENTOS;
    int valorObtenido = *contador;
    int diferenciaValor = resultadoEsperado - valorObtenido;

    printf("El valor esperado es: %d\n", resultadoEsperado);
    printf("El valor obtenido es: %d \n", valorObtenido);
    printf("La diferencia con el valor esperado es: %d\n", diferenciaValor);
}
