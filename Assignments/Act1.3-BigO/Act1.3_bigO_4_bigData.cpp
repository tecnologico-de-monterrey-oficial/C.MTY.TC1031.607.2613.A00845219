#include <iostream>
#include <vector>
using namespace std;

int sumImparesIter(const vector<int>& arr) {
    int suma = 0;
    // repetir una division entre 2 y si nunca da 0 es impar
    for (int num : arr) {
        if (num % 2 != 0) {
            suma += num;
        }
    }
    return suma;
}

int sumImparesRecur(const vector<int>& arr, size_t index = 0) {
    if (index == arr.size()) {
        return 0;
    }
    // verificar el numero
    if (arr[index] % 2 != 0) {
        // caso impar se suma y vuelve a repetir 
        return arr[index] + sumImparesRecur(arr, index + 1);
    } else {
        // si no es impar solo se llama la recursion para llegar a 0
        return sumImparesRecur(arr, index + 1);
    }
}

int main() {
    vector<int> lista = {1, 2, 3, 4, 5, 6, 7, 8, 9}; 
    // Se recorrera la lista y solo se sumaran los impares (25)
    cout<< "Suma iterativa: " <<sumImparesIter(lista) << "\n";
    cout<< "Suma recursiva: " <<sumImparesRecur(lista) << "\n";
    
    return 0;
}