# SistemasOperativos-25-26
- C es un lenguaje veloz
- Es un lenguaje sensible

## Comandos de C
# 📘 Guía de Comandos C (gcc)

Guía rápida de comandos básicos para compilar y ejecutar programas en C usando gcc.

---

### 🔹 1. Compilar un programa

```bash
gcc archivo.c -o programa
```

Qué hace:
- `archivo.c` → archivo fuente
- `-o programa` → nombre del ejecutable generado

Ejemplo:
```bash
gcc prueba.c -o prueba
```

Ejecutar:
```bash
./prueba
```

---

### 🔹 2. Compilar mostrando advertencias

```bash
gcc -Wall archivo.c -o programa
```

- `-Wall` → muestra advertencias importantes

Recomendado:
```bash
gcc -Wall prueba.c -o prueba
```

---

### 🔹 3. Compilación más estricta

```bash
gcc -Wall -Wextra archivo.c -o programa
```

Aún más estricto:
```bash
gcc -Wall -Wextra -Werror archivo.c -o programa
```

- `-Wextra` → más advertencias
- `-Werror` → convierte advertencias en errores

---

### 🔹 4. Especificar estándar de C

```bash
gcc -std=c99 archivo.c -o programa
gcc -std=c11 archivo.c -o programa
gcc -std=c17 archivo.c -o programa
```

Recomendado actualmente:
```bash
gcc -std=c11 archivo.c -o programa
```

---

### 🔹 5. Generar solo archivo objeto (.o)

```bash
gcc -c archivo.c
```

Genera:
```
archivo.o
```

No crea ejecutable todavía.

---

### 🔹 6. Enlazar archivos objeto

```bash
gcc archivo1.o archivo2.o -o programa
```

Se usa cuando el proyecto tiene varios archivos fuente.

---

### 🔹 7. Compilar varios archivos directamente

```bash
gcc archivo1.c archivo2.c -o programa
```

---

### 🔹 8. Ejecutar un programa

```bash
./programa
```

---

### 🔹 9. Ver versión de gcc

```bash
gcc --version
```

---

### 🔹 10. Borrar ejecutables u objetos

Borrar ejecutable:
```bash
rm programa
```

Borrar archivos objeto:
```bash
rm *.o
```

---


# 🚀 BONUS: Makefile básico

Crear archivo llamado `Makefile` con este contenido:

```makefile
programa: main.c
	gcc -Wall -Wextra -std=c11 main.c -o programa
```

Luego compilar solo con:
```bash
make
```


