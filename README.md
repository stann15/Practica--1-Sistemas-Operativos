# Práctica 1 – Programación en C (Sistemas Operativos)

Esta práctica trata de una biblioteca estática en C con tres funciones que procesan líneas leídas desde la entrada estándar y un programa de prueba que las utiliza

## Funciones

| Función | Descripción |
|---|---|
| `head(N)` | Muestra las N primeras líneas |
| `tail(N)` | Muestra las N últimas líneas |
| `longlines(N)` | Muestra las N líneas más largas, ordenadas de mayor a menor longitud |

## Ficheros

- `libreria.c`: implementación de las funciones
- `libreria.h`: cabeceras de las funciones 
- `test.c`: programa de prueba que recibe la función y el número de líneas por argumentos
- `compila.sh`: genera la biblioteca `liblibreria.a` y compila `test` enlazándolo con ella
- `prueba*.txt`: ficheros usados para pruebas

## Autores

- Rubén Torres Rivero
- Stanislaw Cherkhavsky Pater
