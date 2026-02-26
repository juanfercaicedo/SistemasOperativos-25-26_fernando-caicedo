#include <stdio.h>

int main(void){
    int x, contador = 0;

    puts("Introduzca un número entero: ");
    scanf("%d", &x);

    int temp = x;

    // Si el número es 0, tiene 1 dígito
    if(temp == 0){
        contador = 1;
    } else {
        if(temp < 0) {
            temp = -temp;  // Convertimos a positivo
        }

        while(temp > 0){
            temp /= 10;
            contador++;
        }
    }

    printf("El numero introducido tiene %d digitos\n", contador);

    return 0;
}
