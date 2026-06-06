#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void manejador(int signum) {
    puts("Dentro del manejadro de señales ");
}

int main(void) {
    signal(SIGUSR1, manejador);
    puts("Dentro de la main");
    raise(SIGUSR1); // Invoca al proceso
    puts("De nuevo dentro de la main");

    return 0;
}