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
#define SIZE 100

int main(void){
    int pipePadreHijo[2]; // Padre escribe, Hijo lee
    int pipeHijoPadre[2]; // Hijo escribe, Padre lee
    pid_t hijo;

    hijo = fork();

    if(hijo == 0){
        // --- PROCESO HIJO ---
        char bufferHijo[SIZE];
        int vocales = 0;

        close(pipePadreHijo[1]); // Cerramos escritura del primer pipe
        close(pipeHijoPadre[0]); // Cerramos lectura del segundo pipe

        // 1. Leer cadena del padre
        read(pipePadreHijo[0], bufferHijo, SIZE);

        // 2. Contar vocales
        for (int i = 0; bufferHijo[i] != '\0'; i++){
            char voc = tolower(bufferHijo[i]);
            if (voc == 'a' || voc == 'e' || voc == 'i' || voc == 'o' || voc == 'u') {
                vocales++;
            }
        }

        // 3. Enviar resultado al padre
        write(pipeHijoPadre[1], &vocales, sizeof(int));

        close(pipePadreHijo[0]);
        close(pipeHijoPadre[1]);
        exit(0);

    }else{
        // --- PROCESO PADRE ---
        char cadena[SIZE];
        int totalVocales;

        close(pipePadreHijo[0]); // Cerramos lectura del primer pipe
        close(pipeHijoPadre[1]); // Cerramos escritura del segundo pipe

        printf("Padre: Introduce una cadena: ");
        fgets(cadena, SIZE, stdin);
        
        // Quitar el salto de línea que añade fgets
        cadena[strcspn(cadena, "\n")] = 0;

        // 1. Enviar cadena al hijo
        write(pipePadreHijo[1], cadena, SIZE);

        // 2. Esperar respuesta del hijo
        read(pipeHijoPadre[0], &totalVocales, sizeof(int));

        printf("Padre: El hijo dice que hay %d vocales.\n", totalVocales);

        close(pipePadreHijo[1]);
        close(pipeHijoPadre[0]);
        wait(NULL);
    }

    return 0;
}