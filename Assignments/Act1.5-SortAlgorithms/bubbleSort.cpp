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

int main() {
    // lista a ordenar
    vector<int>unlista = {15, 7, 9, 3, 12, 5, 2};
    // funcion
    bubbleSort(unlista);
    cout<<"Lista Ordenada: ";
    for (int num : unlista) {
        cout<< num<< " ";
    }
    cout<<"\n";
    return 0;
}