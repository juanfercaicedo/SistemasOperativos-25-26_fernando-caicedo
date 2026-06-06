#include <stdio.h>
void primos(int inicio, int final);

int main(void){
    int x, y;

    printf("Introduce el primer número:")
    scanf("%d", &x);

    printf("Ahora introduce el segundo número: ")
    scanf("%d", &y);

    primos(x, y); 

}

void buscarPrimos(int inicio, int fin) {
    printf("Primos en el rango [%d, %d]:\n", inicio, fin);

    for (int i = inicio; i <= fin; i++) {
        if (i <= 1) continue;

        int esPrimo = 1;
        for (int j = 2; j < i; j++) {
            if (i % j == 0) {
                esPrimo = 0;
                break;
            }
        }

        if (esPrimo) {
            printf("%d ", i);
        }
    }
    printf("\n");
}