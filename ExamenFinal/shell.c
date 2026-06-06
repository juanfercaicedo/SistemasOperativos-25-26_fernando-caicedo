#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

# define VERSION 1.0

int main(void) {
    pid_t hijo;
    char comando[20];
    printf("Bienvenido a JF-Shell %0.2f. Introduzca un comando para ejecutar \n", VERSION);
    scanf("%19s", comando);

    while(strcmp(comando, "salir") != 0) {
        hijo = fork();
        if(hijo == 0) {
            char otraCadena[50] = "/bin/";
            strcat(otraCadena, comando);

            execl(otraCadena, comando, NULL);
            printf("Comando no reconocido \n");

            exit(1);
        } else if(hijo > 0) {
            wait(NULL); // El padre espera a que el hijo termine
            
            // Volvemos a pedir el comando para que el bucle continúe
            printf("Introduzca un comando para ejecutar:\n");
            scanf("%19s", comando);
        }

    }
    printf("Saliendo de JF-Shell");
    return 0;
}