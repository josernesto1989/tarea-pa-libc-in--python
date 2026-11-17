# Biblioteca compartida en C consumida desde Python

Proyecto de ejemplo que muestra cómo crear una biblioteca compartida (`.so`)
en C y consumirla desde Python mediante `ctypes`.

## Estructura

```
.
├── include/
│   └── pa_lib.h          # Declaraciones públicas
├── src/
│   └── pa_lib.c          # Implementación en C
├── python/
│   ├── pa_lib.py         # Wrapper ctypes
│   └── demo.py           # Demostración de uso
└── README.md
```

## Compilación (solo comandos en la terminal)

Requiere `gcc` (o compatible). No se usa ningún sistema de build (make/autotools).

```bash
gcc -O2 -Wall -Wextra -fPIC -Iinclude -c src/pa_lib.c -o pa_lib.o
gcc -shared -o libpa.so pa_lib.o -lm
rm -f pa_lib.o
```

Esto genera `libpa.so` en la raíz del proyecto. Para recompilar, repite los comandos. Para limpiar:

```bash
rm -f libpa.so pa_lib.o
```

## Uso desde Python

```bash
cd python
python3 demo.py
```

O ajustando la ruta de la biblioteca:

```bash
PA_LIB_PATH=/ruta/a/libpa.so python3 python/demo.py
```

## Funciones expuestas

| Función C | Wrapper Python | Descripción |
|---|---|---|
| `pa_suma` | `suma(a, b)` | Suma de dos enteros |
| `pa_factorial` | `factorial(n)` | Factorial de n |
| `pa_distancia` | `distancia(...)` | Distancia euclidiana entre dos puntos |
| `pa_distancia_puntos` | `distancia_puntos(a, b)` | Igual, con estructura `PaPunto` |
| `pa_reversa` | `reversa(s)` | Invierte una cadena (memoria liberada automáticamente) |
| `pa_suma_arreglo` | `suma_arreglo(arr)` | Suma elementos de un arreglo |
| `pa_ordenar` | `ordenar(arr)` | Ordena un arreglo de enteros |
| `pa_aplicar` | `aplicar(arr, f)` | Aplica un callback Python a cada elemento |
| `pa_version` | `version()` | Versión de la biblioteca |

## Notas

- La biblioteca se compila con `-fPIC` y se enlaza con `-shared`.
- `pa_reversa` reserva memoria con `malloc`; el wrapper libera automáticamente con `pa_liberar`.
- `pa_aplicar` demuestra el paso de callbacks de Python a C mediante `CFUNCTYPE`.
- En macOS el sufijo equivalente es `.dylib`; en Windows `.dll`. Este ejemplo apunta a Linux/`.so`.
