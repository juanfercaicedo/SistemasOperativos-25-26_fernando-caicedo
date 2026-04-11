#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(void){
    pid_t hijo; // declaramos variable de hijo
    int numeroUsuario;
    int resultado;
    int estado;

    puts("Introduce un número para calcular su cuadrado: ");
    scanf("%d", &numeroUsuario);

    hijo = fork();

    if(hijo < 0) {
        perror("ERROR!!!");
    } else if(hijo == 0) {
        // --- PROCESO HIJO ---
        resultado = numeroUsuario * numeroUsuario;
        exit(resultado); // Enviamos el resultado como "última voluntad"
        
    } else {
        // --- PROCESO PADRE ---
        wait(&estado); // Esperamos a que el hijo muera y recogemos su estado
        
        // Lupa 1: ¿Murió de forma natural usando exit()? (Devuelve Sí o No)
        if(WIFEXITED(estado)){ 
        
            int numeroCuadrado = WEXITSTATUS(estado); 
            
            printf("El cuadrado del numero %d es %d \n", numeroUsuario, numeroCuadrado);
        }
    }
    
    return 0; // Buena práctica en C para indicar que el programa principal terminó bien
}