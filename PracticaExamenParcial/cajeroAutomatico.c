/*
El padre creará una tubería (pipe) y una memoria compartida (mmap).

El padre inicializa el saldo de la cuenta bancaria en $1000 (en la memoria compartida).

Se crea el proceso hijo (fork).

El Hijo (El Cajero): * Resta $300 directamente de la cuenta bancaria (usando el puntero del mmap).

Genera un número de recibo (ejemplo: int recibo = 8542;).

Le envía ese número de recibo al padre a través de la tubería.

Termina su ejecución con exit(0).

El Padre (El Banco):

Espera a que el cajero (hijo) termine su operación (wait).

Lee el número de recibo que le llegó por la tubería.

Imprime un mensaje confirmando el número de recibo y mostrando el saldo restante en la cuenta (leyendo el mmap).

Limpia y destruye la memoria con munmap
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>

static int *saldoInicial;

int main(void) {
    pid_t hijo;
    int mi_tuberia[2];

    saldoInicial = mmap(NULL, sizeof(*saldoInicial), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *saldoInicial = 1000;
    pipe(mi_tuberia);

    hijo = fork();

    if(hijo < 0) {
        perror("ERRORRRRRR EN LA CREACION DEL FORK");
        exit(0);
    } else if(hijo == 0) {
        *saldoInicial -= 300;
        close(mi_tuberia[0]);
        
        srand(time(NULL));
        int numeroRecibo = rand()%100000;
        

        write(mi_tuberia[1], &numeroRecibo, sizeof(numeroRecibo));
        close(mi_tuberia[1]);
        exit(0);
    } else {
        
        close(mi_tuberia[1]);
        wait(NULL);
        int numeroRecibido;

        read(mi_tuberia[0], &numeroRecibido, sizeof(numeroRecibido));
        close(mi_tuberia[0]);
        printf("Transacción #%d EXITOSA. El saldo total de la cuenta es: $%d\n", numeroRecibido, *saldoInicial);
        munmap(saldoInicial, sizeof(*saldoInicial));
    }

    return 0;
}