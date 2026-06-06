#include <stdio.h>
int main (void){
    int numeroUsuario, invertido = 0;
    printf("Introduzca un número: ");

    scanf("%d", &numeroUsuario);

    int temp = numeroUsuario;

    if(temp < 0){
        temp = -temp;
    }else {
        while(temp > 0){
            invertido = invertido * 10 + (temp % 10);
            temp = temp / 10;
        }
    
        printf("El numero invertido es: %d", invertido);
    }
}
