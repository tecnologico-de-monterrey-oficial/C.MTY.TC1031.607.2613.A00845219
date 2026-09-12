#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <string>
#include <algorithm>

using namespace std;
using namespace std::chrono;

// funciones para ordenar y medir tiempo

// imprimir vector 
template<typename T>
void imprimirVector(const vector<T>& v) {
    int n = v.size();
    if (n <= 20) {
        for (T val : v) cout << val << " ";
    } else {
        for (int i = 0; i < 10; ++i) cout << v[i] << " ";
        cout << "... ";
        for (int i = n - 10; i < n; ++i) cout << v[i] << " ";
    }
    cout << "\n";
}

// Generar vectores aleatorios segun el tipo de dato
template<typename T>
vector<T> generarVectorAleatorio(int n, string tipo) {
    vector<T> v(n);
    random_device rd;
    mt19937 gen(rd());
    
    if (tipo == "int") {
        uniform_int_distribution<int> dist(1, 100000);
        for(int i = 0; i < n; ++i) v[i] = dist(gen);
    } else if (tipo == "float") {
        uniform_real_distribution<float> dist(1.0, 100000.0);
        for(int i = 0; i < n; ++i) v[i] = dist(gen);
    } else if (tipo == "double") {
        uniform_real_distribution<double> dist(1.0, 100000.0);
        for(int i = 0; i < n; ++i) v[i] = dist(gen);
    }
    return v;
}

// ALGORITMOS

// swapSort
template <typename T>
void swapSort(vector<T> &list, long long &comps, long long &swaps) {
    comps = 0; swaps = 0;
    int n = list.size();
    // recorrer lista
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comps++;
            if (list[j] > list[j + 1]) {
                swap(list[j], list[j + 1]);
                swaps++;
            }
        }
    }
}

