#include <stdio.h>

void cambiarPosicion(char *array, int tamaño);

int main(void){
    int tamañoArray;
    
    puts("Introduce el número de elementos del array:");
    scanf("%d", &tamañoArray);

    char array[tamañoArray + 1]; 
    
    puts("Ahora introduce los elementos de tu array");
    for(int i = 0; i < tamañoArray; i++){
        scanf(" %c", &array[i]); 
    }

    array[tamañoArray] = '\0';

    cambiarPosicion(array, tamañoArray);

    printf("Array final: %s\n", array);

    return 0;
}

void cambiarPosicion(char *array, int tamaño){
    int posicion;
    char nuevo;

    printf("¿Qué posición quieres cambiar? ");
    scanf("%d", &posicion);

    posicion = posicion - 1;

    printf("Introduce el nuevo caracter: ");
    scanf(" %c", &nuevo);

    array[posicion] = nuevo;
}  