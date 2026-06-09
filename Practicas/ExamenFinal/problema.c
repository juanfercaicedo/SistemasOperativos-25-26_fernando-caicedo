/*
Se está celebrando la final de un torneo de tiro con arco por equipos. El equipo consta de dos arqueros que se turnan para disparar a 5 dianas. Un árbitro coordina quién dispara en cada ronda y anota los puntos.
Objetivo del Programa:
Crear un programa en C que utilice hilos y exclusivamente señales para sincronizar los turnos de los arqueros.
Requisitos del Sistema:
Estructuras y Variables Globales:
Un array unidimensional de enteros: int puntuaciones[5];
Una variable global int ronda_actual = 0; para saber por qué diana van.
Los identificadores de los hilos: arbitro, arquero1, arquero2.
Los Hilos Arqueros (Trabajadores):
El arquero1 reaccionará a la señal SIGUSR1.
El arquero2 reaccionará a la señal SIGUSR2.
Ambos viven en un bucle infinito durmiendo (pause()).
Al despertar, deben pedir los puntos al usuario por pantalla.
(Ej: "[Arquero 1] Introduce los puntos (0-10) de la ronda 0: ")
Guardan el número introducido con scanf en puntuaciones[ronda_actual].
Le avisan al árbitro de que ya han tirado mandándole la señal SIGALRM.
El Hilo Árbitro (Coordinador):
Debe dar 1 segundo de cortesía (sleep(1)) al empezar para que los arqueros se posicionen y se duerman.
Mediante un bucle for, recorre las 5 rondas (del 0 al 4).
En cada iteración, actualiza la ronda_actual.
Distribución: Si el número de la ronda es par (0, 2, 4), le manda la señal al arquero1. Si es impar (1, 3), le manda la señal al arquero2.
Tras mandar la orden, el árbitro se duerme (pause()) esperando la confirmación (SIGALRM).
Sincronización (La regla de oro):
NO puedes usar Mutex, Semáforos ni variables de condición. Solo señales.
Recuerda crear los manejadores vacíos en tu código y asignarlos en el main antes de crear los hilos.
Finalización:
Cuando el bucle del árbitro termina, el árbitro imprime por pantalla un resumen de las 5 puntuaciones y calcula la SUMA TOTAL de los puntos del equipo.
Tras imprimirlo, el árbitro "elimina" a los dos arqueros usando la función adecuada.
El programa principal (main) espera a los hilos y finaliza limpiamente.
*/

#include <stdio.h>    
#include <stdlib.h>   
#include <unistd.h>   
#include <pthread.h>  
#include <sys/types.h>
#include <sys/wait.h> 
#include <signal.h>

#define NUMERO_RONDAS 5

pthread_t arbitro, arquero1, arquero2;

int puntuaciones[NUMERO_RONDAS];
int ronda_actual = 0;
int numeroUsuario = 0;

void arbitroHandler(int signum){}
void arquero1Handler(int signum){}
void arquero2Handler(int signum){}

void *hiloArbitro(void *arg) {
    sleep(1);
    for(int i = 0; i < NUMERO_RONDAS; i++) {
        
        ronda_actual = i;
        
        if(i % 2 == 0){
            pthread_kill(arquero1, SIGUSR1);
            pause();
        } else {
            pthread_kill(arquero2, SIGUSR2);
            pause();
        }
    }

    pthread_cancel(arquero1);
    pthread_cancel(arquero2);
    pthread_exit(NULL);
}

void *hiloArquero1(void *arg) {
    while(1) {
        pause();
        printf("[Arquero 1] Introduce los puntos (0-10) de la ronda %d: \n", ronda_actual);
        scanf("%d", &numeroUsuario);
        puntuaciones[ronda_actual] = numeroUsuario;
        pthread_kill(arbitro, SIGALRM);
    }
    return NULL;
}

void *hiloArquero2(void *arg) {
 while(1) {
        pause();
        printf("[Arquero 2] Introduce los puntos (0-10) de la ronda %d: \n", ronda_actual);
        scanf("%d", &numeroUsuario);
        puntuaciones[ronda_actual] = numeroUsuario;
        pthread_kill(arbitro, SIGALRM);
    }
    return NULL;
}

int main(void) {
    // Definimos las señales
    signal(SIGALRM, arbitroHandler);
    signal(SIGUSR1, arquero1Handler);
    signal(SIGUSR2, arquero2Handler);

    // Creamos los hilos
    pthread_create(&arbitro, NULL, hiloArbitro, NULL);
    pthread_create(&arquero1, NULL, hiloArquero1, NULL);
    pthread_create(&arquero2, NULL, hiloArquero2, NULL);

    // Esperamos a que los hilos acaben
    pthread_join(arbitro, NULL);
    pthread_join(arquero1, NULL);
    pthread_join(arquero2, NULL);

    return 0;
}