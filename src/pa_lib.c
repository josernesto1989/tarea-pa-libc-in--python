/* Implementación de la biblioteca compartida pa_lib. */

#include "pa_lib.h"  /* Declaraciones públicas */

#include <math.h>     /* sqrt */
#include <stdlib.h>   /* malloc, free, qsort */
#include <string.h>   /* strlen */

/* Suma de dos enteros. */
PA_API int pa_suma(int a, int b) {
    return a + b;
}

/* Factorial de n. Si n < 0 devuelve 0 (caso inválido). */
PA_API int pa_factorial(int n) {
    if (n < 0) return 0;
    long long r = 1;                 /* Acumulador del resultado */
    for (int i = 2; i <= n; i++)     /* Multiplica 2..n */
        r *= i;
    return (int)r;
}

/* Distancia euclidiana entre (x1,y1) y (x2,y2). */
PA_API double pa_distancia(double x1, double y1, double x2, double y2) {
    double dx = x2 - x1;             /* Diferencia en X */
    double dy = y2 - y1;             /* Diferencia en Y */
    return sqrt(dx * dx + dy * dy);  /* Teorema de Pitágoras */
}

/* Distancia entre dos puntos dados como estructuras PaPunto. */
PA_API double pa_distancia_puntos(const PaPunto* a, const PaPunto* b) {
    if (!a || !b) return 0.0;        /* Validación de punteros nulos */
    return pa_distancia(a->x, a->y, b->x, b->y);
}

/* Invierte la cadena s. Reserva memoria con malloc() que el llamador libera. */
PA_API char* pa_reversa(const char* s) {
    if (!s) return NULL;             /* Cadena nula: sin resultado */
    size_t len = strlen(s);
    char* out = (char*)malloc(len + 1);  /* +1 para el terminador '\0' */
    if (!out) return NULL;           /* Fallo de asignación */
    for (size_t i = 0; i < len; i++)
        out[i] = s[len - 1 - i];     /* Copia en orden inverso */
    out[len] = '\0';                 /* Terminador de cadena */
    return out;
}

/* Libera memoria reservada por la biblioteca (wrapper de free). */
PA_API void pa_liberar(void* p) {
    free(p);
}

/* Suma los n elementos del arreglo arr. */
PA_API int pa_suma_arreglo(const int* arr, size_t n) {
    if (!arr) return 0;              /* Arreglo nulo */
    int acc = 0;
    for (size_t i = 0; i < n; i++)
        acc += arr[i];
    return acc;
}

/* Función de comparación para qsort: orden ascendente de enteros. */
static int cmp_int(const void* a, const void* b) {
    int va = *(const int*)a;
    int vb = *(const int*)b;
    return (va > vb) - (va < vb);    /* -1, 0 o 1 */
}

/* Ordena en sitio el arreglo arr de n enteros (ascendente) usando qsort. */
PA_API void pa_ordenar(int* arr, size_t n) {
    if (!arr || n < 2) return;       /* Nada que ordenar */
    qsort(arr, n, sizeof(int), cmp_int);
}

/* Aplica el callback f a cada elemento del arreglo arr (in-place). */
PA_API void pa_aplicar(int* arr, size_t n, pa_funcion_int f) {
    if (!arr || !f) return;          /* Validación de punteros */
    for (size_t i = 0; i < n; i++)
        arr[i] = f(arr[i]);          /* f viene de Python vía ctypes */
}

/* Devuelve la versión de la biblioteca (cadena estática, no liberar). */
PA_API const char* pa_version(void) {
    return "pa-lib 1.0.0";
}
