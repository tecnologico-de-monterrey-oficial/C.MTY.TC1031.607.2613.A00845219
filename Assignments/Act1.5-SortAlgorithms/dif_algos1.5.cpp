#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
void bubbleSort(vector<T> &list) {
    // definimos un booleano como verdadero
    bool change = true;
    // iterar desde n hasta 1
    for (int i=list.size()-1; i>0 && change; i--) {
        // cambio el valor de change a falso
        change = false;
        // iteramos desde 0 hasta qu sea menor que i
        for (int j=0; j<i; j++) {
            // comparamos el valor de j con el valor de j+1 para determinar si es mayor
            if (list[j] > list[j+1]) {
                // si es mayor
                // cambiamos change a verdadero
                change = true;
                // intercambiamos los valores
                swap(list[j], list[j+1]);
            }
        }
    }
}

template <typename T>
void selectionsort(vector<T> &list) {
    int n = list.size();
    // recorremos la lista desde el inicio
    for (int i=0; i<n-1; i++) {
        // valor minimo (menor) es i
        int minIndex = i;
        for (int j=i+1; j<n; j++) {
            // comparamos el valor de j con el valor de minIndex para determinar si es menor
            if (list[j] < list[minIndex]) {
                minIndex = j;
            }
        }
        swap(list[i], list[minIndex]);
    }
}

template <typename T>
void insertionsort(vector<T> &list) {
    int n = list.size();
    // recorremos la lista desde el inicio
    for (int i=1; i<n; i++) {
        int j = i-1;
        // mientras j sea mayor o igual a 0 y el valor de j sea mayor que 0
        while (j > 0 && list[j] < list[j - 1]) {
            // movemos el valor de j a la izquierda
            swap(list[j], list[j - 1]);
            j--;
        }
        // colocamos key en su lugar correspondiente
        list[j+1] = 0;
    }
}

int main() {
    // lista a ordenar
    vector<int>unlista = {15, 7, 9, 3, 12, 5, 2};
    // funciones
    cout<<"Eliga algoritmo de ordenamiento\n"<<endl;
    cout<<"1 Bubble sort\n2 Selection sort\n3 Insertion sort"<<endl;
    cout<<"Cualquier otra opcion arrojara error o la lista sin ordenar"<<endl;
    int opt;
    cin>>opt;
    if (opt==1) {
        bubbleSort(unlista);
    }
    else if (opt==2){
        selectionsort(unlista);
    }
    else if (opt==3){
        insertionsort(unlista);
    }
    cout<<"Lista Ordenada: ";
    for (int num : unlista) {
        cout<< num<< " ";
    }
    cout<<"\n";
    return 0;
}