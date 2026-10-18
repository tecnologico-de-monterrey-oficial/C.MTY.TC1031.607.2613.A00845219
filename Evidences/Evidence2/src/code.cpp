/* NO PUEDES USAR LIBRERIAS:
std::list, std::forward_list, std::queue, std::stack, std::deque ni std::sort std::stable_sort. 
Los registros se almacenan únicamente en tu lista doblemente ligada. 

USAR SOLO PARA CONTAR FRECUENCIAS ESTADISTICAS:
std::map y std::unordered_map

===Por hacer===
1. Aplicar
- LinkedList (lista simple)
- Queue (fila)
- Stack (pila)
- DoublyLinkedList (lista doblemente ligada)

2. Buscar la funcion para cargar documentos al programa
3. Menu
- Buscar logs por dia
- Ordenar por fecha y hora
- Logs ascendente y descendentes
- Estadisticas de logs (total de registros, dia con mas actividad, IP mas repetida)
- Salir limpiando memoria

===Opcionales posibles===
1. Implementar un algoritmo de ordenamiento (merge o quick)
2. Agregar una fila de consultas e ir atendiendo una por una en orden de fila

INCLUIR OUTPUT
>>> detalles en canvas
*/

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream> 
#include <vector>
#include <map>
#include <set>
#include <algorithm>

// Archivos pasados
#include "LinkedListMain.h"
#include "DLinkedList.h"
#include "Q.h"
#include "pilas.h"

using namespace std;

// Struct para almacenar cada registro de log
struct LogRecord {
    string mes;
    int dia;
    int year;
    string hora;
    string ip;
    string mensaje;

    // cada mes con un valor numerico
    int mesANumero(string mes) const {
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
    // Sobrecarga de operadores (Solo ordena por año, luego mes, luego día)
    bool operator<(const LogRecord& other) const {
        if (year != other.year) {
            return year < other.year;
        }
        
        int m1 = mesANumero();
        int m2 = other.mesANumero();
        if (m1 != m2) return m1 < m2;
        
        return dia < other.dia;
    }
    
    bool operator>(const LogRecord& other) const {
        return other < *this;
    }
    
    bool operator==(const LogRecord& other) const {
        // Corregido: anio -> year
        return year == other.year && dia == other.dia && mes == other.mes; 
    }
};

// funcion para imprimir registros de log
void imprimirLog(const LogRecord& log) {
    cout << log.mes << " " << log.dia << " " << log.year << " " 
         << log.hora << " " << log.ip << " " << log.mensaje << endl;
}

// Funcion para cargar archivo log y convertirlo en DLinkedList
void cargarArchivo(DoublyLinkedList<LogRecord>& listaLogs) {
    Queue<string> filaLineas;
    string nombreArchivo;
    int lineasOmitidas = 0, registrosCargados = 0;
    cout << "Ingresa el nombre del archivo a cargar (ej. log607-1.txt): ";
    cin >> nombreArchivo;
    ifstream archivo(nombreArchivo);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return;
    }
    string linea;

    while (getline(archivo, linea)) {
        if (!linea.empty()) {
            filaLineas.push(linea); 
        }
    }
    archivo.close();

    while (!filaLineas.isEmpty()) {
        string currentLine = filaLineas.pop();
        stringstream ss(currentLine);
        LogRecord log;
        
        if (ss >> log.mes >> log.dia >> log.year >> log.hora >> log.ip) {
            getline(ss >> ws, log.mensaje);
            listaLogs.addLast(log); 
            registrosCargados++;
        } else {
            lineasOmitidas++;
            cout << "Línea omitida por formato inválido: " << currentLine << endl;
        }
    }

    cout << "Carga finalizada. Registros exitosos: " << registrosCargados 
         << " | Líneas omitidas: " << lineasOmitidas << endl;
}

// QuickSort
int getPivot(vector<LogRecord> &list, int left, int right) {
    int aux = left - 1;
    int pivot = right;
    // iteramos desde left hasta pivot
    for (int i = left; i < pivot; i++) {
        // Tenemos < sobrecargado en LogRecord, usar directo
        if (list[i] < list[pivot]) {
            aux++;
            swap(list[aux], list[i]);
        }
    }
    aux++;
    // intercambiamos el valor de aux con el valor de pivot
    swap(list[aux], list[pivot]);
    return aux;
}

void quicksort(vector<LogRecord> &arr, int inicio, int fin) {
    // ejecucion recursiva
    if (inicio < fin) {
        int pivot = getPivot(arr, inicio, fin);
        quicksort(arr, inicio, pivot - 1);
        quicksort(arr, pivot + 1, fin);
    }
}

// Funcion para escribir estadisticas del log
void Estadisticas(const vector<LogRecord>& registros) {
    map<string, int> conteoDias;
    map<string, int> conteoIps;
    set<string> tiposEvento;
    
    for (const auto& r : registros) {
        string fechaStr = r.mes + " " + to_string(r.dia) + " " + to_string(r.year);
        conteoDias[fechaStr]++;
        conteoIps[r.ip]++;
        tiposEvento.insert(r.mensaje);
    }
    
    string diaMasIncidentes, ipMasRepetida;
    int maxDias = 0, maxIps = 0;
    
    for (const auto& par : conteoDias) {
        if (par.second > maxDias) { maxDias = par.second; diaMasIncidentes = par.first; }
    }
    for (const auto& par : conteoIps) {
        if (par.second > maxIps) { maxIps = par.second; ipMasRepetida = par.first; }
    }
    
    cout << "\n================ ESTADISTICAS DEL REPORTE ================\n";
    cout << "Total de registros: " << registros.size() << "\n";
    cout << "Dia con mas incidentes: " << diaMasIncidentes << " (" << maxDias << " eventos)\n";
    cout << "IP mas repetida: " << ipMasRepetida << " (" << maxIps << " apariciones)\n";
    cout << "Tipos de evento detectados:\n";
    for (const auto& ev : tiposEvento) {
        cout << " - " << ev << "\n";
    }
    cout << "==========================================================\n";
}

// --- MAIN PRINCIPAL ---
int main() {
    DoublyLinkedList<LogRecord> listaLogs;
    vector<LogRecord> arrayTemporalLogs; // Vector de apoyo para Quicksort O(1) en acceso
    
    // 1. Cargar el archivo
    cargarArchivo(listaLogs);
    
    // 2. Transferir datos de tu DLinkedList al vector para poder ordenarlos
    while (!listaLogs.empty()) { 
        arrayTemporalLogs.push_back(listaLogs.deleteFirst());
    }

    if (arrayTemporalLogs.empty()) {
        cout << "No hay registros para procesar." << endl;
        return 0;
    }

    // 3. Ordenar usando Quicksort
    quicksort(arrayTemporalLogs, 0, arrayTemporalLogs.size() - 1);
    cout << "\nRegistros ordenados exitosamente por Año, Mes y Día.\n";

    // 4. Calcular e imprimir todas las estadísticas pedidas
    Estadisticas(arrayTemporalLogs);

    return 0;
}