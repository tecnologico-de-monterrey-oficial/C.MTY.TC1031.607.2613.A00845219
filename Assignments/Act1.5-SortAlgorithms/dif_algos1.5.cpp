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
        /* colocamos key en su lugar correspondiente
        list[j+1] = 0; Se elimino para que funcione correctamente, reemplazaba valores con 0*/   
    }
}

template <typename T>
int getPivot(vector<T> &list, int left, int right) {
    // creamos una variable auxiliar con el valor de left -1
    int aux= left-1;
    // creamos una variable pivot con el valor de right
    int pivot= right;
    // iterar desde left hasta pivot -1 (<pivot)
    for(int i=left; i<pivot; i++) {
        // comparar si el valor de pivot> al valor de i (left)
        if(list[i] < list[pivot]) {
            // incrementar valor i
            aux++;
            // intercambiar aux con i
            swap(list[aux], list[i]);
        }
    }
    // incrementar aux
    aux++;
    // cambiar aux con pivot
    swap(list[aux], list[pivot]);
    return aux;
}

template <typename T>
void quicksort(vector<T> &list, int left, int right) {
    // se ejecuta la recursividad si left <right
    if(left< right) {
        int pivot = getPivot(list, left, right);
        // ordenamos la lista del lado izq de pivote
        quicksort(list, left, pivot-1);
        // ordenar la lista del lado del pivote
        quicksort(list, pivot +1, right);
    }
}

template <typename T>
void merge(vector<T> &list, int left, int mid, int right) {
    // generamos la lista de left a mid
    // crear lista para valores de lado izq
    vector<T> leftList;
    // iterar lista de left a mid
    for (int i=left; i<=mid; i++){
        leftList.push_back(list[i]);

    }
    // generar lista de mid+1 a left
    vector<T> rightList;
    // iterar lista de left a mid
    for (int j=mid+1; j<=right; i++) {
        rightList.push_back(list[j]);
    }
    // combinar listas
    // variable index que contiene valor para actualizar
    int index = left;
    // iniciar index del lado izq
    int i=0;
    // iniciar index del lado derecho
    int j=0;
    // iterar mientras hayan listas
    while (i<leftList.size() && j<rightList.size()) {
        // comparar valor i de leftList con valor de j de rightList
        if (leftList[i]<rightList[j]){
            // actualizar index con el valor de leftList
            list[index] = leftList[i];
            // incrementamos i
            i++;
        }
        else {
            // actualizar index con el valor de rightList
            list[index] = rightList[j];
            // incrementamos j
            j++;
        }
        index++;
    }
    while (j<rightList.size()) {
        // actualizamos list en index con el valor de 
    }
}

template <typename T>
void mergesort(vector<T> &list, int left, int right) {
    // condicion de control es left < right
    if(left <right) {
        //calc mid
        int mid = (left + right)/2;
        // ordenar de left a mid
        mergesort(list[left], list[mid]);

    }
}

int main() {
    // lista a ordenar
    vector<int>unlista = {15, 7, 9, 3, 12, 5, 2};
    // funciones
    cout<<"Eliga algoritmo de ordenamiento\n"<<endl;
    cout<<"1 Bubble sort\n2 Selection sort\n3 Insertion sort\n4 Quick sort"<<endl;
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
    else if (opt==4) {
        quicksort(unlista, 0, unlista.size() -1);
    }
    cout<<"Lista Ordenada: ";
    for (int num : unlista) {
        cout<< num<< " ";
    }
    cout<<"\n";
    return 0;
}