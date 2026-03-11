#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> // librería para manejar la función wait();

int main(void){
    // en linux todo lo que _t es un nuevo tipo de variable
    int n;
    pid_t pid1;
    pid1 = fork();

    if(pid1==0){// Está condición solo la cumple el hijo
        printf("Hola soy el hijo y tengo un proceso PID: %d y el proceso de mi padre es: %d\n Ahora el valor de n: \n", getpid(), getppid()); //geppid(get parent process identifier)
        scanf("%d", &n);
        printf("Genial, has introducido el número %d\n", n);
    }else if(pid1 > 0){
        printf("Hola, soy el proceso padre con PID %d. Mi hijo tiene PID %d\n", getpid(), (int)pid1);
        wait(NULL);
        puts("Ahora si, el hijo ha acabado y ya puedo morir en paz");
    }else{
        perror("Ha ocurrido un error al crear el proceso");
    }

    return 0;
}