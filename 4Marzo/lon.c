#include<stdio.h>
#include<limits.h>
#include<string.h>

int mi_strlen(char *str);

int main(void){
    char cadena[150];
    puts("Introduce una cadena: ");
    fgets(cadena, sizeof(cadena), stdin);  //stdin(Standard input), puede ser reemplazado por un 0.
    printf("La longuitud de la cadena es de %d caracteres \n", mi_strlen(cadena));
    return 0;
}

int mi_strlen(char *str){
    int contador = 0;
    while (str[contador] != '\0'){ //*str es un puntero, el cual toma el valor de cadena del método main; con esto se ocupa contador como índice
        contador ++;
    }
    return contador-1;
}