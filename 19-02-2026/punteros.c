#include <stdio.h>

int main(void)
{
	int numero = 8;
	int *p; // estamos creado un puntero
	
	p=&numero;
	
	printf("El número vale %d y se encuentra en %p\n", *p, &p);
	return 0;
}	

// formato puntero 
// & utilizamos cuando ocupamos la función scanf, nos devuelve la dirección de memoria
