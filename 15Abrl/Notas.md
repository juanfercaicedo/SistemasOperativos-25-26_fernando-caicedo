## Semaforos
- Protegen en la parte más crítica del código
    - Cuando cambiamos el valor de la variable compartida
- Librerías necesarias: 
```c
#include <semaphore.h>
#include <fcntl.h>

```

# 🔐 Semáforos en C

## 🧠 ¿Qué es un semáforo?

Un **semáforo** es un mecanismo de sincronización que sirve para **controlar el acceso a recursos compartidos** cuando hay varios procesos o hilos.

👉 Evita problemas como:

* condiciones de carrera (*race conditions*)
* datos inconsistentes
* accesos simultáneos peligrosos

---

## 🎯 ¿Para qué se utilizan?

Se usan cuando:

* varios procesos acceden a la **misma variable o memoria**
* hay que proteger una **sección crítica**

👉 Ejemplo típico:

```c
contador++;
```

Si dos procesos hacen esto a la vez → resultado incorrecto ❌

Con semáforo → acceso ordenado ✅

---

## ⚙️ ¿Cómo funcionan?

Un semáforo tiene un valor entero interno.

### Operaciones principales:

### 🔻 `sem_wait()`

* **Decrementa** el semáforo
* Si el valor es 0 → el proceso **se bloquea**
* También se conoce como **P()**

```c
sem_wait(semaforo);
```

---

### 🔺 `sem_post()`

* **Incrementa** el semáforo
* Desbloquea a otro proceso si estaba esperando
* También se conoce como **V()**

```c
sem_post(semaforo);
```

---

## 🔒 Sección crítica

Es la parte del código donde accedes a recursos compartidos.

```c
sem_wait(semaforo);

// 🔴 SECCIÓN CRÍTICA
variable_compartida++;

sem_post(semaforo);
```

---

## 📚 Librerías necesarias

```c
#include <semaphore.h>
#include <fcntl.h>
```

---

## 🧾 Sintaxis correcta

```c
sem_t *semaforo;

semaforo = sem_open("/mi_semaforo", O_CREAT, S_IRUSR | S_IWUSR, 1);
```

### Parámetros:

* `"/mi_semaforo"` → nombre (SIEMPRE empieza con `/`)
* `O_CREAT` → crea el semáforo si no existe
* `S_IRUSR | S_IWUSR` → permisos (lectura/escritura)
* `1` → valor inicial

---

## 🧹 Liberación de recursos

Muy importante:

```c
sem_close(semaforo);
sem_unlink("/mi_semaforo");
```

* `sem_close` → cierra en el proceso
* `sem_unlink` → elimina del sistema

---

- [Ejemplo en código](../9Abril/sumaResta.c)