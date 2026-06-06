#include <stdio.h>
void intercambiarNumero(int *numero1, int *numero2);

int main(void) {
    int a = 5;
    int b = 10;
    
    printf("Antes a = %d y b = %d\n", a, b);

    intercambiarNumero(&a, &b); 

    printf("Ahora el valor de a es %d y el de b %d\n", a, b);
    
    return 0;
}

void intercambiarNumero(int *numero1, int *numero2) {
    int auxiliar;

    auxiliar = *numero1; 
    *numero1 = *numero2;  
    *numero2 = auxiliar; 
}