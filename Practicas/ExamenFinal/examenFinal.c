/*
Crear un programa que a través de procesos y/o hilos realice las siguientes tareas: 
a. Estructura de datos Crea una matriz de enteros con tamaño ROWSxCOLS, con valores iniciales para las constantes ROWS = 4 y COLS = 3. 
b. Creación de hilos Crea 3 hilos/procesos que se llamarán "coordinador", "positivo", "negativo". Estos hilos deben permanecer vivos hasta el final del programa 
c. Coordinación El hilo/proceso coordinador gestiona a los otros dos hilos, que se encargan de llenar de valores la matriz de enteros pidiendo su valor al usuario. 
d. Distribución de trabajo Las posiciones de la matriz cuyo producto de los dos índices que la componen sea par (incluyendo el 0), será rellenada preguntando al usuario por el hilo/proceso "positivo". 
Aquellas posiciones cuyo producto de los dos índices sea impar, se encargará de rellenarlas el hilo/proceso "negativo". 
Nota: Cuando el producto de índices sea "0", se encarga el hilo o proceso "positivo". 
e. Sincronización Para sincronizar los 3 hilos/procesos no pueden emplearse flags o semáforos/mutex, sino únicamente señales. 
Para ello manejaremos un máximo de 3: SIGALRM, SIGUSR1, SIGUSR2. 
f. Mostrar resultado Cuando la matriz está llena por completo, "coordinador" muestra el contenido de la matriz en formato tabular. 
Los hilos/procesos restantes siguen vivos en este punto. 
g. Finalización ordenada Una vez mostrada la matriz, "coordinador" elimina primero a "negativo", luego a "positivo" y por último a sí mismo. 
h. Terminación del programa Solo entonces finalizará el proceso principal del programa, cuando los demás terminen sus tareas.
*/


#include <stdio.h>    
#include <stdlib.h>   
#include <unistd.h>   
#include <pthread.h>  
#include <sys/types.h>
#include <sys/wait.h> 
#include <signal.h>

#define ROWS 4
#define COLS 3

int matriz[ROWS][COLS];
int columnaActual = 0, filaActual = 0, numeroUsuario = 0;

pthread_t coordinador, positivo, negativo;

// Señales que vamos a utilizar
void positivoHandler(int signum){}
void negativoHandler(int signum){}
void coordinadorHandler(int signum){}

void imprimirMatriz() {
    printf("=== RESULTADOS === \n");
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("%d\t", matriz[i][j]);
        }
        printf("\n");
    }
    printf("---------\n");
}

void *hiloNegativo(void *arg) {
    while(1){ 
        pause();
        printf("[HILO NEGATIVO]: INTRODUCE UN VALOR PARA LA MATRIZ [%d][%d]\n", columnaActual, filaActual);
        scanf("%d", &numeroUsuario);
        matriz[columnaActual][filaActual] = numeroUsuario;
        pthread_kill(coordinador, SIGALRM);
    }
}

void *hiloPositivo(void *arg) {
    while(1) {
        pause();
        printf("[HILO POSITIVO]: INTRODUCE UN VALOR PARA LA MATRIZ [%d][%d]\n", columnaActual, filaActual);
        scanf("%d", &numeroUsuario);
        matriz[columnaActual][filaActual] = numeroUsuario;
        pthread_kill(coordinador, SIGALRM);
    }
}

void *hiloCoordinador(void *arg) {
    sleep(1);
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            columnaActual = i;
            filaActual = j;

            if(i * j % 2 == 0) {
                pthread_kill(positivo, SIGUSR1);
                pause();
            } else {
                pthread_kill(negativo, SIGUSR1);
                pause();
            }
        }
    }

    imprimirMatriz();

    pthread_cancel(positivo);
    pthread_cancel(negativo);
    pthread_exit(NULL);
}


int main(void) {
    // Creamos las señales
    signal(SIGUSR1, positivoHandler);
    signal(SIGUSR2, negativoHandler);
    signal(SIGALRM, coordinadorHandler);

    // Creamos los hilos
    pthread_create(&coordinador, NULL, hiloCoordinador, NULL);
    pthread_create(&positivo, NULL, hiloPositivo, NULL);
    pthread_create(&negativo, NULL, hiloNegativo, NULL);

    // Esperamos a que los hilos acaben
    pthread_join(coordinador, NULL);
    pthread_join(positivo, NULL);
    pthread_join(negativo, NULL);

    printf("Programa finalizador correctamente \n");

    return 0;
}