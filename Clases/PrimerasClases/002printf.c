#include <stdio.h>

int suma(int , int ); // Esto es una declaración (prototipo).
						// Es necesario porque main() usa suma() antes de que esté definida.

int main(void)
{
	int x , y;
	puts("Introduce el valor de la primera variable:");
	scanf("%d", &x);
	puts("Introduce el valor de la segunda variable:");
	scanf("%d", &y);

	printf("x vale %i, y vale %i y su suma %i \n", x, y, suma(x,y));
	
	return 0;
}

int suma(int x, int y)
{
	return x+y;
}
