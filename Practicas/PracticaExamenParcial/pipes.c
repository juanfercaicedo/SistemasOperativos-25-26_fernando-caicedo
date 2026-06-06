#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int mi_tuberia[2]; // declaramos la tuberia [0] para lectura [1] para escritura
    pid_t hijo;

    char mensajePadre[] = "Aprobado con 10!";
    char bufferHijo[50]; // hijo guarda lo que lee de padre

    pipe(mi_tuberia);
    
    hijo = fork();

    if(hijo < 0) {
        perror("ERRORRRR!!!");
    } else if(hijo == 0) {
        close(mi_tuberia[1]);
        read(mi_tuberia[0], bufferHijo, sizeof(bufferHijo));
        printf("[EL PROFESOR ME DIJO: %s]\n", bufferHijo);
        close(mi_tuberia[0]);
    } else {
        // --- PROCESO PADRE (Escritor) ---
        
        close(mi_tuberia[0]);
        
        // 2. Enviamos el mensaje por la tubería
        write(mi_tuberia[1], mensajePadre, sizeof(mensajePadre));
        
        close(mi_tuberia[1]);
        
        // 4. Esperamos a que el hijo termine para que no sea zombie
        wait(NULL); 
    }

    return 0;
}