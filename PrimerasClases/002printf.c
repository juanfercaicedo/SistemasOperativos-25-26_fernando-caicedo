#include <stdio.h>

int suma(int x, int y); // Esto es una declaración (prototipo).
						// Es necesario porque main() usa suma() antes de que esté definida.

int main(void)
{
	int x = 5, y = 6;
	
	printf("x vale %i, y vale %i y su suma %i \n", x, y, suma(x,y));
	
	return 0;
}

int suma(int x, int y)
{
	return x+y;
}
