/*
Comunicación entre procesos con memoria compartida anónima (mmap)
El hijo calcula los 10 primeros números de Fibonacci y los escribe
en la memoria compartida. El padre los lee tras esperar al hijo y los 
saca por pantalla
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>


int main(void){
    
}