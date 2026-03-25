#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>

int main(void){
    pid_t pid;
    pid = syscall (SYS_getpid); // 
    printf("El ID mediante llamada al sistema es: %d\n", pid);
    printf("El ID mediante wrapper o función de C es: %d\n", getpid());
    printf("El ID mediante llamada directísima es %d\n", (int)syscall(39)); // LLamada al sistema 39 es lo mismo que pid

    return 0;
}

/*
pid_t es una llamada al sistema
Es una variable que recoge el identificador, el id de un proceso que se está realizando 
*/