// selectionsort
template <typename T>
void selectionsort(vector<T> &list, long long &comps, long long &swaps) {
    comps = 0; swaps = 0;
    int n = list.size();
    // recorremos la lista buscando el valor minimo
    for (int i = 0; i < n - 1; i++) {
        // valor minimo (menor) es i
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            // comparamos el valor de j con el valor de minIndex para determinar si es menor
            comps++;
            if (list[j] < list[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            swap(list[i], list[minIndex]);
            swaps++;
        }
    }
}

// bubbleSort
template <typename T>
void bubbleSort(vector<T> &list, long long &comps, long long &swaps) {
    comps = 0; swaps = 0;
    bool change = true;
    // iterar mientras exista algun cambio en la lista
    for (int i = list.size() - 1; i > 0 && change; i--) {
        // cambio el valor de change a falso
        change = false;
        // iteramos desde 0 hasta que sea menor que i
        for (int j = 0; j < i; j++) {
            // comparamos el valor de j con el valor de j+1 para determinar si es mayor
            comps++;
            if (list[j] > list[j + 1]) {
                // si es mayor
                // cambiamos change a verdadero
                change = true;
                // intercambiamos los valores
                swap(list[j], list[j + 1]);
                swaps++;
            }
        }
    }
}

// insertionsort
template <typename T>
void insertionsort(vector<T> &list, long long &comps, long long &swaps) {
    comps = 0; swaps = 0;
    int n = list.size();
    // recorremos la lista desde el inicio
    for (int i = 1; i < n; i++) {
        int j = i;
        comps++;
        // mientras j sea mayor o igual a 0 y el valor de j sea menor que el valor de j-1
        while (j > 0 && list[j] < list[j - 1]) {
            // movemos el valor de j a la izquierda
            swap(list[j], list[j - 1]);
            swaps++;
            j--;
            if (j > 0) comps++;
        }
    }
}

// mergesort
template <typename T>
void merge(vector<T> &list, int left, int mid, int right) {
    vector<T> leftList;
    // generamos la lista de left a mid
    for (int i = left; i <= mid; i++) {
        leftList.push_back(list[i]);
    }
    
    vector<T> rightList;
    // generamos la lista de mid+1 a right
    for (int j = mid + 1; j <= right; j++) { 
        rightList.push_back(list[j]);
    }
    
    int index = left;
    size_t i = 0;
    size_t j = 0;
    // combinar sublistas ordenadas
    while (i < leftList.size() && j < rightList.size()) {
        if (leftList[i] < rightList[j]) {
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

template <typename T>
void mergesort(vector<T> &list, int left, int right) {
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
template <typename T>
int getPivot(vector<T> &list, int left, int right) {
    int aux = left - 1;
    int pivot = right;
    // iteramos desde left hasta pivot
    for (int i = left; i < pivot; i++) {
        // comparamos el valor de i con el valor de pivot para determinar si es menor
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

template <typename T>
void quicksort(vector<T> &list, int left, int right) {
    // ejecucion recursiva
    if (left < right) {
        int pivot = getPivot(list, left, right);
        quicksort(list, left, pivot - 1);
        quicksort(list, pivot + 1, right);
    }
}

// shellSort (nuevo algo)
template<typename T>
void shellSort(vector<T>& list) {
    int n = list.size();
    // reducir los saltos a la mitad en cada iteracion
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            T temp = list[i];
            int j;
            for (j = i; j >= gap && list[j - gap] > temp; j -= gap) {
                list[j] = list[j - gap];
            }
            list[j] = temp;
        }
    }
}

// Analisis de tiempos de ejecucion
void Analisis() {
    cout << "\nGenerando analisis de tiempos en nanosegundos...\n\n";
    cout << "algoritmo, tipo de dato, tiempo1000, tiempo10000, tiempo100000\n";
    
    string tipos[3] = {"int", "float", "double"};
    int tamanos[3] = {1000, 10000, 100000};
    string algoritmos[7] = {"SwapSort", "SelectionSort", "BubbleSort", "InsertionSort", "MergeSort", "QuickSort", "ShellSort"};
    
    // iterar sobre los tipos de datos y los algoritmos
    for (int t = 0; t < 3; t++) {
        for (int a = 0; a < 7; a++) {
            cout << algoritmos[a] << ", " << tipos[t];
            
            for (int tam = 0; tam < 3; tam++) {
                vector<double> vd; vector<int> vi; vector<float> vf;
                long long comps = 0, swaps = 0;
                
                auto start = high_resolution_clock::now();
                auto stop = start;
                
                if (tipos[t] == "int") {
                    vi = generarVectorAleatorio<int>(tamanos[tam], "int");
                    start = high_resolution_clock::now();
                    if(a==0) swapSort(vi, comps, swaps);
                    else if(a==1) selectionsort(vi, comps, swaps);
                    else if(a==2) bubbleSort(vi, comps, swaps);
                    else if(a==3) insertionsort(vi, comps, swaps);
                    else if(a==4) mergesort(vi, 0, vi.size()-1);
                    else if(a==5) quicksort(vi, 0, vi.size()-1);
                    else if(a==6) shellSort(vi);
                    stop = high_resolution_clock::now();
                } else if (tipos[t] == "float") {
                    vf = generarVectorAleatorio<float>(tamanos[tam], "float");
                    start = high_resolution_clock::now();
                    if(a==0) swapSort(vf, comps, swaps);
                    else if(a==1) selectionsort(vf, comps, swaps);
                    else if(a==2) bubbleSort(vf, comps, swaps);
                    else if(a==3) insertionsort(vf, comps, swaps);
                    else if(a==4) mergesort(vf, 0, vf.size()-1);
                    else if(a==5) quicksort(vf, 0, vf.size()-1);
                    else if(a==6) shellSort(vf);
                    stop = high_resolution_clock::now();
                } else {
                    vd = generarVectorAleatorio<double>(tamanos[tam], "double");
                    start = high_resolution_clock::now();
                    if(a==0) swapSort(vd, comps, swaps);
                    else if(a==1) selectionsort(vd, comps, swaps);
                    else if(a==2) bubbleSort(vd, comps, swaps);
                    else if(a==3) insertionsort(vd, comps, swaps);
                    else if(a==4) mergesort(vd, 0, vd.size()-1);
                    else if(a==5) quicksort(vd, 0, vd.size()-1);
                    else if(a==6) shellSort(vd);
                    stop = high_resolution_clock::now();
                }
                
                auto duration = duration_cast<nanoseconds>(stop - start);
                cout << ", " << duration.count();
            }
            cout << "\n";
        }
    }
}

int main() {
    int opt;
    do {
        cout << "\nEliga una opcion del menu:\n";
        cout << "1 Ordenar lista individualmente\n";
        cout << "2 Generar reporte de tiempos (Analisis comparativo)\n";
        cout << "3 Salir\n";
        cout << "Opcion: ";
        cin >> opt;
        
        if (opt == 1) {
            int n, alg, tipoNum;
            cout << "Cantidad de datos (1000, 10000, 100000): "; cin >> n;
            cout << "Tipo de dato (1: int, 2: float, 3: double): "; cin >> tipoNum;
            cout << "Eliga algoritmo de ordenamiento:\n";
            cout << "1 SwapSort\n2 SelectionSort\n3 BubbleSort\n4 InsertionSort\n5 MergeSort\n6 QuickSort\n7 ShellSort\n";
            cin >> alg;
            
            vector<int> vi; vector<float> vf; vector<double> vd;
            long long comps = 0, swaps = 0;
            auto start = high_resolution_clock::now();
            auto stop = start;
            
            if (tipoNum == 1) {
                vi = generarVectorAleatorio<int>(n, "int");
                start = high_resolution_clock::now();
                if(alg==1) swapSort(vi, comps, swaps);
                else if(alg==2) selectionsort(vi, comps, swaps);
                else if(alg==3) bubbleSort(vi, comps, swaps);
                else if(alg==4) insertionsort(vi, comps, swaps);
                else if(alg==5) mergesort(vi, 0, n-1);
                else if(alg==6) quicksort(vi, 0, n-1);
                else shellSort(vi);
                stop = high_resolution_clock::now();
                cout << "Lista Ordenada: "; imprimirVector(vi);
            } else if (tipoNum == 2) {
                vf = generarVectorAleatorio<float>(n, "float");
                start = high_resolution_clock::now();
                if(alg==1) swapSort(vf, comps, swaps);
                else if(alg==2) selectionsort(vf, comps, swaps);
                else if(alg==3) bubbleSort(vf, comps, swaps);
                else if(alg==4) insertionsort(vf, comps, swaps);
                else if(alg==5) mergesort(vf, 0, n-1);
                else if(alg==6) quicksort(vf, 0, n-1);
                else shellSort(vf);
                stop = high_resolution_clock::now();
                cout << "Lista Ordenada: "; imprimirVector(vf);
            } else {
                vd = generarVectorAleatorio<double>(n, "double");
                start = high_resolution_clock::now();
                if(alg==1) swapSort(vd, comps, swaps);
                else if(alg==2) selectionsort(vd, comps, swaps);
                else if(alg==3) bubbleSort(vd, comps, swaps);
                else if(alg==4) insertionsort(vd, comps, swaps);
                else if(alg==5) mergesort(vd, 0, n-1);
                else if(alg==6) quicksort(vd, 0, n-1);
                else shellSort(vd);
                stop = high_resolution_clock::now();
                cout << "Lista Ordenada: "; imprimirVector(vd);
            }
            
            auto duration = duration_cast<nanoseconds>(stop - start);
            cout << "Tiempo de ejecucion: " << duration.count() << " ns\n";
            
            if (alg >= 1 && alg <= 4) {
                cout << "Comparaciones: " << comps << "\n";
                cout << "Intercambios: " << swaps << "\n";
            }
            
        } else if (opt == 2) {
            Analisis();
        }
    } while (opt != 3);
    
    return 0;
}