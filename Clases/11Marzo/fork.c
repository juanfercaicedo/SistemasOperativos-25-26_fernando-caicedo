#include <stdio.h>
#include <unistd.h>

int main(void){
    puts("Pene de burro australiano");
    fork(); // Se crea una copia del proceso en memoria que comienza a ejecutarse a partir de la linea siguiente
    puts("Hola mundo");
    fork();
    fork();
    puts("Esta clase es aburrida"); // En este caso el fork copia esta linea, y el siguiente fork lo vuelve a copiar, por ende hay el proceso original, la copia del proceso y la segunda copia del proceso
    // fork son copias de variables, las copias no se comunican entre sí.
    
}