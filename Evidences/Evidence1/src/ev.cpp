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

// Lo mismo que class pero todo publico por default
struct LogEntry {
    string mes;         // agarra el mes del log
    string texto;       // el texto original del log
    long long fecha;    // la fecha en formato long long para poder comparar  
};

long long convertirAFechaNumero(string mes, int dia, int hora, int min, int seg) {
    int numMes = mesANumero(mes);
    
    // fecha en orden de importancia con matematicas para hacer comparaciones
    // Año * 10000000000 + Mes * 100000000 + Dia * 1000000 + Hora * 10000 + Minuto * 100 + Segundo
    long long fechaCompuesta = 2024LL * 10000000000LL + 
                               numMes * 100000000LL + 
                               dia * 1000000LL + 
                               hora * 10000LL + 
                               min * 100LL + 
                               seg;
                               
    return fechaCompuesta;
}

int mesANumero(string mes) {
    if (mes == "Jan") return 1;
    if (mes == "Feb") return 2;
    if (mes == "Mar") return 3;
    if (mes == "Apr") return 4;
    if (mes == "May") return 5;
    if (mes == "Jun") return 6;
    if (mes == "Jul") return 7;
    if (mes == "Aug") return 8;
    if (mes == "Sep") return 9;
    if (mes == "Oct") return 10;
    if (mes == "Nov") return 11;
    if (mes == "Dec") return 12;
    return 0;
}