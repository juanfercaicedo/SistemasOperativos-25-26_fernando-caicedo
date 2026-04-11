# Consejos para el Examen
1. Cuando nos pidan hacer tuberías:
```c
int mi_tuberia[2]; // mi_tuberia[0] -> lectura // mi_tuberia[1] -> escritura

pipe(mi_tuberia);// primero creamos la tuberia y luego hacemos el fork
hijo = fork(); // read/write(mi_tuberia[ESCRITURA/LECTURA], &VARIABLE, sizeof(VARIABLE));
```
- [Ejercicio de Ejemplo Tuberias](./pipes.c)
- [Otro Ejemplo](./pipes2.c)
---
2. Evaluar cómo terminó el hijo (wait y macros)
```c
int estado;
wait(&estado); // 1. El padre espera y recoge el expediente del hijo

if (WIFEXITED(estado)) { // 2. Lupa de seguridad: ¿Murió de forma natural?
    int valor_del_hijo = WEXITSTATUS(estado); // 3. Lupa de extracción: Saca el número del exit()
    printf("El hijo devolvió: %d\n", valor_del_hijo);
} else {
    printf("El hijo terminó con error o fue asesinado.\n");
}
```
- [Ejemplo](./numeroCuadrado.c)
- [Ejemplo con tuberias y Macros](./operarioMatematico.c)



