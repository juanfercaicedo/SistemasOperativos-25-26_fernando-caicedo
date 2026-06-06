#include<stdio.h>

int main(void){
    int numeroUsuario;

    puts("Introduzca un número: ");
    scanf("%d", &numeroUsuario);

    if(numeroUsuario % 2 != 0){
        puts("Es numero impar");
    } else{
        puts("Es numero par");
    }
    return 0;
}