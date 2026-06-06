#include <stdio.h>
/*
int main(void) {
    int myNumbers[4] = {25, 50, 75, 100};
    int *puntero = myNumbers;
    for (int i = 0; i < 4; i++) {
        printf("La direccion de memoria de %d es: %p\n", myNumbers[i], (puntero + i));
    }
    return 0;
}
*/

int main(void) {
    int myNumbers[6] = {1, 2, 3, 4, 5, 6};
    int *inicio = myNumbers;
    int tamañoArray = sizeof(myNumbers) / sizeof(int);
    int *fin = myNumbers + tamañoArray - 1;
    int temp;

    while (inicio < fin) {
        temp = *inicio;     
        *inicio = *fin;
        *fin = temp;
        inicio++;
        fin--;
    }
    puts("Array invertido: ");
    for(int i = 0; i < tamañoArray; i++) {
        printf(" %d, ", myNumbers[i]);
    }
}