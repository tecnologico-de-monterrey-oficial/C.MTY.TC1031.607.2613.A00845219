#ifndef List_h
#define List_h

#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class List {
private:
    vector<T> data;
    int size;

public:
    List();
    void insert(T value);
    void removeLast();
    T getData(int pos);
    int getSize();
    T getMax();
    void print();
    void insertAt(int pos, T value);
    void removeAt(int pos);
};

template <typename T>
List<T>::List() {
    this->size = 0;
}

// pone valor al final e incrementa size
template <typename T>
void List<T>::insert(T value) {
    this->data.push_back(value);
    this->size++;
}

//imprime y elimina el último elemento
template <typename T>
void List<T>::removeLast() {
    if (this->size == 0) {
        cout << "NO HAY ELEMENTOS" << endl;
    } else {
        cout << this->data[this->size - 1] << endl;
        this->data.pop_back();
        this->size--;
    }
}

// regresa el contenido en la posición dada
template <typename T>
T List<T>::getData(int pos) {
    // Precondición: 0 <= pos < size
    return this->data[pos];
}

//regresa el valor de size
template <typename T>
int List<T>::getSize() {
    return this->size;
}

// regresa el valor mayor en la lista
template <typename T>
T List<T>::getMax() {
    T maxVal = this->data[0];
    for (int i = 1; i < this->size; i++) {
        if (this->data[i] > maxVal) {
            maxVal = this->data[i];
        }
    }
    return maxVal;
}

//Imprime la lista con formato [pos] con <dato>
template <typename T>
void List<T>::print() {
    for (int i = 0; i < this->size; i++) {
        cout<<"["<< i << "] - "<<this->data[i]<<endl;
    }
}

//Inserta en posición, recorre a la derecha e incrementa size
template <typename T>
void List<T>::insertAt(int pos, T value) {
    if (pos < 0 || pos > this->size) {
        cout <<"POSICIÓN INVÁLIDA"<<endl;
        return;
    }
    this->data.insert(this->data.begin() + pos, value);
    this->size++;
}

//Elimina el elemento en la posición dada recorre a la izquierda y disminuye size
template <typename T>
void List<T>::removeAt(int pos) {
    if (this->size ==0) {
        cout<<"NO HAY ELEMENTOS"<<endl;
        return;
    }
    if (pos < 0 || pos >= this->size) {
        cout<<"POSICIÓN INVÁLIDA"<<endl;
        return;
    }
    
    cout<<this->data[pos]<<endl;
    this->data.erase(this->data.begin() + pos);
    this->size--;
}

#endif