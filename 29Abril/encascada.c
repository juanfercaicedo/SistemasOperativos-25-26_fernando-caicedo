#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define LIMITE 10

void calcula() {
    long long unsigned t;
    for(t = 0; t < (0xFFFFFF); t++);
}

pthread_t array[LIMITE];
int n = 1;

int main(void) {

}