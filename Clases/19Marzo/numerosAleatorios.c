/*Creamos un hijo, papa va a crear 10[1 - 100] números aleatorios y se los envia uno a uno al hijo
El hijo va a averiguar cuales son los números primos, lo va a mostrar por pantalla y lo devuelve al padre el total de primos que ha encontrado
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <sys/types.h>
#include <stdlib.h>
#include <time.h> // libreria de medidas de tiempo
#include <stdbool.h> // permite poner false y true
#include <ctype.h> // charC = tolower(char) para pasar todos los caracteres a minuscula

int main(void){
    srand(time(NULL)); // plantamos una semilla para que los números aleatorios se basen en ellos
    for(int i = 0; i < 10; i++){
        int numero = rand() % 100;    
        printf("%d.- %d\n", i+1, numero);
    }

    return 0;
}