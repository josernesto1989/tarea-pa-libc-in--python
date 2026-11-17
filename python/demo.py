"""Demostración de uso de libpa.so desde Python."""

import os
import sys
sys.path.insert(0, os.path.join(os.path.dirname(__file__)))

from pa_lib import (
    suma, factorial, distancia, distancia_puntos,
    reversa, suma_arreglo, ordenar, aplicar, version,
)

def main():
    # Muestra la versión de la biblioteca compartida.
    print("Versión de la biblioteca:", version())
    # Operaciones básicas.
    print("suma(3, 4) =", suma(3, 4))
    print("factorial(10) =", factorial(10))
    print("distancia(0,0,3,4) =", distancia(0, 0, 3, 4))
    print("distancia_puntos((0,0),(3,4)) =", distancia_puntos((0, 0), (3, 4)))
    # Manipulación de cadenas.
    print("reversa('Hola mundo') =", reversa("Hola mundo"))
    # Operaciones con arreglos.
    arr = [5, 2, 9, 1, 7]
    print("suma_arreglo([5,2,9,1,7]) =", suma_arreglo(arr))
    print("ordenar([5,2,9,1,7]) =", ordenar(arr))
    # Callback: duplica cada elemento.
    print("aplicar([1,2,3], x*2) =", aplicar([1, 2, 3], lambda x: x * 2))

if __name__ == "__main__":
    main()
