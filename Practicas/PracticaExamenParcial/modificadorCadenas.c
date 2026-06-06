#include <stdio.h>

#define SIZE 256

int modificarCadena(char *stringAModificar);

int main(void) {
    char frase[SIZE];
    puts("Introduce una frase");
    fgets(frase, SIZE, stdin);

    int longitud = modificarCadena(frase);
    printf("\n--- RESULTADOS ---\n");
    printf("Frase modificada: %s\n", frase);
    printf("La longitud de la frase es de: %d caracteres.\n", longitud);

    return 0;
}

int modificarCadena(char *stringAModificar) {
    int contador = 0;

    // Recorremos la cadena hasta encontrar el carácter nulo '\0' que marca el final
    // Usamos el puntero iterando directamente sobre la memoria
    while (*stringAModificar != '\0') { // '\0' --> Carácter Nulo
        
        // El fgets captura también el "Enter" (\n), así que aprovechamos para eliminarlo
        // y no contarlo como un carácter válido de la frase
        if (*stringAModificar == '\n') {
            *stringAModificar = '\0'; 
            break; // Salimos del bucle porque ya terminó la frase real
        }

        // Si encontramos una 'a' minúscula, la cambiamos por un asterisco
        if (*stringAModificar == 'a') {
            *stringAModificar = '*';
        }

        // Aumentamos el contador de longitud y avanzamos el puntero a la siguiente letra
        contador++;
        stringAModificar++; 
    }

    // Retornamos la longitud total (equivalente a un stringAModificarlen manual)
    return contador;
}