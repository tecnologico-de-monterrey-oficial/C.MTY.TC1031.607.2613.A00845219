#include <iostream>
#include <vector>

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

void selectionsort(vector<int> &list) {
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

int main() {
    // lista a ordenar
    vector<int>unlista = {15, 7, 9, 3, 12, 5, 2};
    // funciones
    cout<<"Eliga algoritmo de ordenamiento"<<endl;
    int opt;
    cin>>opt;
    if (opt==1) {
        bubbleSort(unlista);
    }
    else if (opt==2){
        
    }
    else if (opt==3){
        selectionsort(unlista);
    }
    cout<<"Lista Ordenada: ";
    for (int num : unlista) {
        cout<< num<< " ";
    }
    cout<<"\n";
    return 0;
}