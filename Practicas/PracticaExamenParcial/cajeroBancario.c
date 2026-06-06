/*
Crear un programa en C que simule a un Cliente (Padre) enviando múltiples transacciones a un Cajero Automático (Hijo). 
El Cajero deberá procesar estas transacciones actualizando un saldo compartido de forma segura, y reportar al Cliente al terminar.
Instrucciones paso a paso:
Preparación (Recursos):
El proceso principal (Padre) debe mapear una zona de memoria compartida anónima (mmap) que contenga un único número entero. Este será el saldo de la cuenta y debe inicializarse en $1000.
El Padre debe crear un semáforo (con sem_open) inicializado a 1 para proteger las modificaciones del saldo.
El Padre debe crear una tubería (pipe) para enviar datos al hijo.
Creación de Procesos:
El Padre realiza un fork() para crear al proceso Hijo (el Cajero).
Comportamiento del Padre (El Cliente):
Debe pedirle al usuario por teclado: "¿Cuántas transacciones deseas generar?" (guardar en un entero N).
Genera un array de N números enteros aleatorios (pueden ser depósitos positivos o retiros negativos, usa rand()).
Envía el array de transacciones al Hijo a través de la tubería.
Cierra los extremos de la tubería que no use.
Se queda bloqueado esperando a que el Hijo termine usando wait(&estado).
Comportamiento del Hijo (El Cajero):
Lee el array de transacciones que le llega por la tubería.
Recorre el array. Por cada transacción:
Debe entrar a su sección crítica usando sem_wait().
Sumar el valor de la transacción al saldo guardado en la memoria compartida (mmap).
Salir de la sección crítica usando sem_post().
Mientras recorre el array, el Hijo debe llevar la cuenta de cuántos depósitos (transacciones mayores a 0) se procesaron en total.
Una vez aplicadas todas las transacciones, el Hijo termina su vida y devuelve el número de depósitos procesados usando exit(cantidad_depositos).
Evaluación y Limpieza Final (El Padre):
Cuando el Padre es despertado por la muerte de su hijo, debe usar sus "lupas" (WIFEXITED y WEXITSTATUS) para extraer el estado de salida del Hijo.
Debe imprimir por pantalla:
El saldo original ($1000).
El número de depósitos procesados reportados por el hijo.
El saldo final
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h> 
#include <stdlib.h>
#include <time.h>
#include <sys/mman.h>
#include <semaphore.h>
#include <fcntl.h>

static int *memoria_compartida;

int main(void) {
    pid_t hijo;
    sem_t *semaforo;
    int numeroTransacciones;
    int mi_tuberia[2];

    srand(time(NULL));

    memoria_compartida = mmap(NULL, sizeof(*memoria_compartida), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    *memoria_compartida = 1000;

    semaforo = sem_open("/mi_semaforo_cajero", O_CREAT, S_IRUSR | S_IWUSR, 1);

    puts("Introduzca el número de transacciones que desea hacer: ");
    scanf("%d", &numeroTransacciones);

    puts("Transacciones recibidas: ");
    int cantidadTransacciones[numeroTransacciones];
    for(int i = 0; i < numeroTransacciones; i++) {
        cantidadTransacciones[i] = (rand() % 201) - 100;
        printf("[%d]",cantidadTransacciones[i]);
    }

    printf("\n");

    pipe(mi_tuberia);

    hijo = fork();

    if(hijo < 0) {
        perror("Error en la creación del fork");
        exit(1);
    } else if (hijo == 0) { // Proceso del Hijo/Cajero
        int conteoTransacciones = 0;
        int conteoRetiros = 0;
        int numerosTransaccionesRecibidos[numeroTransacciones];
        close(mi_tuberia[1]);
        read(mi_tuberia[0], numerosTransaccionesRecibidos, sizeof(numerosTransaccionesRecibidos));
        close(mi_tuberia[0]);

        for(int i = 0; i < numeroTransacciones; i++) {
            sem_wait(semaforo); // siempre hacemos esto antes de cambiar el valor de la memoria_compartida
            *memoria_compartida += numerosTransaccionesRecibidos[i];
            sem_post(semaforo);

            if(numerosTransaccionesRecibidos[i] > 0){
                conteoTransacciones++;
            }

        }
        exit(conteoTransacciones);
    } else { // Proceso del Padre/Cliente
        int estado;
        int depositosRealizados;
        close(mi_tuberia[0]);
        write(mi_tuberia[1], cantidadTransacciones, sizeof(cantidadTransacciones));
        close(mi_tuberia[1]);

        wait(&estado);

        if(WIFEXITED(estado)) {
            depositosRealizados = WEXITSTATUS(estado);
            
            printf("\n--- REPORTE DEL CAJERO ---\n");
            printf("Saldo inicial de la cuenta: $1000\n");
            printf("La cantidad de depósitos procesados (mayores a 0) son: %d\n", depositosRealizados);
            
            printf("El saldo FINAL de la cuenta es: $%d\n", *memoria_compartida);
            
            printf("Las transacciones generadas fueron: ");
            for(int i = 0; i < numeroTransacciones; i++) {
                printf("[%d] ", cantidadTransacciones[i]);
            }
            printf("\n");
            
            munmap(memoria_compartida, sizeof(*memoria_compartida));
            sem_close(semaforo);
            sem_unlink("/mi_semaforo_cajero");
        }
    }
    return 0;
}