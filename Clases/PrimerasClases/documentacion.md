# 📘 Mostrar Variables con printf en C

La función `printf` se utiliza para mostrar información en pantalla.

Se encuentra en la librería:

```c
#include <stdio.h>
```

---

# 🔹 Sintaxis básica

```c
printf("texto y formato", variables);
```

Ejemplo:

```c
int edad = 25;
printf("Mi edad es %d\n", edad);
```

---

# 🔹 Especificadores de formato

Cada tipo de dato necesita un especificador diferente.

| Tipo de dato      | Especificador | Ejemplo |
|------------------|--------------|----------|
| char (carácter)  | %c           | printf("%c", letra); |
| int              | %d o %i      | printf("%d", numero); |
| short            | %hd          | printf("%hd", numero); |
| long             | %ld          | printf("%ld", numero); |
| long long        | %lld         | printf("%lld", numero); |
| unsigned int     | %u           | printf("%u", numero); |
| float            | %f           | printf("%f", numero); |
| double           | %lf          | printf("%lf", numero); |
| long double      | %Lf          | printf("%Lf", numero); |
| string (cadena)  | %s           | printf("%s", texto); |

---

# 🔹 Ejemplos prácticos

```c
#include <stdio.h>

int main() {
    char letra = 'A';
    int edad = 25;
    float altura = 1.75;
    double pi = 3.141592;

    printf("Letra: %c\n", letra);
    printf("Edad: %d\n", edad);
    printf("Altura: %f\n", altura);
    printf("Pi: %lf\n", pi);

    return 0;
}
```

---

# 🔹 Controlar decimales

Puedes indicar cuántos decimales mostrar:

```c
float precio = 19.9876;
printf("%.2f\n", precio);
```

Salida:
```
19.99
```

Explicación:
- `.2` → muestra 2 decimales

---

# 🔹 Mostrar varias variables en una sola línea

```c
int edad = 25;
float altura = 1.75;

printf("Edad: %d y Altura: %.2f\n", edad, altura);
```

⚠ IMPORTANTE:
El orden de las variables debe coincidir con el orden de los especificadores.

---

# 🔹 Caracteres especiales útiles

| Código | Significado |
|--------|------------|
| \n     | Nueva línea |
| \t     | Tabulación |
| \\     | Barra invertida |
| \"     | Comillas |

Ejemplo:

```c
printf("Hola\nMundo\n");
```

---

# 🔹 Error común

Incorrecto:

```c
int edad = 25;
printf("%f", edad);  // ❌ Error de tipo
```

Correcto:

```c
printf("%d", edad);  // ✅
```

---

# 🔹 Resumen rápido

- `%d` → enteros
- `%f` → decimales
- `%c` → caracteres
- `%s` → cadenas
- `\n` → salto de línea
- `%.2f` → controlar decimales

---

# 🚀 Recomendación

Compila siempre con advertencias activadas:

```bash
gcc -Wall -Wextra -std=c11 archivo.c -o programa
```

Te ayudará a detectar errores en `printf`.
