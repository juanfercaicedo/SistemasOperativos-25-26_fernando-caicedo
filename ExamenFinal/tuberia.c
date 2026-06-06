#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>

int main(void) {
    int mi_tuberia[2];
    pid_t hijo;
    char mensaje[] = "Mensaje enviado através del pipe exitosamente!";
    char buffer[100]; // siempre que ocupemos tuberias declaramos una variable buffer para guardar información
    pipe(mi_tuberia);

    hijo = fork();
    if(hijo < 0) {
        perror("Error en el fork()");
        exit(EXIT_FAILURE);
    } else if(hijo == 0) {
        close(mi_tuberia[1]);// tuberia de escritura
        read(mi_tuberia[0], buffer, sizeof(buffer));
        printf("[HIJO] He recibido el siguiente mensaje de mi padre: %s\n", buffer);
        close(mi_tuberia[0]);
    } else {
        close(mi_tuberia[0]);// tuberia de lectura
        write(mi_tuberia[1], mensaje, sizeof(mensaje));
        close(mi_tuberia[1]);
        wait(NULL);
        printf("[PADRE] Mi proceso ha terminado envié el mensaje a mi hijo\n");
    }

    return 0;
}