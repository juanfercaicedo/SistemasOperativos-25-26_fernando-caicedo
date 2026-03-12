/*
- Define un array de 10 números enteros y un "número objetivo" a buscar
- El proceso principal (Padre) debe crear dos procesos hijos utilizando la llamada al sistema fork()
- El Hijo 1 deberá buscar el número objetivo en la primera mital del array
- Si lo encuentra, terminará su ejecución devolviendo un estado de fracaso (exit(0))
- El hijo 2 deberá hacer lo mismo, pero buscando en la segunda mitad del array
- El proceso padre debe usar la llamada al sistema wait() para esperar obligatoriamente a que ambos hijos terminen
- El padre debe inspeccionar el estado de salida de cada hijo utilizando las macors adecuadas (WIFEXITED y WEXITSTATUS)
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>

int main(void){
    int arrayNumeros[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    printf("Introduce el número objetivo que quieres buscar: ");
    int numeroObjetivo;
    scanf("%d", &numeroObjetivo);

    pid_t hijo1, hijo2;

    hijo1 = fork();
    if(hijo1 == 0){ // proceso hijo 1
        for(int i = 0; i < 5; i++){
            if(arrayNumeros[i] == numeroObjetivo){
                printf("El hijo 1 tiene el número objetivo: %d", numeroObjetivo);
                exit(0);
            }
        }
        exit(1);
    }

    hijo2 = fork();
    if(hijo2 == 0){
        for(int i = 5; i < 10; i++){
            if(arrayNumeros[i]==numeroObjetivo){
                printf("El hijo 2 tiene el número objetivo: %d", numeroObjetivo);
                exit(0);
            }
        }
        exit(1);
    }
    return 0;
}