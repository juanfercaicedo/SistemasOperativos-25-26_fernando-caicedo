# Memoria Compartida
## ¿Qué estamos haciendo realmente?

Cuando ejecutas `mmap` con esos parámetros, pedimos al Kernel del sistema operativo que reserve un espacio de memoria virtual que sea "especial". A diferencia de la memoria normal de un proceso (que es privada), esta zona es **heredable** y **común**.

### Anatomía de la llamada
```c
variable_compartida = mmap(
    NULL,                   // 1. Dirección de inicio
    sizeof(int),            // 2. Longitud
    PROT_READ | PROT_WRITE, // 3. Protecciones
    MAP_SHARED | MAP_ANONYMOUS, // 4. Banderas (Flags)
    -1,                     // 5. File Descriptor
    0                       // 6. Offset -> Desplazamiento (Si no hay fichero no hay desplazamiento)
);
```

### 1. El `NULL` (La dirección)
- **Como lo tienes:** `NULL` significa que el Sistema Operativo elige dónde poner la memoria. Es lo más seguro y recomendado.
- **Tu duda:** Si quieres una dirección concreta, pones un puntero ahí. **Pero ojo:** El SO puede ignorar tu sugerencia si esa dirección no es válida o ya está ocupada, a menos que uses el flag `MAP_FIXED` (lo cual es peligroso y poco común).

### 2. Los Flags: El "truco" de la compartición
Aquí es donde ocurre la magia:
* **`MAP_ANONYMOUS`**: Indica que no hay un archivo físico en el disco respaldando esta memoria. Es solo RAM pura. Por eso el *File Descriptor* se pone en `-1`.
* **`MAP_SHARED`**: Es el flag crucial. Dice que los cambios en esta memoria son visibles para otros procesos. 

> [!IMPORTANT]
> **La Herencia:** Para que esto funcione entre procesos, el `mmap` debe hacerse **antes** de un `fork()`. Cuando el proceso padre crea al hijo, ambos comparten el mismo espacio de memoria física gracias a este mapeo.

---

## Resumen de conceptos clave

| Parámetro | Propósito | Explicación sencilla |
| :--- | :--- | :--- |
| **`PROT_READ \| PROT_WRITE`** | Permisos | "Quiero poder leer y escribir en este trozo de memoria". |
| **`MAP_ANONYMOUS`** | Sin archivo | "No quiero guardar esto en un archivo, solo quiero un hueco en la RAM". | (La dirección de memoria no está basada en un fichero)
| **`MAP_SHARED`** | Compartir | "Si yo cambio un valor, mi hijo (proceso fork) también verá el cambio". |

---

## ¿Por qué usar esto y no una variable global?

Es una confusión común. Si declaras `int x = 0;` global y luego haces un `fork()`:
1. El hijo recibe una **copia** de `x`.
2. Si el hijo hace `x = 10;`, el padre **sigue viendo 0**. 

Con `mmap`, ambos procesos apuntan a la **misma dirección física** de la RAM. Es un "teléfono directo" entre ellos.

---

## Función `munmap`

La función `munmap` (abreviatura de *memory unmap*) se utiliza para eliminar el mapeo de un rango de direcciones de memoria en el espacio de direcciones virtuales del proceso actual.

### 1. Sintaxis de la Línea
```c
munmap(variable_compartida, sizeof(variable_compartida));
```

### 2. Análisis de Parámetros

| Parámetro | Tipo | Descripción |
| :--- | :--- | :--- |
| `variable_compartida` | `void *addr` | Es el **puntero** que apunta al inicio de la región de memoria que deseas liberar. Generalmente es la dirección devuelta previamente por una llamada exitosa a `mmap`. |
| `sizeof(variable_compartida)` | `size_t length` | Especifica el **tamaño en bytes** del área que se va a desenlazar. En este caso, se usa `sizeof` para asegurar que se libera exactamente el tamaño que ocupa la variable. |

---

### 3. ¿Qué hace exactamente?

1.  **Finaliza el acceso:** Una vez ejecutada esta línea, cualquier intento de acceder a la dirección de memoria contenida en `variable_compartida` provocará un error de segmentación (**Segmentation Fault**), ya que esa memoria ya no le pertenece al proceso.
2.  **Sincronización:** Si la memoria fue mapeada con el flag `MAP_SHARED`, los cambios realizados se escriben de vuelta en el archivo o objeto subyacente (si aplica) antes de que el mapeo desaparezca.
3.  **Liberación de recursos:** Informa al kernel del sistema operativo que esas páginas de memoria física pueden ser reutilizadas para otros fines.

### 4. Importancia en Memoria Compartida
Si estás trabajando con **IPC (Inter-Process Communication)**, esta línea es el "cierre" de la ventana de comunicación. Mientras `mmap` crea el puente entre dos procesos, `munmap` destruye el puente del lado del proceso que lo ejecuta.

---

### 5. Recomendaciones de Seguridad
Es una buena práctica verificar si la función tuvo éxito, ya que, aunque es raro, podría fallar si los parámetros son inválidos.

```c
if (munmap(variable_compartida, sizeof(variable_compartida)) == -1) {
    perror("Error al ejecutar munmap");
    // Manejo de error
}
```

> **Nota importante:** `munmap` no borra los datos físicamente de la RAM de inmediato por razones de rendimiento, simplemente invalida el permiso del proceso para leer o escribir en esa zona.