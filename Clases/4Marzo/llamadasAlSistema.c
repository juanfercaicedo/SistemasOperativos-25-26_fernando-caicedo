#include <stdio.h>
#include <unistd.h> // Unix standard en c
#include <sys/syscall.h> // todas las llamadas del sistema en s
// Llamadas al sistema en c

/*
int main(void){
    char mensaje[] = "Hola Mundo \n";
    printf("%s", mensaje);

    write(1, mensaje,sizeof(mensaje)); // Solo compatible en linux, es un wrapper.
    // 1(stdout) que se saque por pantalla
    

    return 0;
}
*/

int main(void){
    har mensaje[] = "Hola Mundo \n";
    printf("%s", mensaje);

    write(1, mensaje,sizeof(mensaje));
    syscall(SYS_write, 1, mensaje, sizeof(mensaje));
    
    return 0;
}