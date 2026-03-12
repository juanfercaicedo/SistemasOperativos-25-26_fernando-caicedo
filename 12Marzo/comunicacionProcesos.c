#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>

int main(void){
    pid_t proceso;
    int status; // fuarda información de como ha finalizado el proceso hijo
    puts("Introduce un número cualquiera:");
    int numero;
    scanf("%d", &numero);
    
    printf("Soy el padre (PID: %d) y voy a crear al hijo\n", getpid());

    proceso = fork();
    if(proceso < 0){
        perror("Error en el fork");
        exit(EXIT_FAILURE);
    } else if(proceso == 0){ // proceso hijo
        printf("Hijo, PID: %d evaluando el número %d es par o impar\n", getpid(), numero);
        if(numero %2 == 0){
            // número par devolvemos 0
            exit(0);
        } else{
            // número impar devolvemos 1
            exit(1);
        }
    } else{
        printf("Padre, PID: %d. Esperando a que mi hijo con un PID: %d, termine su tarea \n", getpid(), proceso);
        wait(&status);
        if(WIFEXITED(status)){ // WIFEXITED cuando ha acabado de forma anormal devolverá falso e iremos al else, sabe si acabamos con exit o return
            int resultadoHijo = WEXITSTATUS(status);
            if(resultadoHijo == 0){
                puts("El hijo ha acabado, la variable es PAR");
            }else if(resultadoHijo == 1){
                puts("El hijo ha acabado, la variables es IMPAR");
            }else{
                puts("El hijo ha acabado, pero ha devuelto uun código desconocido");
            }
        }else{
            puts("Atención, el hijo ha terminado de manera anómala");
        }
    }
    return 0;
}