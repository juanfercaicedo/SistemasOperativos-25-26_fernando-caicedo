# Señales
* Las señales son interrupciones de software asíncronas que el sistema operativo u otro proceso envía a un programa en ejecución para notificarle que ha ocurrido un evento importante.
* Al ser "asíncronas", significa que pueden llegar en cualquier momento, interrumpiendo el flujo normal del programa.


## Estados y Acciones por Defecto
* Cuando un proceso recibe una señal, el sistema operativo pausa la ejecución normal del programa y busca qué hacer con ella. Hay tres formas en las que un programa puede reaccionar:
* Acción por defecto: Lo que hace el sistema si no programamos nada (suele ser terminar el proceso, ignorar la señal o pausarlo).
* Ignorar la señal: Le decimos explícitamente al sistema que no haga nada cuando llegue esa señal.
* Capturarla (Manejarla): Ejecutar una función específica (llamada Signal Handler o manejador de señales) escrita por nosotros para responder al evento.
* Nota importante: Hay dos señales que nunca se pueden ignorar ni capturar: SIGKILL (matar proceso forzosamente) y SIGSTOP (pausar proceso). Esto es un mecanismo de seguridad del sistema operativo.

## Señales más comúnes

En C, las señales están definidas en la librería `<signal.h>`. Cada señal tiene un nombre (macro) y un número entero asociado:

| Nombre           | Número | Evento que la genera                                             | Acción por defecto          |
| :--------------- | :----: | :--------------------------------------------------------------- | :-------------------------- |
| `SIGINT`         |    2   | Interrupción por teclado (ej. presionar `Ctrl + C`).             | Termina el proceso.         |
| `SIGKILL`        |    9   | Cierre forzoso e inmediato del proceso.                          | Termina el proceso.         |
| `SIGSEGV`        |   11   | "Segmentation Fault". Acceso inválido a la memoria.              | Termina + *Core Dump*.      |
| `SIGTERM`        |   15   | Solicitud de terminación limpia (ej. comando `kill`).            | Termina el proceso.         |
| `SIGALRM`        |   14   | Temporizador finalizado (usado con la función `alarm()`).        | Termina el proceso.         |
| `raise()`        |    -   | Envía una señal al **mismo proceso** que la invoca.              | Depende de la señal enviada |
| `kill()`         |    -   | Envía una señal a un **proceso (PID)** específico.               | Depende de la señal enviada |
| `pthread_kill()` |    -   | Envía una señal a un **hilo (thread)** dentro del mismo proceso. | Depende de la señal enviada |

---

### 4. ¿Cómo manejar señales en C?
Para capturar una señal, necesitas la librería `<signal.h>`. Existen dos funciones principales para esto:
* `signal()`: Es la forma clásica y más sencilla, aunque no se recomienda para programas complejos porque su comportamiento puede variar entre distintos sistemas operativos.
* `sigaction()`: Es el estándar moderno POSIX. Es mucho más robusta, permite bloquear otras señales mientras se maneja una y ofrece mayor control.

**Ejemplo básico usando `signal()`:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> // Para señales
#include <unistd.h> // Para la función sleep()
#include <stdbool.h> // Para utilizar booleanos dentro de C.

// 1. Creamos la función manejadora
void mi_manejador(int num_señal) {
    printf("\n¡He recibido la señal %d (SIGINT)!\n", num_señal);
    printf("Guardando datos y saliendo de forma segura...\n");
    exit(0); // Terminamos el programa de forma controlada
}

int main() {
    // 2. Asociamos la señal SIGINT a nuestro manejador
    signal(SIGINT, mi_manejador);

    printf("Programa en ejecución. Presiona Ctrl+C para interrumpir.\n");

    // Bucle infinito para mantener el programa vivo
    while(true) {
        printf("Trabajando...\n");
        sleep(2);
    }

    return 0;
}
```

---

### 5. ¿Cómo enviar señales desde C?
Un proceso también puede generar señales, ya sea para sí mismo o para otros procesos (si tiene los permisos necesarios):
* `raise(int sig)`: El programa se envía una señal a sí mismo.
* `kill(pid_t pid, int sig)`: Envía una señal a un proceso específico usando su identificador de proceso (PID).