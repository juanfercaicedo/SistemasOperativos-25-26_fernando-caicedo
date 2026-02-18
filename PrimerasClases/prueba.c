#include <stdio.h>

void kk ()
{
		puts("Otra función para sacar cosas de C\n");
		return;
}

int main(void)
{
	printf("Hola Mundo, es mi primer programa en C\n");
	kk();
	return 0;
}


// Cuando main llama a una función, esa función debe ser declarada antes de que sea compilada
