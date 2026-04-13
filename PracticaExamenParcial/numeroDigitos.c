/*
Usar fork(), wait() y entender cómo el hijo envía un estado de salida al padre usando exit().
Enunciado:
El proceso padre debe pedirle al usuario un número por teclado. A continuación, crea un proceso hijo.

El Hijo: Debe tomar ese número y calcular si tiene más de 3 dígitos (usando divisiones sucesivas entre 10). 
Si tiene 3 dígitos o más, termina su ejecución enviando un exit(1). Si tiene menos de 3 dígitos, envía un exit(0).

El Padre: Debe esperar a que el hijo termine usando wait(&estado). Usando las macros WIFEXITED y WEXITSTATUS, el padre debe evaluar la respuesta e imprimir por pantalla: "El hijo me ha dicho que el número es grande" o "El hijo me ha dicho que el número es pequeño".
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void) {
    pid_t hijo;
    int numeroUsuario;
    puts("Introduzca un numero: ");
    scanf("%d", &numeroUsuario);
    int estadoHijo;

    hijo = fork();

    if(hijo < 0) {
        perror("ERROR EN LA CREACION DEL FORK");
        exit(0);
    } else if(hijo == 0) {
        int contador = 0;
        while(numeroUsuario > 0) {
            numeroUsuario = numeroUsuario / 10;
            contador++;
        }

        if(contador >= 3) {
            puts("El numero tiene tres o mas digitos");
            exit(1);
        } else if(contador < 3) {
            puts("El numero tiene tres o menos digitos");
            exit(0);
        }
    }
}