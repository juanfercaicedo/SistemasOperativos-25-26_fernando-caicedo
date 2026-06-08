/*
Te han contratado para programar el sistema operativo de la bóveda (cámara acorazada) del Banco Central. Por protocolos de máxima seguridad, la gran puerta de acero solo se abre si el Director del banco gira la llave maestra 3 veces seguidas desde una ubicación remota.
Objetivo del Programa:
Crear un programa en C que mantenga la puerta bloqueada y dormida hasta que reciba las 3 señales del exterior. Mientras tanto, un sistema de cámaras de seguridad estará vigilando en segundo plano.
Requisitos del Sistema:
Variables Globales:
Un contador de llaves_giradas (iniciado a 0). ¡Recuerda cómo protegerlo del compilador "listillo"!
Una variable bandera para mostrar mensajes.
El Mutex y la Variable de Condición.
El Manejador de Señales (El Director del Banco):
Debe capturar la señal SIGUSR1.
Suma 1 a las llaves giradas.
Levanta la bandera de mensaje.
Despierta a la bóveda tocando la campana de la variable de condición.
El Hilo de la Puerta (hilo_puerta):
Al empezar, obtiene su PID, lo imprime y te dice: "Sistema de Bóveda Iniciado. PID: [X]. Esperando 3 giros de llave..."
Echa el cerrojo con el Mutex.
Mientras las llaves giradas sean menos de 3, debe:
Irse a dormir al sofá (y soltar el cerrojo).
Al despertar, si la bandera está arriba, imprimir: "¡CLACK! Llave girada. (Llevamos [X] de 3)" y bajar la bandera.
Al conseguir las 3 llaves y salir del bucle, suelta el cerrojo definitivamente e imprime: "💰 ¡BÓVEDA ABIERTA! Acceso a los fondos concedido."
El Hilo de Cámaras (hilo_camaras): (¡Aquí está la novedad!)
En lugar de quedarse mudo, este hilo debe tener un bucle while que dé vueltas mientras las llaves sean menos de 3.
Dentro del bucle, debe hacer un sleep(3) y luego imprimir: "📷 [Cámaras]: Todo despejado en el pasillo...".
(Nota: Así verás cómo este hilo va imprimiendo cosas por su cuenta mientras la puerta está totalmente paralizada en el wait).
Al salir del bucle (cuando se abre la puerta), imprime: "📷 [Cámaras]: Apagando grabación. Entrando modo manual."
El Programa Principal (main):
Inicializa manualmente el Mutex y la Variable de Condición usando las funciones init.
Configura la señal.
Crea los dos hilos.
Espera a que terminen con join
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/syscall.h>

#define CANTIDAD_GIROS 3

pid_t idLlave;

int volatile llaves_giradas = 0;
int volatile mensaje = 0;

pthread_mutex_t lock;
pthread_cond_t giroLlave;

pthread_t hiloPuerta, hiloCamaras;

void señal(int signum){
    llaves_giradas++;
    mensaje = 1;

    pthread_cond_signal(&giroLlave);
}

void *puerta(void *arg){
    idLlave = getpid();
    int TID = idLlave;
    printf("TID del proceso: %d\n", TID);
    printf("Sistema de Bóveda Iniciado. PID: %d\n", TID);
    printf("Ejecuta: kill -SIGUSR1 %d\n", TID);

    pthread_mutex_lock(&lock);

    while(llaves_giradas < CANTIDAD_GIROS) {
        printf("Da %d de vueltas seguidas para abrir la puerta: \n", CANTIDAD_GIROS);
        
        pthread_cond_wait(&giroLlave, &lock);
        if(mensaje) {
            printf("Has girado la llave %d vuelta/s, te hace faltan %d vueltas\n", llaves_giradas, 3 - llaves_giradas);
            mensaje = 0;
        }
    }
    pthread_mutex_unlock(&lock);
    printf("💰 ¡BÓVEDA ABIERTA! Acceso a los fondos concedido.\n");

    return NULL;
}

void *camara(void *arg){
    while(llaves_giradas < CANTIDAD_GIROS) {
        sleep(3);
        printf("📷 [Cámaras]: Todo despejado en el pasillo...\n");
    }
    printf("📷 [Cámaras]: Apagando grabación. Entrando modo manual.\n");
    
    return NULL;
}

int main(void) {
    signal(SIGUSR1, señal);

    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&giroLlave, NULL);
    
    pthread_create(&hiloPuerta, NULL, puerta, NULL);
    pthread_create(&hiloCamaras, NULL, camara, NULL);
    
    pthread_join(hiloPuerta, NULL);
    pthread_join(hiloCamaras, NULL);

    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&giroLlave);

    return 0;
}