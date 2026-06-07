/* Un padre crea un hijo. El padre tiene un buffer de 100 bytes, y le pedimos al usuario que introduzca una cadena por teclado, el padre envia al hijo la cadena.
El hijo cuenta la cantidad de vocales que hay en la cadena y el hijo devielve ese número al padre.
*/
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>
#include <stdbool.h> // permite poner false y true
#include <ctype.h> // charC = tolower(char) para pasar todos los caracteres a minuscula

#define BUFFER 100

int main(void) {
    int pipe1[2]; // Tuberia Padre (Padre manda mensaje a hijo)
    int pipe2[2]; // Tuberia Hijo (Hijo envia las vocales a padre)

    pid_t hijo;

    pipe(pipe1);
    pipe(pipe2);

    hijo = fork();
    if(hijo < 0) {
        perror("Error durante el fork()");
        exit(EXIT_FAILURE);
    } else if (hijo == 0) {
        // --- PROCESO HIJO ---
        char bufferHijo[BUFFER];
        close(pipe1[1]);
        read(pipe1[0], bufferHijo, sizeof(bufferHijo));
        
        // Contamos las vocales
        int contador = 0;
        for(int i = 0; bufferHijo[i] != '\0'; i++) {
            char vocales = tolower(bufferHijo[i]);
            if(vocales == 'a'||vocales == 'e'||vocales == 'i' || vocales == 'o'||vocales == 'u'){
                contador ++;
            }
        }
        
        close(pipe2[0]);
        write(pipe2[1], &contador, sizeof(int));
        
        close(pipe1[0]);
        close(pipe2[1]);
        exit(0);
    } else {
        // ---PROCESO PADRE ---
        char cadena[BUFFER];
        int resultado;
        // 1. Padre manda mensaje al hijo
        // --- PADRE (dentro del else) ---
        close(pipe1[0]);

        puts("Introduce una oración: ");
        // Lee hasta 99 caracteres y se detiene al pulsar Enter
        fgets(cadena, BUFFER, stdin); 
        
        // Quitar el salto de línea que añade fgets
        cadena[strcspn(cadena, "\n")] = 0;
        
        // write escribe lo que realmente mide la cadena (+1 para incluir el \0)
        write(pipe1[1], cadena, strlen(cadena) + 1); 

        // 2. Padre recibe el conteo del hijo
        close(pipe2[1]);
        read(pipe2[0], &resultado, sizeof(int));
        
        printf("[PADRE] Mi hijo ha acabado, la cantidad de vocales es de: %d", resultado);
        
        close(pipe1[1]);
        close(pipe2[0]);
        wait(NULL); // Padre espera a que su hijo acabe su proceso
    }
    return 0;
}