#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>

#define VERSION 1.0

int main(void){
    char comando[20];
    pid_t hijo;

    // Corregido: "Introduzca"
    printf("Bienvenidos a JL-Shell %0.2f. Introduzca un comando para ejecutar: \n", VERSION);
    
    // Corregido: %s en lugar de %d para leer la palabra
    scanf("%19s", comando);

    // Bucle principal de la consola
    while(strcmp(comando, "salir") != 0){
        
        hijo = fork();
        
        if(hijo == 0){
            // --- PROCESO HIJO ---
            char cadena[50] = "/bin/";
            strcat(cadena, comando);
            // puts(cadena); // Descomenta esto para ver la ruta final (ej: /bin/ls)
            
            execl(cadena, comando, NULL);
            
            // Si llegamos aquí, el comando falló (no existe en /bin/)
            printf("Comando no reconocido.\n");
            exit(1); // Usamos exit(1) para matar al hijo con estado de error
            
        } else if(hijo > 0){
            // --- PROCESO PADRE ---
            wait(NULL); // El padre espera a que el hijo termine
            
            // Volvemos a pedir el comando para que el bucle continúe
            printf("Introduzca un comando para ejecutar:\n");
            scanf("%19s", comando);
        }
        
    } // AQUÍ es donde realmente se cierra el while

    printf("Saliendo de JL-Shell...\n");
    return 0;
}