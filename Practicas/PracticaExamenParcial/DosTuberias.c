/*
Crea dos tuberías: una padre→hijo y otra hijo→padre. 
El padre envía dos números al hijo. El hijo calcula su suma y la devuelve al padre por la segunda tubería. 
El padre imprime el resultado. No uses mmap ni exit() para pasar el resultado.
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>

int main(void){
    pid_t hijo;
    int bufferHijo[20];
    int bufferPadre[20];
    int numeroUsuario1, numeroUsuario2;
    int mi_tuberiaHijo[2], mi_tuberiaPadre[2];
    puts("Introduce un número: ");
    scanf("%d", &numeroUsuario1);
    puts("Ahora introduce otro número para sumarlo: ");
    scanf("%d", &numeroUsuario2);

    pipe(mi_tuberiaHijo);
    pipe(mi_tuberiaPadre);

    hijo = fork();

    if(hijo < 0) {
        perror("error en el fork");
        exit(1);
    } else if(hijo == 0) {
        close(mi_tuberiaHijo[1]);
        read(mi_tuberiaHijo[0], bufferHijo, 20);
        close(mi_tuberiaHijo[0]);

    }
}