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
#include <fstream> // Para leer archivos
#include <sstream> // Para convertir strings a números

using namespace std;
using namespace std::chrono;

// Lo mismo que class pero todo publico por default
struct LogEntry {
    string mes;         // agarra el mes del log
    string texto;       // el texto original del log
    long long fecha;    // la fecha en formato long long para poder comparar  
};

// cada mes con un valor numerico
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

// long sirve para guardar numeros grandes que int no puede guardar
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


// Funcion para cargar arhivo log y convertirlo en vector de LogEntry
vector<LogEntry> cargarArchivo(string rutaArchivo) {
    vector<LogEntry> registros;
    ifstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo " << rutaArchivo << endl;
        return registros;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue; // Ignorar líneas vacías

        stringstream ss(linea);
        string mes, horaStr;
        int dia;

        // Formato tipico de log: "Month Day HH:MM:SS RestOfLine"
        ss >> mes >> dia >> horaStr;

        // Extraer tiempos del string "HH:MM:SS"
        int hora = stoi(horaStr.substr(0, 2));
        int min  = stoi(horaStr.substr(3, 2));
        int seg  = stoi(horaStr.substr(6, 2));

        // Crea la entrada de log
        LogEntry entrada;
        entrada.texto = linea;
        entrada.fecha = convertirAFechaNumero(mes, dia, hora, min, seg);

        registros.push_back(entrada);
    }

    archivo.close();
    cout << "Archivo '" << rutaArchivo << "' cargado con exito. Total de registros: " << registros.size() << endl;
    return registros;
}

/*
ALGORTIMOS DE ORDENAMIENTO
*/

// swapSort
void swapSort(vector<LogEntry> &list) {
    int n = list.size();
    // recorrer lista
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (list[j].fecha > list[j + 1].fecha) {
                swap(list[j], list[j + 1]);
            }
        }
    }
}

// selectionsort
void selectionsort(vector<LogEntry> &list) {
    int n = list.size();
    // recorremos la lista buscando el valor minimo
    for (int i = 0; i < n - 1; i++) {
        // valor minimo (menor) es i
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            // comparamos el valor de j con el valor de minIndex para determinar si es menor
            if (list[j].fecha < list[minIndex].fecha) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(list[i], list[minIndex]);
        }
    }
}

// bubbleSort
void bubbleSort(vector<LogEntry> &list) {
    bool change = true;
    // iterar mientras exista algun cambio en la lista
    for (int i = list.size() - 1; i > 0 && change; i--) {
        // cambio el valor de change a falso
        change = false;
        // iteramos desde 0 hasta que sea menor que i
        for (int j = 0; j < i; j++) {
            // comparamos el valor de j con el valor de j+1 para determinar si es mayor
            if (list[j].fecha > list[j + 1].fecha) {
                // si es mayor
                // cambiamos change a verdadero
                change = true;
                // intercambiamos los valores
                swap(list[j], list[j + 1]);
            }
        }
    }
}

// insertionsort
void insertionsort(vector<LogEntry> &list) {
    int n = list.size();
    // recorremos la lista desde el inicio
    for (int i = 1; i < n; i++) {
        int j = i;
        // mientras j sea mayor o igual a 0 y el valor de j sea menor que el valor de j-1
        while (j > 0 && list[j].fecha < list[j - 1].fecha) {
            // movemos el valor de j a la izquierda
            swap(list[j], list[j - 1]);
            j--;
        }
    }
}

// mergesort
void merge(vector<LogEntry> &list, int left, int mid, int right) {
    vector<LogEntry> leftList;
    // generamos la lista de left a mid
    for (int i = left; i <= mid; i++) {
        leftList.push_back(list[i]);
    }
    
    vector<LogEntry> rightList;
    // generamos la lista de mid+1 a right
    for (int j = mid + 1; j <= right; j++) { 
        rightList.push_back(list[j]);
    }
    
    int index = left;
    size_t i = 0;
    size_t j = 0;
    // combinar sublistas ordenadas
    while (i < leftList.size() && j < rightList.size()) {
        if (leftList[i].fecha < rightList[j].fecha) {
            list[index] = leftList[i];
            i++;
        } else {
            list[index] = rightList[j];
            j++;
        }
        index++;
    }
    // copiar los elementos restantes de leftList, si los hay
    while (i < leftList.size()) {
        list[index] = leftList[i];
        i++;
        index++;
    }
    // copiar los elementos restantes de rightList, si los hay
    while (j < rightList.size()) {
        list[index] = rightList[j];
        j++;
        index++;
    }
}

void mergesort(vector<LogEntry> &list, int left, int right) {
    // condicion de control recursiva
    if (left < right) {
        int mid = (left + right) / 2;
        // ordenar de left a mid
        mergesort(list, left, mid);
        // ordenar de mid+1 a right
        mergesort(list, mid + 1, right);
        // combinar las sublistas ordenadas
        merge(list, left, mid, right);
    }
}

// quicksort
int getPivot(vector<LogEntry> &list, int left, int right) {
    int aux = left - 1;
    int pivot = right;
    // iteramos desde left hasta pivot
    for (int i = left; i < pivot; i++) {
        // comparamos el valor de i con el valor de pivot para determinar si es menor
        if (list[i].fecha < list[pivot].fecha) {
            aux++;
            swap(list[aux], list[i]);
        }
    }
    aux++;
    // intercambiamos el valor de aux con el valor de pivot
    swap(list[aux], list[pivot]);
    return aux;
}

void quicksort(vector<LogEntry> &list, int left, int right) {
    // ejecucion recursiva
    if (left < right) {
        int pivot = getPivot(list, left, right);
        quicksort(list, left, pivot - 1);
        quicksort(list, pivot + 1, right);
    }
}

// swapSort
void swapSort(vector<LogEntry> &list) {
    int n = list.size();
    // algoritmo, recorrer lista
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (list[j].fecha > list[j + 1].fecha) {
                swap(list[j], list[j + 1]);
            }
        }
    }
}

/* FALTA
archivo nuevo output.txt
Rango por busqueda binaria
Menu
*/