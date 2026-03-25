#include <stdio.h>

int main(void){
    int myNumbers[6] = {1, 2, 3, 4, 5, 6};
    int *inicio = myNumbers;              // apunta al primer elemento
    int *fin = myNumbers + sizeof(myNumbers)/sizeof(int)-1; // apunta al último elemento
    int temp;
    int tamañoArray = sizeof(myNumbers)/sizeof(int); // tamaño del array

    printf("Array original: ");
    for (int i = 0; i < tamañoArray; i++) {
        printf("%d ", myNumbers[i]);
    }
    printf("\n");

    while (inicio < fin) {
        temp = *inicio;
        *inicio = *fin;
        *fin = temp;
        inicio++;   // avanza hacia la derecha
        fin--;      // retrocede hacia la izquierda
    }
   
    // Mostrar el array invertido
    printf("Array invertido: ");
    for (int i = 0; i < tamañoArray; i++) {
        printf("%d ", myNumbers[i]);
    }
    return 0;
}
