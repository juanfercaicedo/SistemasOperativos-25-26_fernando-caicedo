## Enunciado 
- Crear un programa que a través de procesos y/o hilos realice las siguientes tareas:
a. Estructura de datos
Crea una matriz de enteros con tamaño ROWSxCOLS, con valores iniciales para las constantes ROWS = 4 y COLS = 3.
b. Creación de hilos
Crea 3 hilos/procesos que se llamarán "coordinador", "positivo", "negativo". Estos hilos deben permanecer vivos hasta el final del programa
c. Coordinación
El hilo/proceso coordinador gestiona a los otros dos hilos, que se encargan de llenar de valores la matriz de enteros pidiendo su valor al usuario. 
d. Distribución de trabajo
Las posiciones de la matriz cuyo producto de los dos índices que la componen sea par (incluyendo el 0), será rellenada preguntando al usuario por el hilo/proceso "positivo".
Aquellas posiciones cuyo producto de los dos índices sea impar, se encargará de rellenarlas el hilo/proceso "negativo".
Nota: Cuando el producto de índices sea "0", se encarga el hilo o proceso "positivo".
e. Sincronización
Para sincronizar los 3 hilos/procesos no pueden emplearse flags o semáforos/mutex, sino únicamente señales. Para ello manejaremos un máximo de 3: SIGALRM, SIGUSR1, SIGUSR2.
f. Mostrar resultado
Cuando la matriz está llena por completo, "coordinador" muestra el contenido de la matriz en formato tabular. Los hilos/procesos restantes siguen vivos en este punto.
g. Finalización ordenada
Una vez mostrada la matriz, "coordinador" elimina primero a "negativo", luego a "positivo" y por último a sí mismo.
h. Terminación del programa
Solo entonces finalizará el proceso principal del programa, cuando los demás terminen sus tareas.

```c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#define ROWS 4
#define COLS 3

int matrix[ROWS][COLS], ipos, jpos, temp;
pthread_t positivo, negativo, coordinador;

// Prototipos
void muestra_tabular();
void positivo_handler(int);
void negativo_handler(int);
void coordinador_handler(int);
void* positivo_f();
void* negativo_f();
void* coordinador_thread_f();

int main(void) {
    // 1. Asignamos los manejadores de señales (vacíos, solo sirven para despertar de un pause)
    signal(SIGUSR1, positivo_handler);
    signal(SIGUSR2, negativo_handler);
    signal(SIGALRM, coordinador_handler);

    // 2. Creación de hilos (Requisito B)
    pthread_create(&positivo, NULL, positivo_f, NULL);
    pthread_create(&negativo, NULL, negativo_f, NULL);
    pthread_create(&coordinador, NULL, coordinador_thread_f, NULL);

    // 3. Terminación del programa: El main espera a que los demás terminen (Requisito H)
    pthread_join(coordinador, NULL);
    // Nota: positivo y negativo son cancelados desde coordinador, 
    // pero podemos hacerles join para recoger su estado final ordenadamente.
    pthread_join(negativo, NULL);
    pthread_join(positivo, NULL);

    printf("Programa finalizado correctamente.\n");
    return 0;
}

// --- Manejadores de señales (Requisito E) ---
// Su único propósito es interrumpir la función pause() de los hilos
void positivo_handler(int sig) {}
void negativo_handler(int sig) {}
void coordinador_handler(int sig) {}

// --- Funciones de los Hilos ---

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

    // Requisito C y D: Coordinación y Distribución
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
    
    // Requisito F: Mostrar resultado en formato tabular
    muestra_tabular();
    
    // Requisito G: Finalización ordenada
    // Coordinador elimina a negativo, luego a positivo y por último a sí mismo
    pthread_cancel(negativo);
    pthread_cancel(positivo);
    pthread_exit(NULL);
}

// --- Funciones Auxiliares ---
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
```