#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>

int main(void){
    int n1, n2;
    pid_t suma, resta;

    printf("Introduce un número: ");
    scanf("%d", &n1);
    printf("Ahora introduce otro número: ");
    scanf("%d", &n2);

    suma = fork();
    
    if(suma > 0){
        resta = fork();
    }

    if(suma == 0){
        int resultado = n1 + n2;
        printf("La suma de los dos números es %d\n", resultado);
        exit(1); // finaliza el proceso entero
    }else if(resta == 0){
        int res2 = n1 - n2;
        printf("La resta de los dos números es de %d\n", res2);
        exit(1); // finaliza el proceso entero
    }else if(suma > 0 && resta > 0){
        while(wait(NULL)>0); // se queda a la espera de los dos procesos
        puts("Soy el padre y finalizo mi ejecución");
    }else{
        perror("Alguna mierda de error se ha producido");
    }

    return 0;
}