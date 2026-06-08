# Notas para el examen 🧐
## Formas de declarar métodos
- El código se compila de arriba para abajo. Por ende, si ocupamos una función en el main que la desarrollamos más abajo, el compilador no la conocerá y nos va a dar un error. Para esto tenemos dos soluciones:
    - Crear un método prototipo (Declararlo al inicio):
    ```c
        int suma(int , int);
        int main(void) {
            int x, y;
            printf("La suma es de: ", suma(x, y))

        }

        int suma(int x, int y) {
            return x + y;
        }
    ```
    - O solo simplemente desarrollamos el método antes que el main
---
## Formas de declarar variables 👨🏻‍🏫
| Tipo de dato      | Especificador | Ejemplo |
|------------------|--------------|----------|
| char (carácter)  | %c           | printf("%c", &letra); |
| int              | %d o %i      | printf("%d", &numero); |
| short            | %hd          | printf("%hd", &numero); |
| long             | %ld          | printf("%ld", &numero); |
| long long        | %lld         | printf("%lld", &numero); |
| unsigned int     | %u           | printf("%u", &numero); |
| float            | %f           | printf("%f", &numero); |
| double           | %lf          | printf("%lf", &numero); |
| long double      | %Lf          | printf("%Lf", &numero); |
| string (cadena)  | %s           | printf("%s", &texto); |
| hexadecimals numbers  | %p      | printf("%d", &texto); |
---
## Punteros
- Los punteros son direcciones de memoria
- Se declaran de la siguiente manera: 
```c
    int main(void) {
        int myNumbers[4] = {1, 2, 3, 4};
        int *p;
        *p = myNumbers; // *p apuntara a myNumbers[0]
    }
```
- `*p` apuntará a un valor, por el otro lado p, apuntará a una dirección de memoria
---
## Procesos fork y procesos hijos 🧑‍🧒‍🧒
- Un `fork()` copia todo lo que está delante de él
- Un hijo se declara de la siguiente manera: 
```c
    int main(void) {
        pid_t hijo;
        hijo = fork();
    }
```
- `pid_t` es un tipo de variable
- el hijo es creado cuando hacemos `hijo` = fork();
- El hijo debe morir antes que el padre, si el padre muere antes se hacen procesos fantasmas
- Esto se soluciona con `wait()`
```c
    if(hijo > 0) {
        printf("Soy el padre con un PID: %d y estoy esperando a que mi hijo con un PID: %d termine\n", getpid(), (int)hijo);
        wait(&estado); // espera a que el hijo termine
        if(WIFEXITED(estado)) {
            int resultadoHijo = WEXITSTATUS(estado);
            if(resultadoHijo == 0) {
                puts("El número es PAR \n");
            } else {
                puts("El número es IMPAR \n");
            }
        } else {
            puts("El hijo ha acabado de manera anomala \n");
        }
    }
```
- `WIFEXITED(estado)`: Comprueba como murio el hijo, con un exit() o un return()
    - Es verdadero o falso, si es verdadero el hijo murio por su voluntad
    - Si es falso el proceso murio de forma anómala
- `WEXITSTATUS(estado)`: Extra el valor con el que murió el hijo
---
## Tuberías 💩
- Se la declara antes que del `fork()`
- Siempre que creamos una tubería debemos crear una variable buffer para guardar los datos temporalmente
```c
    int main(void) {
        int mi_tuberia[2];
        char buffer[100];
        pipe(mi_tuberia);
    }
```
- Para leer en una tuberia hacemos:
    ```c
    close(mi_tuberia[1]); // tuberia de escritura
    read(mi_tuberia[0], buffer, sizeof(buffer));
    close(mi_tuberia[0]);
    ```
- En cambio para escribir en una tubería:
    ```c
    close(mi_tuberia[0]); // tuberia de lectura
    read(mi_tuberia[1], buffer, sizeof(buffer));
    close(mi_tuberia[1]);
    ```
- Igual que en todo proceso, el padre tiene que esperar a que su hijo muera, lo hacemos con:
    - `wait(NULL);`
    - Con este wait el padre siempre esperará a que el hijo acabe su proceso
- El hijo lee una tubería y el padre escribe en ella
- Si un padre tiene más de un hijo, debemos crear una tubería por hijo
    - `wait(NULL);` solo espera a un hijo
    - Entonces para que el padre espere a todos sus hijos debe haber la misma cantidad de wait(NULL) como de hijos
