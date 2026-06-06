#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static int intentos = 0;
static int mostrar_mensaje = 0;
static int terminar = 0;

void manejador_sigint(int sig)
{
    intentos++;

    if (intentos < 3)
    {
        mostrar_mensaje = 1;
    }
    else
    {
        terminar = 1;
    }
}

int main(void)
{
    signal(SIGINT, manejador_sigint);

    printf("PID: %d\n", getpid());

    while (!terminar)
    {
        if (mostrar_mensaje)
        {
            printf("\n¡Ouch! Eso duele. Te quedan %d intento(s).\n", 3 - intentos);
            mostrar_mensaje = 0;
        }

        printf("El programa sigue ejecutándose... (PID %d)\n", getpid());

        sleep(2);
    }

    printf("\nBien, me rindo. ¡Hasta luego!\n");

    return 0;
}