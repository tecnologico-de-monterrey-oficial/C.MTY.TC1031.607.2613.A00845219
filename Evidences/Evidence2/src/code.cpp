#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <sstream> 
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <chrono>

// Archivos pasados
#include "../include/LinkedListMain.h"
#include "../include/DLinkedList.h"
#include "../include/Q.h"
#include "../include/pilas.h"

using namespace std;
using namespace std::chrono;

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
        if (year != other.year) return year < other.year;

        int m1 = mesANumero(mes);
        int m2 = other.mesANumero(other.mes);
        if (m1 != m2) return m1 < m2;
        
        return dia < other.dia;
    }
    
    bool operator>(const LogRecord& other) const {
        return other < *this;
    }
    
    bool operator==(const LogRecord& other) const {
        // Comparar año, mes y día para determinar igualdad
        return year == other.year && dia == other.dia && mes == other.mes; 
    }
};

// funcion para imprimir registros de log
void imprimirLog(const LogRecord& log) {
    cout << log.mes << " " << log.dia << " " << log.year << " " 
         << log.hora << " " << log.ip << " " << log.mensaje << endl;
}

// Funcion para cargar archivo log y convertirlo en DLinkedList
void cargarArchivo(vector<LogRecord>& arrayLogs, string rutaArchivo, string& rutaExitosa) {
    int lineasOmitidas = 0, registrosCargados = 0;
    vector<string> posiblesRutas = {
        rutaArchivo,               // 1. Desde Evidence2/
        "../" + rutaArchivo,       // 2. Desde Evidence2/src/
        "../../" + rutaArchivo     // 3. Desde Evidence2/src/output/
    };

    ifstream archivo;
    for (const string& ruta : posiblesRutas) {
        archivo.open(ruta);
        if (archivo.is_open()) {
            rutaExitosa = ruta; // Se usa 'rutaExitosa' que viene por parámetro
            cout << "==> Archivo abierto exitosamente en: " << ruta << endl;
            break;
        }
        archivo.clear();
    }

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo." << endl;
        return;
    }

    string linea;
    arrayLogs.clear();
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        stringstream ss(linea);
        LogRecord log;
        
        if (ss >> log.mes >> log.dia >> log.year >> log.hora >> log.ip) {
            getline(ss >> ws, log.mensaje);
            arrayLogs.push_back(log); // Se usa 'arrayLogs' en lugar de 'listaLogs'
            registrosCargados++;
        } else {
            lineasOmitidas++;
        }
    }
    archivo.close();

    cout << "Carga finalizada. Registros exitosos: " << registrosCargados 
         << " | Lineas omitidas: " << lineasOmitidas << endl;
}

// QuickSort
int getPivot(vector<LogRecord> &list, int left, int right, long long &comparaciones) {
    int aux = left - 1;
    int pivot = right;
    for (int i = left; i < pivot; i++) {
        comparaciones++;
        if (list[i] < list[pivot]) {
            aux++;
            swap(list[aux], list[i]);
        }
    }
    aux++;
    swap(list[aux], list[pivot]);
    return aux;
}

void quicksort(vector<LogRecord> &arr, int inicio, int fin, long long &comparaciones, int profundidadActual, int &maxProfundidad) {
    if (profundidadActual > maxProfundidad) {
        maxProfundidad = profundidadActual;
    }
    if (inicio < fin) {
        int pivot = getPivot(arr, inicio, fin, comparaciones);
        quicksort(arr, inicio, pivot - 1, comparaciones, profundidadActual + 1, maxProfundidad);
        quicksort(arr, pivot + 1, fin, comparaciones, profundidadActual + 1, maxProfundidad);
    }
}

// Funcion para escribir estadisticas del log
void Estadisticas(const vector<LogRecord>& registros) {
    if (registros.empty()) {
        cout << "No hay registros cargados.\n";
        return;
    }
    // map para contar el dia con actividad, ip repetida y evento mas frecuente
    map<string, int> conteoDias;
    map<string, int> conteoIps;
    map<string, int> conteoEventos;
    // contar frecuencias
    for (const auto& r : registros) {
        string fechaStr = r.mes + " " + to_string(r.dia) + " " + to_string(r.year);
        conteoDias[fechaStr]++;
        conteoIps[r.ip]++;
        conteoEventos[r.mensaje]++;
    }
    // Encontrar los maximos y empates
    int maxDias = 0, maxIps = 0, maxEventos = 0;
    
    for (const auto& par : conteoDias) if (par.second > maxDias) maxDias = par.second;
    for (const auto& par : conteoIps) if (par.second > maxIps) maxIps = par.second;
    for (const auto& par : conteoEventos) if (par.second > maxEventos) maxEventos = par.second;
    
    // Almacenar todos los que empaten con el valor maximo
    vector<string> diasEmpate, ipsEmpate, eventosEmpate;
    for (const auto& par : conteoDias) if (par.second == maxDias) diasEmpate.push_back(par.first);
    for (const auto& par : conteoIps) if (par.second == maxIps) ipsEmpate.push_back(par.first);
    for (const auto& par : conteoEventos) if (par.second == maxEventos) eventosEmpate.push_back(par.first);
    
    cout << "\n================ ESTADISTICAS DEL REPORTE ================\n";
    cout << "Total de registros procesados: " << registros.size() << "\n\n";
    cout << "Dia con mas incidentes (" << maxDias << " eventos):\n";

    for(const auto& dia : diasEmpate) cout << " -> " << dia << "\n";
    cout << "\nIPs mas repetidas (" << maxIps << " apariciones):\n";

    for(const auto& ip : ipsEmpate) cout << " -> " << ip << "\n";
    cout << "\nEvento mas frecuente (" << maxEventos << " incidencias):\n";
    
    for(const auto& evento : eventosEmpate) cout << " -> " << evento << "\n";
    cout << "==========================================================\n";
}

