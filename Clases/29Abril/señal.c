#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void sig_handler_padre(int signum) {
    printf("Padre: recibida una señal de respuesta del chaval \n");
}

void sig_handler_hijo(int signum) {
    printf("Hijo: recibida señal del padre \n");
    sleep(1);
    kill(getppid(), SIGUSR1);
}

int main(void) {
    pid_t pid;
    pid = fork();

    if(pid < 0) {
        perror("Error en el fork");
        exit(1);
    } else if(pid == 0) { // proceso hijo
        signal(SIGUSR1, sig_handler_hijo);
        printf("Hijo: a la epsera de una señal \n");
        pause(); // duerme un proceso hasta que recibe su señal
    } else {
        signal(SIGUSR1, sig_handler_padre);
        sleep(1);
        kill(pid, SIGUSR1);
        printf("Padre: ...me quedo a la espera de una respuesta del chaval \n");
        pause();
    }

    return 0;
}