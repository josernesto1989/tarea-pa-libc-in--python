"""Wrapper de Python sobre la biblioteca compartida libpa.so usando ctypes."""

import ctypes
import os
from ctypes import (c_int, c_double, c_char_p, c_void_p, POINTER,
                    Structure, CFUNCTYPE)

# Ruta de la biblioteca: variable de entorno PA_LIB_PATH o libpa.so junto al módulo.
_LIB_PATH = os.environ.get("PA_LIB_PATH", os.path.join(os.path.dirname(__file__), "..", "libpa.so"))
if not os.path.exists(_LIB_PATH):
    _LIB_PATH = os.path.join(os.getcwd(), "libpa.so")

# Carga la biblioteca compartida en memoria.
_lib = ctypes.CDLL(_LIB_PATH)


# Estructura equivalente a PaPunto del lado C.
class PaPunto(Structure):
    _fields_ = [("x", c_double), ("y", c_double)]


# ---------- Declaración de firmas (argtypes/restype) ----------

_lib.pa_suma.argtypes = [c_int, c_int]
_lib.pa_suma.restype = c_int

_lib.pa_factorial.argtypes = [c_int]
_lib.pa_factorial.restype = c_int

_lib.pa_distancia.argtypes = [c_double, c_double, c_double, c_double]
_lib.pa_distancia.restype = c_double

_lib.pa_distancia_puntos.argtypes = [POINTER(PaPunto), POINTER(PaPunto)]
_lib.pa_distancia_puntos.restype = c_double

# Se usa c_void_p (y no c_char_p) para conservar el puntero original
# reservado con malloc() y poder liberarlo después con pa_liberar().
_lib.pa_reversa.argtypes = [c_char_p]
_lib.pa_reversa.restype = c_void_p

_lib.pa_liberar.argtypes = [c_void_p]
_lib.pa_liberar.restype = None

_lib.pa_suma_arreglo.argtypes = [POINTER(c_int), ctypes.c_size_t]
_lib.pa_suma_arreglo.restype = c_int

_lib.pa_ordenar.argtypes = [POINTER(c_int), ctypes.c_size_t]
_lib.pa_ordenar.restype = None

# Tipo de callback Python -> C.
_PA_FUNC_INT = CFUNCTYPE(c_int, c_int)
_lib.pa_aplicar.argtypes = [POINTER(c_int), ctypes.c_size_t, _PA_FUNC_INT]
_lib.pa_aplicar.restype = None

_lib.pa_version.argtypes = []
_lib.pa_version.restype = c_char_p


# ---------- Funciones de alto nivel para Python ----------

def suma(a, b):
    """Suma de dos enteros."""
    return _lib.pa_suma(a, b)


def factorial(n):
    """Factorial de n."""
    return _lib.pa_factorial(n)


def distancia(x1, y1, x2, y2):
    """Distancia euclidiana entre dos puntos por coordenadas."""
    return _lib.pa_distancia(x1, y1, x2, y2)


def distancia_puntos(a, b):
    """Distancia euclidiana entre dos puntos (tuplas)."""
    pa = PaPunto(a[0], a[1])
    pb = PaPunto(b[0], b[1])
    return _lib.pa_distancia_puntos(ctypes.byref(pa), ctypes.byref(pb))


def reversa(s):
    """Invierte una cadena. Libera la memoria reservada por C."""
    raw = _lib.pa_reversa(s.encode() if isinstance(s, str) else s)
    if not raw:
        return None
    try:
        return ctypes.string_at(raw).decode()
    finally:
        _lib.pa_liberar(raw)


def suma_arreglo(arr):
    """Suma los elementos de una lista de enteros."""
    n = len(arr)
    buf = (c_int * n)(*arr)          # Arreglo C a partir de la lista
    return _lib.pa_suma_arreglo(buf, n)


def ordenar(arr):
    """Devuelve una nueva lista con los elementos ordenados."""
    n = len(arr)
    buf = (c_int * n)(*arr)
    _lib.pa_ordenar(buf, n)
    return list(buf)


def aplicar(arr, f):
    """Aplica la función Python f a cada elemento (callback C)."""
    n = len(arr)
    buf = (c_int * n)(*arr)
    cb = _PA_FUNC_INT(f)             # Convierte la función Python en callback C
    _lib.pa_aplicar(buf, n, cb)
    return list(buf)


def version():
    """Versión de la biblioteca."""
    return _lib.pa_version().decode()
