#include <iostream>
#include <vector>
#include <chrono>
#include <string>
#include <algorithm>
#include <fstream> // Para leer archivos
#include <sstream> // Para convertir strings a números

using namespace std;    // para no tener que escribir std:: antes de cosas como cout, vector, cin, string, etc.
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
    ifstream archivo;

    // Listas de posibles rutas para abrir el archivo
    vector<string> posiblesRutas = {
        rutaArchivo,               // 1. Desde Evidence1/
        "../" + rutaArchivo,       // 2. Desde Evidence1/src/
        "../../" + rutaArchivo    // 3. Desde Evidence1/src/output/
    };

    // Probar cada ruta hasta abrir
    for (const string& ruta : posiblesRutas) {
        archivo.open(ruta);
        if (archivo.is_open()) {
            cout << "==> Archivo abierto exitosamente en: " << ruta << endl;
            break;
        }
        archivo.clear();
    }

    if (!archivo.is_open()) {
        cout << "Error: No se pudo encontrar el archivo en ninguna ruta." << endl;
        return registros;
    }

    string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue; // Ignorar líneas vacías

        stringstream ss(linea);
        string mes, palabraTemporal, horaStr;
        int dia;

        // Extraemos Mes, Día y la siguiente palabra
        if (!(ss >> mes >> dia >> palabraTemporal)) continue;

        // Si no es un mes válido (por ejemplo, encabezados del txt), se ignora
        if (mesANumero(mes) == 0) continue; 

        // Revisar si la palabra temporal contiene ':', lo que indica que es la hora
        if (palabraTemporal.find(':') == string::npos) {
            // Si NO tiene ':', significa que nos cruzamos con el Año (ej. 2024)
            // Entonces, la verdadera hora es la siguiente palabra:
            ss >> horaStr; 
        } else {
            // Si tiene ':', entonces sí era la hora
            horaStr = palabraTemporal;
        }

        int hora = 0, min = 0, seg = 0;

        // Extraccion de la hora
        try {
            stringstream ssHora(horaStr);
            string h, m, s;

            if (getline(ssHora, h, ':') && getline(ssHora, m, ':') && getline(ssHora, s, ':')) {
                hora = stoi(h);
                min  = stoi(m);
                seg  = stoi(s);
            } else {
                continue; // Formato de hora no valido, saltar línea
            }
        } catch (...) {
            continue; // Si ocurre cualquier error, saltar línea corrupta
        }

        // Crear la entrada de log
        LogEntry entrada;
        entrada.texto = linea;
        entrada.fecha = convertirAFechaNumero(mes, dia, hora, min, seg);

        registros.push_back(entrada);
    }

    archivo.close();
    cout << "Total de registros cargados con exito: " << registros.size() << endl;
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

// shellSort
void shellSort(vector<LogEntry> &list) {
    int n = list.size();
     // reducir los saltos a la mitad en cada iteracion
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            LogEntry temp = list[i];
            int j;
            for (j = i; j >= gap && list[j - gap].fecha > temp.fecha; j -= gap) {
                list[j] = list[j - gap];
            }
            list[j] = temp;
        }
    }
}

// Funcion para guardar datos en un archivo txt
void guardarArchivo(string rutaArchivo, const vector<LogEntry>& registros) {
    ofstream archivo(rutaArchivo);

    if (!archivo.is_open()) {
        cout << "Error: No se pudo abrir el archivo para guardar en " << rutaArchivo << endl;
        return;
    }

    for (const auto& reg : registros) {
        archivo << reg.texto << "\n";
    }

    archivo.close();
    cout << "==> Archivo guardado con exito en: " << rutaArchivo << endl;
}

//funciones de busqueda binaria
// limite inferior: busca el primer indice donde fecha >= target
int buscarInicio(const vector<LogEntry>& arr, long long fechaInicio) {
    int izq = 0;
    int der = arr.size() - 1;
    int resultado = -1;

    while (izq <= der) {
        int mid = izq + (der - izq) / 2;
        
        if (arr[mid].fecha >= fechaInicio) {    //mitad de la lista
            resultado = mid;   // Inicio
            der = mid - 1;     // buscamos a la izquierda para encontrar el primer indice
        } else {
            izq = mid + 1;
        }
    }
    return resultado;
}

