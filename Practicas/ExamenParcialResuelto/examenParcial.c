#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define NUMERO_HIJOS 4
#define INCREMENTOS 100000

int main(void) {
    int *contador = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *contador = 0;

    pid_t hijos[NUMERO_HIJOS];

    for(int i = 0; i < NUMERO_HIJOS; i++) {
        hijos[i] = fork();
        if(hijos[i] < 0) {
            perror("Error durante el fork()");
            munmap(contador, sizeof(int));
            exit(0);
        } else if (hijos[i] == 0){
            for(int j = 0; j < INCREMENTOS; j++) {
                *contador += 1;
            }
            exit(i + 1);
        }
    }
    // PROCESO PADRE
    int ordenLlegada = 1;
    int resultadoHijo;
    int estado;
    for(int i = 0; i < NUMERO_HIJOS; i++) {
        int idHijo = wait(&estado);
        if(WIFEXITED(estado)) {
            resultadoHijo = WEXITSTATUS(estado);
            ordenLlegada++;
            printf("Ha llegado el hijo %d, su resultado es: %d y llegó en la posición %d\n", idHijo, resultadoHijo, ordenLlegada);
        }
    }
    int resultadoEsperado = NUMERO_HIJOS * INCREMENTOS;
    int resultadoObtenido = *contador;
    int diferenciaResultado = resultadoEsperado - resultadoObtenido;

    printf("El valor esperado era: %d\n", resultadoEsperado);
    printf("El valor obtenido por los hijos fue: %d\n", resultadoObtenido);
    printf("La diferencia del resultado es: %d\n", diferenciaResultado);

    munmap(contador, sizeof(int));

    return 0;
}