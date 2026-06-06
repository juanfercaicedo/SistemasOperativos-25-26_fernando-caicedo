#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>

int main(void) {
    int estado;
    puts("Introduce un número");
    int x;
    scanf("%d", &x);
    pid_t hijo;
    printf("Hola soy el proceso padre y tengo el id: %d y voy a crear a mi hijo \n", getpid());

    hijo = fork();
    if(hijo < 0) {
        perror("Error en el proceso del fork");
        exit(EXIT_FAILURE);
    } else if(hijo == 0) {
        printf("Hola soy el hijo y tengo un ID: %d, y vamos a ver si el número %d es par o impar \n", getpid(), x);
        if(x % 2 == 0) {
            exit(0);
        } else {
            exit(1);
        }
    } else {
        printf("Soy el padre con un PID: %d y estoy esperando a que mi hijo con un PID: %d termine\n", getpid(), (int)hijo);
        wait(&estado);
        if(WIFEXITED(estado)) {
            int resultadoHijo = WEXITSTATUS(estado);
            if(resultadoHijo == 0) {
                puts("El número es PAR \n");
            } else {
                puts("El número es IMPAR \n");
            }
        } else {
            puts("El hijo ha acabado de manera anomala \n");
        }
    }
    return 0;
}