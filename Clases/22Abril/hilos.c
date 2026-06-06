#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <time.h>
#include <pthread.h> // Librería para utilizar hilos

pthread_t ntid; // tipo de variable pthread_t con nombre ntid

void printids(const char *s){
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s pid %u tid %u\n", s, (unsigned int)pid, (unsigned int)tid);
    return;
}

void* nuevo_hilo (void *arg) {
    printids("Nuevo hilo: ");
    return NULL; // puntero vacío
}

int main(void) {
    int error;
    error = pthread_create(&ntid, NULL, &nuevo_hilo, NULL);
    printids("Hilo principal: ");
    /*
    pthread_join(ntid, NULL); //otra forma de hacer lo que hace usleep(100)
    */
    usleep(100); // evita que el hilo padre acabe antes que el hilo hijo
    return 0;
}