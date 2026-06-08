#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <stdbool.h>

bool mensaje = false;
int intentos = 0;
bool terminar = true;

void manejador_señal(int n){
    intentos++;

    if(intentos < 3) {
        mensaje = true;
    } else {
        terminar = true;
    }
}


int main(void) {
    signal(SIGINT, manejador_señal);
    
    printf("PID: %d \n", getpid());

    while(!terminar) {
        if(mensaje) {
            printf("Eso dolio, te quedan %d intentos", 3 - intentos);
            mensaje = false;
        } 
        
        printf("El programa sigue ejecutandose... (PID: %d)", getpid());

        sleep(2);
    }
    printf("\nMe rindo hasta luego\n")

    return 0;
}

