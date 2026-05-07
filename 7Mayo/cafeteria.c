#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/syscall.h>

#define MONEDAS_NECESARIAS 3

void *hilo_maquina(void *arg);
void *hilo_monitor(void *arg);
void manejador(int signum);

pid_t id_maquina = 0;
pthread_t t_maquina, t_monitor;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t moneda_insertada = PTHREAD_COND_INITIALIZER;

static volatile int monedas = 0;
static volatile int mostrar_mensaje = 0;

int main(void)
{
    signal(SIGUSR1, manejador);

    pthread_create(&t_maquina, NULL, hilo_maquina, NULL);
    pthread_create(&t_monitor, NULL, hilo_monitor, NULL);

    pthread_join(t_maquina, NULL);
    pthread_join(t_monitor, NULL);

    return 0;
}

void *hilo_maquina(void *arg)
{
    id_maquina = syscall(SYS_gettid);

    printf("Máquina de café V2.0 Inicializada\n");
    printf("Mi TID es %d\n", id_maquina);
    printf("Ejecuta en otra terminal: kill -SIGUSR1 %d\n", id_maquina);

    pthread_mutex_lock(&lock);

    while (monedas < MONEDAS_NECESARIAS)
    {
        printf("Máquina en espera... Inserta monedas (TID %d)\n", id_maquina);

        pthread_cond_wait(&moneda_insertada, &lock);

        if (mostrar_mensaje)
        {
            printf("\nClinc! Moneda aceptada (Llevas %d de %d)\n",
                   monedas, MONEDAS_NECESARIAS);

            mostrar_mensaje = 0;
        }
    }

    pthread_mutex_unlock(&lock);

    printf("\nBzzzzz Preparando tu café...\n");
    sleep(2);

    printf("¡Aquí tienes! Gracias por tu compra. Apagando máquina.\n");

    return NULL;
}

void *hilo_monitor(void *arg)
{
    while (monedas < MONEDAS_NECESARIAS)
    {
        sleep(1);
    }

    printf("[Monitor] Café despachado. Cerrando sistema.\n");

    return NULL;
}

void manejador(int signum)
{
    monedas++;
    mostrar_mensaje = 1;

    pthread_cond_signal(&moneda_insertada);
}