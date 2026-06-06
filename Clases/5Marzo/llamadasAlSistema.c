#include <unistd.h>

int main(void){
    char nombre[100];
    char edad[100];

    write(1, "Introduce tu nombre: ", sizeof("Introduce tu nombre: ") - 1);
    write(1, "Tu nombre es: ", sizeof("Tu nombre es: ") - 1);
    int n = read(0, nombre, sizeof(nombre));
    write(1, nombre, n);

    write(1, "Introduce tu edad: ", sizeof("Introduce tu edad: ") - 1);
    int c = read(0, edad, sizeof(edad));
    write(1, "Tu edad es: ", sizeof("Tu edad es: ") - 1);
    write(1, edad, c);

    return 0;
}

// 0 teclado
// 1 pantalla
// 2 stderr standard error

