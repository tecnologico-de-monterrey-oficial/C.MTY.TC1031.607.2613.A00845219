#include <iostream>
#include <vector>
using namespace std;

template <typename T>
void swapSort(vector<T> &list) {
    int n = list.size();
    // algoritmo, recorrer lista
    for (int i=0; i<n -1; i++)
        for (int j=0; j<n -i -1; j++)
            if (list[j]> list[j + 1]) {
                swap(list[j], list[j +1]);
            }
};


int main() {
    // lista a ordenar
    vector<int>unlista = {15, 7, 9, 3, 12, 5, 2};
    // funcion
    swapSort(unlista);
    cout<<"Lista Ordenada: ";
    for (int num : unlista) {
        cout<< num<< " ";
    }
    cout<<"\n";
    return 0;
}

