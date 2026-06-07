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
