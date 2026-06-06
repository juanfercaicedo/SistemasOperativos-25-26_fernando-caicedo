#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>

int main(void){
    pid_t hijo = fork();

    if(hijo > 0){ // proceso padre
        wait(NULL);
    }else if(hijo == 0){ // proceso hijo
        execlp("/bin/ps", "ps", "-l", "-e" ,NULL);      // " ", " " lo que está dentro de las comillas son parámetros, NULL indica que hemos acabado de meter parámetros
        // Podemos meter cuantos parámetros como queramos
        // como mínimo en la version mas corta posible podemos execlp("/bin/ps", "ps", NULL); Dirección del fichero, y como parámetros ponemos el nombre del programa que estamos ejecuatando en este caso ps(process status)
        printf("Toda la clase aprueba con un 10 en Sistemas Operativos");
    }

    puts("El hijo ha muerto, larga vida al hijo");

    return 0;
}