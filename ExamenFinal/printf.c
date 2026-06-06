#include <stdio.h>

int suma(int x, int y) {
    return x + y;
}

int main(void) {
    int x, y;
    puts("Introduce un número: ");
    scanf("%d", &x);
    puts("Ahora introduce otro número: ");
    scanf("%d", &y);

    printf("La suma de x e y es de: %i \n", suma(x, y));
}
