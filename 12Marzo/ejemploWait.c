// Proceso zombie: Salvo el proceso #0 todos los procesos que tengamos en el SO debe tener un papá, cuando el papá muere antes que el hijo, el hijo se vuelve un proceso zombie.
/*
- Papá crea un hijo
- El hijo saca un mensaje por pantalla con su ID y su PPID (por lo tanto el padre tiene que estar vivo)
- Matamos al padre
- Utilizamos comandos como el PS desde una consola de comandos y verificamos quién es ahora el padre(postizo) del proceso hijo
*/
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>

int main(void){
    pid_t proceso;
    printf("Hola soy el proceso padre con un ID %d\n", getpid());
    proceso = fork();
    if(proceso > 0){ // Proceso Padre
        sleep(1); // Dormimos al padre 1 segundo para que se ejecute el hijo
        exit(1); // Muere el padre
    } else if(proceso == 0){ // Proceso hijo
        printf("Hola soy el proceso hijo con un ID: %d, y mi padre tiene un ID %d\n", getpid(), getppid());
        sleep(2); // El hijo se duerme dos segundos y se regresa al exit() del padre, por lo tanto murio
        printf("Hola de nuevo, soy el proceso hijo con un ID: %d, y ahora mi padre tiene un ID %d\n", getpid(), getppid()); // Linux asigno un nuevo papá (systemd / systemdemon se encarga de esto)
    }
    return 0;
}