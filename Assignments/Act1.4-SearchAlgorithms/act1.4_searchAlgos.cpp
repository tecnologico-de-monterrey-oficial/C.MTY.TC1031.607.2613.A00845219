#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// busca secuencial
template <typename T>
int buscaSecuencial(const vector<T>& arr, int n, T x) {
    for (int i=0; i<n; i++) {
        if (arr[i]==x) {
            return i;
        }
    }
    return -1;
}

// busca binaria
template <typename T>
int buscaBinaria(const vector<T>& arr, int n, T x) {
    int izq = 0;
    int der = n - 1;
    while (izq <= der) {
        int mid = izq + (der - izq) / 2;    //mitad de la lista
        if (arr[mid] == x) {
            return mid;
        }
        if (arr[mid] < x) {
            izq = mid + 1;
        } else {
            der= mid - 1;
        }
    }
    return -1;
}

int main() {
    cout<<"Escoja su tipo de busqueda:\n 1. Secuencial\n 2. Binaria\n";
    int op;
    cin>>op;
    if (op == 1) {
        vector<int> arr = {2, 3, 4, 10, 40};
        int x = 10;
        int n = arr.size();
        if (buscaSecuencial(arr, n, x) != -1) {
            cout << "Elemento encontrado en el indice: " << buscaSecuencial(arr, n, x) << endl;
        } else {
            cout << "Elemento no encontrado" << endl;
        }   
    } else if (op == 2) {
        vector<int> arr = {2, 3, 4, 10, 21, 40, 42, 67, 69, 99, 100, 101, 420};    //Esto tiene que estar ordenado para funcionar binaria
        int x = 10;
        int n = arr.size();
        if (buscaBinaria(arr, n, x) != -1) {
            cout << "Elemento encontrado en el indice: " << buscaBinaria(arr, n, x) << endl;
        } else {
            cout << "Elemento no encontrado" << endl;
        }
    } else {
        cout << "Invalido" << endl;
        return 1;
    }
    

    return 0;
}