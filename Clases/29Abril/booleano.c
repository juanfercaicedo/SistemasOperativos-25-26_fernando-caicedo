#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h> // Función para poder utilizar booleanos

void manejador(int signum);

int main(void) {
    signal(SIGINT, manejador);
    while(true) {
        puts("Hola amiguitos, aquí estoy pasando el rato");
        sleep(2);
    }
    return 0;
}

void manejador(int signum) {
    puts("Que te jodan");
}