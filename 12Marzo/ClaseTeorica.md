- Los sistemas actuales permiten que se carguen en memoria multiples programas de forma simultánea
- `.exe` es un programa que se almacena en el disco. El kernel sube ese programa en un proceso
- Todo proceso contiene:
    - Las intrucciones del programa 
    - El contador del programa (PC, program counter/puntero que indica en donde está la siguiente instrucción)
    - Los contenidos de los registros del procesador
    - La pila del proeso (Almacenamiento temporal de datos al invocar funciones como parámetros, variables locales, direcciones de retorno...)
    - La sección de datos (variables globales)
    - El cúmulo de memoria (memory heap)(Memoria asiganda dinámicamente durante su ejecución)
        - Somos capaces de alojar memoria dinámicamente
        - Se puede hacer en c con la función: `malloc`
---
## Estados de un proceso
- Nuevo: El proceso fue creado 
- Ejecución: El programa está dentro de la CPU
- En espera: El programa se ha bloqueado para esperar un suceso, por ejemplo una entrada de datos por parte del usuario
- Preparado: El proceso esta a la espera de ser llevaado al procesador
- Terminado: El proceso ha terminado con su ejecución
    - Limpieza de ficheros y memoria

## Bloque de Control de Procesos -PCB
- Cada proceso se representa en el sistema operativo mediante un bloque de control de proceso. El PCB es una estructura de datos que contiene los siguientes elementos:
    - Estado del proceso
    - Contador del programa
    - Registros CPU
    - Información planificación CPU
    - Información gestión de la memoria
    - Información contable
    - Información del estado de E/S.

## Procesos
- El comando `ps`generar un listado de procesos que se encuentra actualemente activos en nuestra sesión
    - `ps -e`-> Nos da la lista entera de todos los procesos que están en el sistema
    - `ps -el`-> Nos da los procesos con más información ppid

## Programación de procesos
- **Fork**: Usada para crear un nuevo proceso mediante la duplicación del proceso llamdo fork es la primitiva básica de creación de un proceso
- **wait**: Permite que un proceso espere a que otro, relacionado con él (por ejemplo un hijo). Tambíen hay `waitid`
    - [Ejemplo Wait](ejemploWait.c)

## Comunicación entre procesos
- [Ejemplo Comunicación entre Procesos hecho con el profesor](comunicacionProcesos.c)
- [Ejemplo hecho por mi](numeroObjetivo.c)