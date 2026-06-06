#include <stdio.h>

int main(void){
	int myNumbers [4] = {25, 50, 75, 100};
	int *ptr = myNumbers;
	int i;
	printf("%p\n", ptr);

	
	/*
	printf("%p\n", myNumbers);
	printf("%p\n", &myNumbers[0]); // & "operador de dirección"
	printf("%p\n", &myNumbers[1]);
	printf("%d\n", *myNumbers); // "*" ve el valor dentro de una dirección de memoria
	*/
		
	for(i = 0; i<4; i++){
		printf("%p o también %p\n", (ptr+1), &myNumbers[i]);
	}
	printf("%p\n", ptr);
	
	return 0;
}
