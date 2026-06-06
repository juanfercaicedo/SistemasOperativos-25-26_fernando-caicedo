/* Papa lee por teclado dos numeros, pasa por la tuberia los números al hijo y los suma*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>

int main(void){
    int numeros[2];
    int miTuberia[2];
    pid_t hijo;

    pipe(miTuberia);
    hijo = fork();

    if(hijo == 0){
        int numerosRecibidos[2];
        close(miTuberia[1]); // 1 ocupamos para escribir, por lo tanto el hijo no lo debe ocupar por lo tanto lo cerramos para el hijo

        read(miTuberia[0], numerosRecibidos, sizeof(numerosRecibidos));
        int suma = numerosRecibidos[0] + numerosRecibidos[1];

        printf("La suma de %d + %d es de: %d \n", numerosRecibidos[0], numerosRecibidos[1], suma);
        close(miTuberia[0]);
        exit(0);
    } else{
        // --- MENSAJE DEL PADRE---
        puts("Introduce un número"); 
        scanf("%d", &numeros[0]);
        puts("Ahora introduce otro número: ");
        scanf("%d", &numeros[1]);
        write(miTuberia[1], numeros, sizeof(numeros));
        
        close(miTuberia[1]);
        wait(NULL);
    }
    return 0;
}