## Hilos
- `Hilo:` Es la unidad básica de utilización de CPU.
- Componentes:
    - ID de un hilo
    - Set de registros
    - Pila(stack)
- Comparte con el rest de hilo del mismo proceso de la sección de datos, la sección de texto y otros recursos del SO.
## Ejemplo en clase
- [Código hecho en clase](./hilos.c)    

## 🧵 Explicación del código de hilos en C

Este programa crea un **hilo secundario** usando la librería `pthread` y muestra por pantalla los identificadores del **proceso** y de los **hilos**.

---

## 🧠 Variables globales

```c
pthread_t ntid;
```

* `pthread_t` es el tipo de dato que representa un **hilo**
* `ntid` guardará el identificador del hilo creado

---

## 🖨️ Función `printids`

```c
void printids(const char *s){
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s pid %u tid %u\n", s, (unsigned int)pid, (unsigned int)tid);
}
```

Esta función:

* Obtiene el **ID del proceso** con `getpid()`
* Obtiene el **ID del hilo actual** con `pthread_self()`
* Imprime ambos junto con un mensaje

📌 Importante:

* Todos los hilos comparten el mismo **PID**
* Cada hilo tiene su propio **TID**

---

## 🧵 Función del nuevo hilo

```c
void* nuevo_hilo (void *arg) {
    printids("Nuevo hilo: ");
    return NULL;
}
```

Esta es la función que ejecutará el hilo secundario.

* Se ejecuta cuando se crea el hilo
* Simplemente imprime sus identificadores

---

## 🚀 Función `main`

```c
int main(void) {
    int error;

    error = pthread_create(&ntid, NULL, &nuevo_hilo, NULL);

    printids("Hilo principal: ");

    usleep(100);

    return 0;
}
```

### Paso a paso:

1. **Creación del hilo**

   ```c
   pthread_create(&ntid, NULL, &nuevo_hilo, NULL);
   ```

   * Crea un nuevo hilo
   * Ejecuta la función `nuevo_hilo`
   * Guarda el identificador en `ntid`

2. **El hilo principal también imprime**

   ```c
   printids("Hilo principal: ");
   ```

3. **Pequeña espera**

   ```c
   usleep(100);
   ```
   * Pausa el programa brevemente
   * Permite que el hilo secundario termine antes de que el programa finalice

---

## 📌 ¿Qué hace el programa?

* Crea un hilo secundario
* Tanto el hilo principal como el secundario:

  * Imprimen su PID (igual)
  * Imprimen su TID (diferente)
* Muestra cómo funcionan los hilos dentro de un mismo proceso

---

## 🧾 Ejemplo de salida

```text
Hilo principal:  pid 1234 tid 1001
Nuevo hilo:      pid 1234 tid 1002
```

👉 Observa:

* Mismo `pid`
* Distinto `tid`

---


