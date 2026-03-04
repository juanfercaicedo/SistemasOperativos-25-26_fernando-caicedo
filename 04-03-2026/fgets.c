#include <stdio.h>
#include <string.h>
#include <unistd.h>
#define SIZE 256

int main(void){
    char nombre[SIZE];
    printf("Escribe tus nombres y tus apellidos");
    fgets(nombre, SIZE, stdin); //stdin(Standard input), puede ser reemplazado por un 0.
    if((strlen(nombre)>0)&&nombre[strlen(nombre)-1]== '\n'){
        nombre[strlen(nombre)-1]='\0';
    }
    printf("Hola %s, igual y acabas aprobando sistemas operativos\n", nombre);
}