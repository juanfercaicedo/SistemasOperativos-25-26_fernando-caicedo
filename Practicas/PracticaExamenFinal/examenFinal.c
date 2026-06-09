#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#define ROWS 4
#define COLS 3

int matrix[ROWS][COLS], ipos, jpos, temp;
pthread_t positivo, negativo, coordinador;

void muestra_tabular();
void positivo_handler(int);
void negativo_handler(int);
void coordinador_handler(int);
void* positivo_f();
void* negativo_f();
void* coordinador_thread_f();

int main(void) {
    // 1. Asignamos los manejadores de señales
    signal(SIGUSR1, positivo_handler);
    signal(SIGUSR2, negativo_handler);
    signal(SIGALRM, coordinador_handler);

    // 2. Creación de hilos
    pthread_create(&positivo, NULL, positivo_f, NULL);
    pthread_create(&negativo, NULL, negativo_f, NULL);
    pthread_create(&coordinador, NULL, coordinador_thread_f, NULL);

    // 3. Terminación del programa, el main espera a que los demás terminen
    pthread_join(coordinador, NULL);
    pthread_join(negativo, NULL);
    pthread_join(positivo, NULL);

    printf("Programa finalizado correctamente.\n");
    return 0;
}

void positivo_handler(int sig) {}
void negativo_handler(int sig) {}
void coordinador_handler(int sig) {}


void* positivo_f() {
    while(1) {
        pause(); // Espera a recibir SIGUSR1
        printf("[Hilo Positivo] Introduce valor para la matriz[%d][%d] (producto par/0): ", ipos, jpos);
        scanf("%d", &temp);
        matrix[ipos][jpos] = temp;
        
        // Avisa al coordinador de que ya ha terminado
        pthread_kill(coordinador, SIGALRM);
    }
    return NULL;
}

void* negativo_f() {
    while(1) {
        pause(); // Espera a recibir SIGUSR2
        printf("[Hilo Negativo] Introduce valor para la matriz[%d][%d] (producto impar): ", ipos, jpos);
        scanf("%d", &temp);
        matrix[ipos][jpos] = temp;
        
        // Avisa al coordinador de que ya ha terminado
        pthread_kill(coordinador, SIGALRM);
    }
    return NULL;
}

void* coordinador_thread_f() {
    // Pequeño retardo para dar tiempo a los hilos trabajadores a llegar a su primer pause()
    usleep(100000); 

    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            ipos = i;
            jpos = j;
            
            if ((i * j) % 2 == 0) {
                // Producto par o 0 -> le toca a "positivo"
                pthread_kill(positivo, SIGUSR1);
                pause(); // Espera a que termine (SIGALRM)
            } else {
                // Producto impar -> le toca a "negativo"
                pthread_kill(negativo, SIGUSR2);
                pause(); // Espera a que termine (SIGALRM)
            }
        }
    }
    
    muestra_tabular();
    
    pthread_cancel(negativo);
    pthread_cancel(positivo);
    pthread_exit(NULL);
}

void muestra_tabular() {
    printf("\n--- Contenido de la Matriz ---\n");
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("------------------------------\n");
}

/*
void positivoHandler(int);
void negativoHandler(int);
void coordinadorHandler(int);

void *hiloNegativo(void *arg) {
    while(1) {
        pause(); // Espera recibir señal
        printf("[HILO POSITIVO]: INTRODUCE EL VALOR PARA LA MATRIZ[%d][%d]", columnaActual, filaActual);
        scanf("%d", &numeroUsuario);
        matriz[columnaActual][filaActual] = numeroUsuario;
        
        pthread_kill(coordinador, SIGALRM);
    }
    return NULL;
}

void *hiloPositivo(void *arg) {
    while(1) {
        pause(); // Espera recibir señal
        printf("[HILO NEGATIVO]: INTRODUCE UN VALOR PARA LA MATRIZ[%d][%d]", columnaActual, filaActual);
        scanf("%d", &numeroUsuario);
        matriz[columnaActual][filaActual] = numeroUsuario;
        pthread_kill(coordinador, SIGALRM);
    }
    return NULL;
}

void imprimirMatriz() {
    printf("=== RESULTADOS ===\n");
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
    printf("---------------\n");
}

void *hiloCoordinador(void *arg) {
    sleep(1);
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            columnaActual = i;
            filaActual = j;

            if(i * j % 2 == 0) {
                pthread_kill(positivo, SIGUSR1);
                pause(); // Esperamos a que acabe SIGALRM
            } else {
                pthread_kill(negativo, SIGUSR2);
                pause(); // Esperamos a SIGLRM
            }
        } 
    }
    imprimirMatriz();

    pthread_cancel(negativo);
    pthread_cancel(positivo);
    pthread_exit(NULL);
}

void positivoHandler(int sig){}
void negativoHandler(int sig){}
void coordinadorHandler(int sig){}

*/