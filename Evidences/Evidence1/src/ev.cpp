/* Resumen de lo que se tiene que hacer
1. Implementar todos los algoritmos de ordenamiento vistos
2. menu interactivo para seleccionar archivo y algoritmo (Y que le pregunte al usuario lo que espera de ese algoritmo 
ej. rapido, lento, estable, etc.)
3. Al terminar imprimir lo siguiente:
    - archivo nuevo output.txt
    - Nombre del algoritmo
    - Archivo que se eligio
    - tamaño de datos
    - Tiempo de ejecucion
    - Complejidad (mejor o peor caso?)
    extra - indicar si el tiempo que predijo el usuario fue correcto o no (con tolerancia)
4. implementar busqueda por rango pidiendo fecha/hora de inicio y fin
    - utilizar busqueda binaria o algo similar
    - archivo nuevo rango.txt
    - en caso que haya datos duplicados hacer que la busqueda continue hasta que no haya mas duplicados y que se cumpla el rango
*/

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;
