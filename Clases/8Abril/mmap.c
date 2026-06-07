#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h> // memory managment

static int *variable_compartida; // declaramos un punturo a una variable de tipo entero, es una dirección de memoria

int main(void){
    pid_t hijo;
    variable_compartida = mmap(NULL, sizeof(*variable_compartida), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,0);

    hijo = fork();
    
    if(hijo == 0) { // proceso hijo
        puts("Dame un valor para la variable: ");
        scanf("%d", &*variable_compartida);
        munmap(variable_compartida, sizeof(variable_compartida));
        exit(0);
    } else {
        puts("Soy el padre, quedo a la espera de que el hijo haga su trabajo");
        wait(NULL);
        printf("Soy el padre, y el hijo a cambiado su valor de la variable %d\n", *variable_compartida);
        munmap(variable_compartida, sizeof(variable_compartida));
    }
    return 0;
}