// limite superior: busca el ultimo indice donde fecha <= target
int buscarFin(const vector<LogEntry>& arr, long long fechaFin) {
    int izq = 0;
    int der = arr.size() - 1;
    int resultado = -1;

    while (izq <= der) {
        int mid = izq + (der - izq) / 2;
        
        if (arr[mid].fecha <= fechaFin) {   //mitad de la lista
            resultado = mid;   // fin
            izq = mid + 1;     // buscamos a la derecha para encontrar el ultimo índice
        } else {
            der = mid - 1;
        }
    }
    return resultado;
}

// Funcion especifica para buscar y guardar registros en un rango de fechas
void buscarYGuardarRango(const vector<LogEntry>& list) {
    string mesInicio, mesFin, horaStrInicio, horaStrFin;
    int diaInicio, diaFin;

    cout << "\n=== BUSQUEDA POR RANGO DE FECHAS ===" << endl;
    
    //fecha inicial
    cout << "FECHA INICIAL (Ejemplo: Jun 1 00:00:00): ";
    cin >> mesInicio >> diaInicio >> horaStrInicio;
    
    // fecha final
    cout << "FECHA FINAL (Ejemplo: Jun 1 23:59:59): ";
    cin >> mesFin >> diaFin >> horaStrFin;

    // Conversion de horas a enteros
    int h1 = stoi(horaStrInicio.substr(0, 2)), m1 = stoi(horaStrInicio.substr(3, 2)), s1 = stoi(horaStrInicio.substr(6, 2));
    int h2 = stoi(horaStrFin.substr(0, 2)),    m2 = stoi(horaStrFin.substr(3, 2)),    s2 = stoi(horaStrFin.substr(6, 2));

    long long fechaInicio = convertirAFechaNumero(mesInicio, diaInicio, h1, m1, s1);
    long long fechaFin    = convertirAFechaNumero(mesFin, diaFin, h2, m2, s2);

    // busqueda binaria
    int idxInicio = buscarInicio(list, fechaInicio);
    int idxFin    = buscarFin(list, fechaFin);

    // Validar si se encontraron registros en el rango
    if (idxInicio != -1 && idxFin != -1 && idxInicio <= idxFin) {
        int totalEncontrados = idxFin - idxInicio + 1;
        cout << "\nSe encontraron " << totalEncontrados << " registros en ese rango." << endl;

        // guardar en archivo txt
        ofstream archivoRango("range607.txt");
        if (archivoRango.is_open()) {
            for (int i = idxInicio; i <= idxFin; i++) {
                archivoRango << list[i].texto << "\n";
            }
            archivoRango.close();
            cout << "==> Registros guardados con exito en 'range607.txt'" << endl;
        }
    } else {
        cout << "\nNo se encontraron registros en el rango especificado." << endl;
    }
}


