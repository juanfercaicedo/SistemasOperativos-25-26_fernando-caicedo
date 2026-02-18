# Teoría 

- Identificador puede estar compuesto de cualquier combinación de:
    - Letras(Minúsculas, mayúsculas)
        - Salvo letras con tile, ñ, ç 
    - dígitos
    - el símbolo subrayado `_`

# 📘 Tipos de Variables en C

En C, las variables se utilizan para almacenar datos en memoria.  
Cada variable debe declararse indicando su tipo.

---

## 🔹 Tipos de datos básicos en C

### 1️⃣ char
Almacena un solo carácter.

```c
char letra = 'A';
```

- Ocupa generalmente 1 byte
- También puede almacenar valores numéricos pequeños (código ASCII)

---

### 2️⃣ short int
Entero corto.

```c
short int numero = 10;
```

- Generalmente ocupa 2 bytes
- Rango aproximado:
  - -32,768 a 32,767 (con signo)

También puede escribirse simplemente como:
```c
short numero;
```

---

### 3️⃣ int
Entero estándar.

```c
int edad = 25;
```

- Generalmente ocupa 4 bytes
- Rango aproximado:
  - -2,147,483,648 a 2,147,483,647

---

### 4️⃣ long int
Entero largo.

```c
long int poblacion = 8000000;
```

- Generalmente 4 u 8 bytes (depende del sistema)
- Mayor capacidad que `int`

También puede escribirse:
```c
long poblacion;
```

---

### 5️⃣ long long int
Entero muy grande.

```c
long long int numero_grande = 9000000000;
```

- Generalmente 8 bytes
- Permite números mucho más grandes

---

### 6️⃣ float
Número decimal de precisión simple.

```c
float precio = 19.99;
```

- Generalmente 4 bytes
- Precisión aproximada de 6-7 cifras decimales

---

### 7️⃣ double
Número decimal de doble precisión.

```c
double pi = 3.1415926535;
```

- Generalmente 8 bytes
- Mayor precisión que `float`

---

### 8️⃣ long double
Número decimal de mayor precisión.

```c
long double numero_preciso = 3.141592653589793;
```

- Más precisión que `double`
- Tamaño depende del sistema

---

## 🔹 Variables con signo y sin signo

Muchos tipos enteros pueden ser:

### signed (con signo)
Permite números negativos y positivos.

```c
signed int numero = -10;
```

### unsigned (sin signo)
Solo permite números positivos.

```c
unsigned int numero = 10;
```

Ejemplo:
```c
unsigned int edad = 30;
```

---

## 🔹 Resumen rápido

| Tipo | Uso principal |
|------|--------------|
| char | Un carácter |
| short | Entero pequeño |
| int | Entero estándar |
| long | Entero grande |
| long long | Entero muy grande |
| float | Decimal simple |
| double | Decimal más preciso |
| long double | Decimal de alta precisión |

---

## 🔹 Ejemplo completo

```c
#include <stdio.h>

int main() {
    char letra = 'A';
    int edad = 25;
    float altura = 1.75;
    double pi = 3.1416;

    printf("Letra: %c\n", letra);
    printf("Edad: %d\n", edad);
    printf("Altura: %.2f\n", altura);
    printf("Pi: %lf\n", pi);

    return 0;
}
```

---

## 🔹 Nota importante

El tamaño exacto en bytes puede variar dependiendo del sistema operativo y la arquitectura (32 bits o 64 bits).

# 📘 Tipos de Variables en C

En C, las variables se utilizan para almacenar datos en memoria.  
Cada variable debe declararse indicando su tipo.

---

## 🔹 Tipos de datos básicos en C

### 1️⃣ char
Almacena un solo carácter.

```c
char letra = 'A';
```

- Ocupa generalmente 1 byte
- También puede almacenar valores numéricos pequeños (código ASCII)

---

### 2️⃣ short int
Entero corto.

```c
short int numero = 10;
```

- Generalmente ocupa 2 bytes
- Rango aproximado:
  - -32,768 a 32,767 (con signo)

También puede escribirse simplemente como:
```c
short numero;
```

---

### 3️⃣ int
Entero estándar.

```c
int edad = 25;
```

- Generalmente ocupa 4 bytes
- Rango aproximado:
  - -2,147,483,648 a 2,147,483,647

---

### 4️⃣ long int
Entero largo.

```c
long int poblacion = 8000000;
```

- Generalmente 4 u 8 bytes (depende del sistema)
- Mayor capacidad que `int`

También puede escribirse:
```c
long poblacion;
```

---

### 5️⃣ long long int
Entero muy grande.

```c
long long int numero_grande = 9000000000;
```

- Generalmente 8 bytes
- Permite números mucho más grandes

---

### 6️⃣ float
Número decimal de precisión simple.

```c
float precio = 19.99;
```

- Generalmente 4 bytes
- Precisión aproximada de 6-7 cifras decimales

---

### 7️⃣ double
Número decimal de doble precisión.

```c
double pi = 3.1415926535;
```

- Generalmente 8 bytes
- Mayor precisión que `float`

---

### 8️⃣ long double
Número decimal de mayor precisión.

```c
long double numero_preciso = 3.141592653589793;
```

- Más precisión que `double`
- Tamaño depende del sistema

---

## 🔹 Variables con signo y sin signo

Muchos tipos enteros pueden ser:

### signed (con signo)
Permite números negativos y positivos.

```c
signed int numero = -10;
```

### unsigned (sin signo)
Solo permite números positivos.

```c
unsigned int numero = 10;
```

Ejemplo:
```c
unsigned int edad = 30;
```

---

## 🔹 Resumen rápido

| Tipo | Uso principal |
|------|--------------|
| char | Un carácter |
| short | Entero pequeño |
| int | Entero estándar |
| long | Entero grande |
| long long | Entero muy grande |
| float | Decimal simple |
| double | Decimal más preciso |
| long double | Decimal de alta precisión |

---

## 🔹 Ejemplo completo

```c
#include <stdio.h>

int main() {
    char letra = 'A';
    int edad = 25;
    float altura = 1.75;
    double pi = 3.1416;

    printf("Letra: %c\n", letra);
    printf("Edad: %d\n", edad);
    printf("Altura: %.2f\n", altura);
    printf("Pi: %lf\n", pi);

    return 0;
}
```

---

## 🔹 Nota importante

El tamaño exacto en bytes puede variar dependiendo del sistema operativo y la arquitectura (32 bits o 64 bits).

- Más recursos teóricos:
    1. [Primer Código en C](./PrimerasClases/prueba.c)
    2. [Comandos](./PrimerasClases/README.md)
    3. [printf](./PrimerasClases/documentacion.md)
    4. [Código printf](./PrimerasClases/002printf.c)
    
