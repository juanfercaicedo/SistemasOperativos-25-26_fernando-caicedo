#include <stdio.h>

void propina(int valor);

int main (void){
    int totalUsuario;

    puts("Introduzca el valor de su cuenta: ");
    scanf("%d", &totalUsuario);

    propina(totalUsuario);
}

void propina(int valor){
    float propinaCamarero;
    if(valor > 0){
        propinaCamarero = valor * 0.2;
        printf("La propina que se recibe es de $%f ", propinaCamarero);
    } else{
        printf("ERROR! EL VALOR INGRESADO ES NEGATIVO!!");
    }
}