int main() {
    int opt;
    do {
        cout << "\nEliga una opcion del menu:\n";
        cout << "1 Ordenar archivo de log\n";
        cout << "2 Realizar busqueda por rango de fechas (range607.txt)\n";
        cout << "3 Salir\n";
        cout << "Opcion: ";
        cin >> opt;

        if (opt == 1) {
            int archivoOpt, alg, prediccion;
            
            cout << "\nEliga el archivo de log:\n";
            cout << "1. log607-1.txt (Desordenado)\n";
            cout << "2. log607-2.txt (Casi ordenado)\n";
            cout << "Opcion: ";
            cin >> archivoOpt;

            if (archivoOpt != 1 && archivoOpt != 2) {
                cout << "Error: Opcion de archivo invalida. Intente de nuevo.\n";
                continue; 
            }

            // Ruta para ir a data/
            string nombreArchivo = (archivoOpt == 2) ? "data/log607-2.txt" : "data/log607-1.txt";
            vector<LogEntry> registros = cargarArchivo(nombreArchivo);

            if (registros.empty()) {
                cout << "Error: No se pudo cargar el archivo.\n";
                continue;
            }

            cout << "\nEliga algoritmo de ordenamiento:\n";
            cout << "1 SwapSort\n2 SelectionSort\n3 BubbleSort\n4 InsertionSort\n5 MergeSort\n6 QuickSort\n7 ShellSort\n";
            cout << "Opcion: ";
            cin >> alg;

            cout << "Prediccion de rendimiento (1: Rapido/Eficiente, 2: Lento/Ineficiente): ";
            cin >> prediccion;

            string nombreAlg = "";
            string complejidad = "";
            bool esRapido = false;

            auto start = high_resolution_clock::now();

            if (alg == 1) {
                nombreAlg = "SwapSort";
                complejidad = "O(N^2)";
                swapSort(registros);
            } else if (alg == 2) {
                nombreAlg = "SelectionSort";
                complejidad = "O(N^2)";
                selectionsort(registros);
            } else if (alg == 3) {
                nombreAlg = "BubbleSort";
                complejidad = "O(N^2)";
                bubbleSort(registros);
            } else if (alg == 4) {
                nombreAlg = "InsertionSort";
                complejidad = "O(N^2)";
                insertionsort(registros);
            } else if (alg == 5) {
                nombreAlg = "MergeSort";
                complejidad = "O(N log N)";
                esRapido = true;
                mergesort(registros, 0, registros.size() - 1);
            } else if (alg == 6) {
                nombreAlg = "QuickSort";
                complejidad = "O(N log N)";
                esRapido = true;
                quicksort(registros, 0, registros.size() - 1);
            }
            else if (alg == 7) {
                nombreAlg = "ShellSort";
                complejidad = "O(N log N)";
                esRapido = true;
                shellSort(registros);
            } else {
                cout << "Error: Opcion de algoritmo invalida. Intente de nuevo.\n";
                continue; 
            }
            
            auto stop = high_resolution_clock::now();
            auto duration = duration_cast<milliseconds>(stop - start);

            // Guardar resultado ordenado en output608.txt
            guardarArchivo("output608.txt", registros);

            // Imprimir reporte de la ejecución
            cout << "\n--- RESULTADOS ---" << endl;
            cout << "Archivo elegido: " << nombreArchivo << "\n";
            cout << "Tamano de datos: " << registros.size() << " registros\n";
            cout << "Algoritmo: " << nombreAlg << "\n";
            cout << "Complejidad teorica: " << complejidad << "\n";
            cout << "Tiempo de ejecucion: " << duration.count() << " ms\n";

            // Evaluación de la predicción del usuario
            bool acerto = (prediccion == 1 && esRapido) || (prediccion == 2 && !esRapido);
            if (acerto) {
                cout << "Prediccion del usuario: CORRECTA\n";
            } else {
                cout << "Prediccion del usuario: INCORRECTA\n";
            }

        } else if (opt == 2) {
            int archivoOpt;
            cout << "\nEliga el archivo para buscar por rango:\n";
            cout << "1. log607-1.txt\n2. log607-2.txt\nOpcion: ";
            cin >> archivoOpt;

            if (archivoOpt != 1 && archivoOpt != 2) {
            cout << "Error: Opcion de archivo invalida. Intente de nuevo.\n";
            continue; 
            }

            // Ruta a la carpeta data/
            string nombreArchivo = (archivoOpt == 2) ? "data/log607-2.txt" : "data/log607-1.txt";
            vector<LogEntry> registros = cargarArchivo(nombreArchivo);

            if (!registros.empty()) {
                // Se ordena el vector antes de realizar la búsqueda por rango
                quicksort(registros, 0, registros.size() - 1);
                buscarYGuardarRango(registros);
            }
        }

    } while (opt != 3);

    return 0;
}