---
## Llamadas al sistema 📱
- `strcmp`: String compare, compara cadenas caracter por caracter
- Si son iguales devuelve un `0`
- `strcat`: String concatenate, une dos cadenas de texto 
- `execlp`: *exec*, *list*, *path*, Reemplaza el proceso actual por un programa nuevo
---
## mmap (Memory Map / Memoria compartida)
- Kernel reserva un espacio de memoria virtual
- El objetivo es que un padre y un hijo compartan memoria, de esta forma cuando un hijo haga un cambio, el padre también lo tendrá
- Necesitamos la librería `<sys/mman.h>`
- Declaramos la variable de memoria compartida de la siguiente forma:
```c
    static int *variable_compartida;

    int main(void){
        variable_compartida = mmap(NULL, sizeof(*variable_compartida), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1,0);
    }
```
- Siempre debemos declarar la memoria compartida antes de hacer un `fork()`
- Siempre que ocupemos `mmap`, siempre al acabar tenemos que limpiar la memoria, lo hacemos mediante: `munmap`
- Tenemos que liberar la memoria tanto del lado del padre como del hijo
---
## Semáforos 🚦
- Un semáforo es un mecanismo de sincronización que sirve para controlar el acceso a recursos compartidos" 
- Controla el acceso a la memoria compartida
- Necesitaremos utilizar las librerias: `semaphore.h` y `fcntl.h`
- Al igual que la memoria compartida, el semáforo lo debemos declarar antes que el fork();
- Lo declaramos de la siguiente manera:
```c
    sem_t *semaforo = sem_open("/mi_semaforo", O_CREAT, S_IRUSR | S_IWUSR, 1);
```
- `sem_wait()` Cierra el semáforo
- `sem_post()` Abre el flujo del semáforo
- Tiene que ir en la sección crítica, es decir cuando modificamos el valor de la variable compartida
- Al igual que con la memoria compartida, debemos cerrar el semáforo una vez haya acabado su función, lo hacemos mediante `sem_close()`
- Y también eliminamos la clave del sistema con: `sem_unlink("/mi_semaforo);`
---
## Hilos 🧵
- Unidad básica de utilización dentro del CPU
- Un hilo es como un fork(), la diferencia es que no necesitamos de mmap, ya que ya comparte memoria
- Lo declaramos de la siguiente manera:
```c
    pthread_t nombre_variable;
```
- `pthread_create(&nombre_variable, NULL, &nuevo_hilo, NULL);`: Crea un nuevo hilo
- `pthread_self()`: Nos da el ID del hilo
- `pthread_join()`: Es el equivalente del wait() en un `fork()`
- Los métodos que ejecutan un hilo siempre deben tener esta estructura:
```c
    void* hilo(void *arg) {
    }
```
- `pthread_mutex()`: Mutal Exclusion
- Controla el flujo
    - Solo puede acceder uno a la vez
    - `pthread_mutex()`-> Puede estar libre u ocupado
- Lo declaramos de la siguente manera:
```c
pthread_mutex_t nombreVariable;
```
- Lo inicializamos de la siguiente manera:
```c
    pthread_mutex_init(&nombreVariable, NULL);
```
- Ahora siempre vamos a cerrar la "puerta" en cuando vayamos a entrar a una zona crítica, si hay otro hilo ocupodo `mutex` esperará a que se desocupe
```c
    pthread_mutex_lock(&nombreVariable);
```
- Después de haber modificado la zona crítica, como una variable compartida, tenemos que abrir el mutex
```c
    pthread_mutex_unlock(&nombreVariable);
```
- Por último al igual que la memoria compartida, debemos liberar el espacio una vez hayamos acabado
```c
    pthread_mutex_destroy(&nombreVariable);
```
---
## Señales 📶
- Interrumpen un proceso
- Las 4 señales más usadas son:
    1. `SIGINT`: (*Signal Interrupt*): Es la señal que se envía cuando el usuario pulsa Ctrl + C en la consola. Por defecto, su trabajo es matar al proceso educadamente.
    2. `SIGKILL`: (*Signal Kill*): Mata a un proceso
    3. `SIGALRM`: (*Signal Alarm*): Le pide al sistema que le mande una señal, como una alarma temporal
    4. `SIGUSR1` y `SIGUSR2`: El sistema operativo no les tiene una tarea asignada, su función las determina el programador.
- Para utilizar señales necesitamos la librería `<signal.h>`
- Tenemos que utilizar un método para la señal en caso de que utilicemos SIGUSR1 y SIGUSR2, lo hacemos de la siguiente manera:
```c
void manejadorSeñal(int signum);

int main(void) {
    signal(SIGUSR1, manejadorSeñal);
}
```
---
## Notas generales
- Es mejor utilizar `fgets` en vez de `scanf` cuando estamos tratando con una cadena de caractéres, como puede ser una oración
- Para lograr obtener un número aleatorio debemos ocupar la librería `<time.h>` y lo hacemos de la siguiente manera:
```c
    srand(time(NULL));
    for (int i = 0; i < 10; i++) {
        int numeroAleatorio = rand() % 100;
        printf("%d.- %d\n", i + 1, numeroAleatorio);
    }
```
- En tuberías cuando estamos ocupando arrays como conjunto de datos, no es suficiente dar el valor(tamaño del array), debemos declara el valor de los elementos del array, esto se hace mediante: 
    - `SIZE * sizeof(int);`
    - Eso en caso de que sea un entero
