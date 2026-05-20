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

}