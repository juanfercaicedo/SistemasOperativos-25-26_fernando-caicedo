#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>

int main(void){
    pid_t hijo = fork();

    if(hijo > 0){
        wait(NULL);
        puts("El proceso suicida hijo ha acabado de ejecutar el esclavo, me largo");    
    }else if(hijo == 0){
        execlp("./esclavo", "esclavo", NULL); // todos los programas en Linux deben de tener al menos como parámetro su propio nombre
        puts("pene de burro australiano"); // en teoría nada debajo del execlp se debería ejecutar ya que se debe reemplazar por el programa esclavo
    }
    return 0;
}

/*
    execl
    execlp el funcionamiento es igual
*/