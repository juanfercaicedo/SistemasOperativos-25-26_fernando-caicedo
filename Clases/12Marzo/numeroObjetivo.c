#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>
#define SIZE = 10

int main(void){
#define SIZE = 10;
    int arrayNumeros[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int numeroObjetivo;
    
    printf("Introduce el número objetivo que quieres buscar: ");
    scanf("%d", &numeroObjetivo);

    pid_t hijo1, hijo2;

    // --- CREACIÓN DEL HIJO 1 ---
    hijo1 = fork();
    if(hijo1 == 0){ // Proceso hijo 1
        for(int i = 0; i < SIZE / 2; i++){
            if(arrayNumeros[i] == numeroObjetivo){
                printf("El hijo 1 tiene el número objetivo: %d\n", numeroObjetivo);
                exit(0); // 0 indica que lo encontró
            }
        }
        exit(1); // 1 indica que no lo encontró
    }

    // --- CREACIÓN DEL HIJO 2 ---
    hijo2 = fork();
    if(hijo2 == 0){ // Proceso hijo 2
        for(int i = SIZE / 2; i < SIZE; i++){
            if(arrayNumeros[i] == numeroObjetivo){
                printf("El hijo 2 tiene el número objetivo: %d\n", numeroObjetivo);
                exit(0); // 0 indica que lo encontró
            }
        }
        exit(1); // 1 indica que no lo encontró
    }

    // --- PROCESO PADRE ---
    int estado;
    int encontrado = 0; // Variable bandera

    // Como hay dos hijos, el padre debe llamar a wait() dos veces
    for(int i = 0; i < 2; i++) {
        wait(&estado); // El padre se bloquea hasta que un hijo termine
        
        // Inspeccionamos el estado de salida
        if(WIFEXITED(estado)) {
            // WEXITSTATUS nos da el número que el hijo puso dentro de su exit()
            if(WEXITSTATUS(estado) == 0) {
                encontrado = 1; 
            }
        }
    }

    // Resultado final enviado por el padre
    printf("\n---Resultado Final---\n");
    if(encontrado){
        printf("El número objetivo %d fue encontrado en uno de los hijos.\n", numeroObjetivo);
    } else {
        printf("El número objetivo %d no fue encontrado en ninguno de los hijos.\n", numeroObjetivo);
    }

    return 0;
}