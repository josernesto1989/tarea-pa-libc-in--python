#ifndef PA_LIB_H
#define PA_LIB_H

/* Guarda de inclusión: evita que el header se procese más de una vez. */
#include <stddef.h>  /* size_t */

#ifdef __cplusplus
/* Si se compila como C++, las funciones se exponen con enlace C (sin name mangling). */
extern "C" {
#endif

/* Macro para exportar símbolos de la biblioteca compartida.
 * En Windows se usa __declspec(dllexport); en Unix/Linux/macOS se marca
 * la visibilidad como "default" para que ctypes pueda resolver el símbolo. */
#if defined(_WIN32)
  #define PA_API __declspec(dllexport)
#else
  #define PA_API __attribute__((visibility("default")))
#endif

/* Estructura que se comparte con Python: representa un punto en el plano. */
typedef struct {
    double x;  /* Coordenada horizontal */
    double y;  /* Coordenada vertical   */
} PaPunto;

/* ---------- Operaciones básicas ---------- */

/* Suma de dos enteros. */
PA_API int    pa_suma(int a, int b);

/* Factorial de n (n >= 0). Devuelve 0 si n es negativo. */
PA_API int    pa_factorial(int n);

/* Distancia euclidiana entre dos puntos dados por coordenadas. */
PA_API double pa_distancia(double x1, double y1, double x2, double y2);

/* Distancia euclidiana entre dos puntos dados como estructuras PaPunto. */
PA_API double pa_distancia_puntos(const PaPunto* a, const PaPunto* b);

/* ---------- Cadenas ---------- */

/* Invierte la cadena s. El resultado se reserva con malloc();
 * el llamador debe liberarlo con pa_liberar(). */
PA_API char*  pa_reversa(const char* s);

/* Libera memoria reservada por la biblioteca (por ejemplo, el resultado de pa_reversa). */
PA_API void   pa_liberar(void* p);

/* ---------- Arreglos ---------- */

/* Suma los n elementos del arreglo arr. */
PA_API int    pa_suma_arreglo(const int* arr, size_t n);

/* Ordena en sitio (in-place) los n elementos del arreglo arr (ascendente). */
PA_API void   pa_ordenar(int* arr, size_t n);

/* ---------- Callbacks ---------- */

/* Tipo de función callback: recibe un int y devuelve un int. */
typedef int (*pa_funcion_int)(int);

/* Aplica la función f a cada elemento del arreglo arr (in-place). */
PA_API void   pa_aplicar(int* arr, size_t n, pa_funcion_int f);

/* ---------- Metadatos ---------- */

/* Devuelve la versión de la biblioteca como cadena (no liberar). */
PA_API const char* pa_version(void);

#ifdef __cplusplus
}
#endif

#endif /* PA_LIB_H */
