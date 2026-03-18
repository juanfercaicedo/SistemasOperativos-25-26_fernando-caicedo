#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>

int main(void){
    int mi_tuberia[2];

    pid_t hijo;
    char mensaje[] = "Hola proceso hijo! Misión cumplida";
    char buffer [100]; // buffer de memoria de 100 bytes
    pipe(mi_tuberia); // si devuelve -1 hay un error

    hijo = fork(); // si queremos ocupar la tuberia con el padre e hijo, debemos declarar la tubería antes de que creemos al hijo 
    if(hijo > 0){ // padre
        close(mi_tuberia[0]);//escribimos en el lado 1, entonces la cerramos
        printf("[PADRE] escribiendo en el pipe... \n");
        write(mi_tuberia[1], mensaje, sizeof(mensaje));// escribimos en el lado lector tuberia[1]
        close(mi_tuberia[1]); // cerramos el lado del array que acabamos de usar
        wait(NULL); //esperamos a que el hijo acabe, evitamos proceso zombie
        puts("El hijo ha finalizado, termino mi ejecución\n");
    } else if(hijo == 0){ // Proceso Hijo, va a leer de la tubería ocupa lado 0
        close(mi_tuberia[1]);
        read(mi_tuberia[0], buffer, sizeof(buffer)); // donde vamos a guardar lo que leemos en el buffer
        printf("[HIJO] ha recibido el siguiente mensaje del papa %s", buffer);
        close(mi_tuberia[0]);
        exit(1);
    }
    return 0;
}