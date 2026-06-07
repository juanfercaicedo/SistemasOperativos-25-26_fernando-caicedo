#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>

int main(void) {
    int x, y;
    int tuberia1[2]; // Padre manda numeros a hijo
    int tuberia2[2]; // Hijo envia el resultado a padre
    pid_t hijo;

    pipe(tuberia1);
    pipe(tuberia2);

    hijo = fork();
    if(hijo < 0) {
        perror("Error en el fork()");
        exit(EXIT_FAILURE);
    } else if(hijo == 0) {
        int numerosRecibidos[2];
        int resultado;
        close(tuberia1[1]);
        read(tuberia1[0], numerosRecibidos, sizeof(numerosRecibidos));

        resultado = numerosRecibidos[0] + numerosRecibidos[1]; 

        close(tuberia2[0]);
        write(tuberia2[1], &resultado, sizeof(int));

        close(tuberia1[0]);
        close(tuberia2[1]);
    } else {
        int numerosUsuarios[2];
        int resultadoHijo = 0;

        puts("Introduzca un número para sumar: ");
        scanf("%d", &numerosUsuarios[0]);
        puts("Ahora introduce otro: ");
        scanf("%d", &numerosUsuarios[1]);

        // Mandamos el resultado al hijo
        close(tuberia1[0]);
        write(tuberia1[1], numerosUsuarios, sizeof(numerosUsuarios));

        // Recibimos el resultado del hijo
        close(tuberia2[1]);
        read(tuberia2[0], &resultadoHijo, sizeof(int));

        printf("El resultado de la suma es de: %d\n ", resultadoHijo);

        close (tuberia1[1]);
        close (tuberia2[0]);

        wait(NULL);
    }
}