// funcion para usar la pila y buscar por dia
void buscarPorDia(const vector<LogRecord>& registros, bool ordenado) {
    if (!ordenado) {
        cout << "\nALERTA: La lista no esta ordenada. Por favor ordene los datos primero (Opcion 1).\n";
        return;
    }
    
    string mesBuscado;
    int diaBuscado, yearBuscado;
    
    cout << "\n-- Búsqueda de Registros --\n";
    cout << "Mes (Ej. Sep): "; cin >> mesBuscado;
    cout << "Dia (Ej. 14): "; cin >> diaBuscado;
    cout << "Anio (Ej. 2024): "; cin >> yearBuscado;

    LogRecord temp;
    if (temp.mesANumero(mesBuscado) == 0 || diaBuscado < 1 || diaBuscado > 31 || yearBuscado < 1900) {
        cout << "Error: Formato de fecha invalido.\n";
        return;
    }
    // 
    LogRecord objetivo;
    objetivo.mes = mesBuscado; objetivo.dia = diaBuscado; objetivo.year = yearBuscado;
    
    // usando la pila
    Stack<LogRecord> pilaResultados; 
    int contador = 0;

    // O(N)
    for (const auto& r : registros) {
        if (r == objetivo) {
            pilaResultados.push(r); // Insertar en tu pila personalizada
            contador++;
        } else if (objetivo < r) {
            break; // Detener recorrido gracias al ordenamiento previo
        }
    }

    if (contador == 0) {
        cout << "\nNo hay registros para la fecha solicitada.\n";
    } else {
        cout << "\nSe encontraron " << contador << " registros.\n";
        cout << "Mostrando orden invertido usando Pila:\n";
        
        // iterar la pila hasta terminar
        while (!pilaResultados.isEmpty()) { 
            imprimirLog(pilaResultados.top());
            pilaResultados.pop();              
        }
    }
}

// validar si el vector ya esta ordenado
bool estaOrdenado(const vector<LogRecord>& arr) {
    if (arr.empty()) return true;
    for (size_t i = 1; i < arr.size(); i++) {
        if (arr[i] < arr[i - 1]) return false;
    }
    return true;
}

// funcion para generar archivo output ordenado
void archivoOutput(const vector<LogRecord>& arr) {
    ofstream salida("output608.out");
    if (!salida.is_open()) {
        cout << "Error: No se pudo crear output608.out" << endl;
        return;
    }
    for (const auto& log : arr) {
        salida << log.mes << " " << log.dia << " " << log.year << " " 
               << log.hora << " " << log.ip << " " << log.mensaje << "\n";
    }
    salida.close();
    cout << "Archivo 'output608.out' generado exitosamente." << endl;
}


// main menu
int main() {
    vector<LogRecord> arrayTemporalLogs; 
    bool datosOrdenados = false;
    string rutaExitosa = "";
    int opt;

    do {
        cout << "\n--- Analisis de Logs ---\n";
        cout << "1. Cargar y Ordenar Archivo de Log\n";
        cout << "2. Buscar registros por fecha (Requiere ordenamiento)\n";
        cout << "3. Ver Estadisticas Generales\n";
        cout << "4. Salir\n";
        cout << "Opcion: ";
        cin >> opt;

        if (opt == 1) {
            int fileOpt;
            cout << "\nArchivos disponibles:\n1. log607-1.txt\n2. log607-2.txt\nSeleccion: ";
            cin >> fileOpt;
            
            string rutaArchivo = (fileOpt == 1) ? "data/log607-1.txt" : "data/log607-2.txt";
            cargarArchivo(arrayTemporalLogs, rutaArchivo, rutaExitosa);
            
            if (arrayTemporalLogs.empty()) continue;

            if (estaOrdenado(arrayTemporalLogs)) {
                cout << "\nLa lista YA ESTA ORDENADA. Se omite el algoritmo de ordenamiento.\n";
                datosOrdenados = true;
            } else {
                cout << "\nOrdenando registros...\n";
                long long comparaciones = 0;
                int maxProfundidad = 0;
                
                auto start = high_resolution_clock::now();
                quicksort(arrayTemporalLogs, 0, arrayTemporalLogs.size() - 1, comparaciones, 1, maxProfundidad);
                auto stop = high_resolution_clock::now();
                auto duration = duration_cast<milliseconds>(stop - start);
                
                datosOrdenados = true;
                
                cout << "\n--- Resultados del Algoritmo ---\n";
                cout << "Algoritmo usado: QuickSort\n";
                cout << "Archivo origen: " << rutaExitosa << "\n";
                cout << "Tamanio de los datos: " << arrayTemporalLogs.size() << " elementos\n";
                cout << "Tiempo de ejecucion: " << duration.count() << " ms\n";
                cout << "Numero de comparaciones: " << comparaciones << "\n";
                cout << "Profundidad maxima de recursion: " << maxProfundidad << "\n";
                cout << "Coincidencia con la prediccion: (Complejidad: O(N log N)\n";
                cout << "--------------------------------\n";
            }
            archivoOutput(arrayTemporalLogs);
            
        } else if (opt == 2) {
            if (arrayTemporalLogs.empty()) {
                cout << "\nNo hay datos cargados. Ejecute la Opcion 1 primero.\n";
            } else {
                buscarPorDia(arrayTemporalLogs, datosOrdenados);
            }
        } else if (opt == 3) {
            Estadisticas(arrayTemporalLogs);
        }

    } while (opt != 4);

    cout << "Programa finalizado.\n";
    return 0;
}