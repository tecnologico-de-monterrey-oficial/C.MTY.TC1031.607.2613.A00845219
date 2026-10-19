#ifndef Linkedlist_h
#define Linkedlist_h

#include "Node.h"
#include <iostream>
#include <stdexcept>
#include <memory> // para usar unique_ptr

template <typename T>
class Linkedlist {
private:
    std::unique_ptr<Node<T>> head;
    int size;
public:
    Linkedlist() : head(nullptr), size(0) {} 
    
    void push_front(T data);
    void push_back(T data);

    // funciones
    void insert_after(int index, T data);
    void delete_element(T data);
    void delete_at(int index);
    T get_at(int index) const;
    void update_element(T old_data, T new_data);
    void update_at(int index, T new_data);
    int find(T data) const;
    T& operator[](int index);
    
    void print(); 
    void print() const;
    
    // Operador = (duplica lista)
    Linkedlist<T>& operator=(const Linkedlist<T>& other);
};


template <typename T>
void Linkedlist<T>::push_front(T data) {
    // crear nuevo nodo
    std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(data);
    // actualizar el siguiente del nuevo nodo al nodo actual
    newNode->next = std::move(head);
    // actualizar head del nuevo nodo
    head = std::move(newNode);
    size++; // Se agregó para llevar control del tamaño
}

//push_back
template <typename T>
void Linkedlist<T>::push_back(T data) {
    std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(data);
    if (!head) {
        head = std::move(newNode);
    } else {
        Node<T>* aux = head.get();
        while (aux->next != nullptr) {
            aux = aux->next.get();
        }
        aux->next = std::move(newNode);
    }
    size++;
}

template <typename T>
void Linkedlist<T>::print() {
    // crear pointer auxiliar que apunte a head
    Node<T>* aux = head.get(); 
    // recorrer la lista hasta que aux sea diferente de nullptr
    while (aux!= nullptr) {
        std::cout << aux->data << " ";
        aux = aux->next.get(); // Se agregó .get()
    }
    std::cout << std::endl;
}

template <typename T>
void Linkedlist<T>::insert_after(int index, T data) {
        if (index < 0 || index >= size) throw std::out_of_range("Índice fuera de rango");
        Node<T>* aux = head.get();
        for (int i = 0; i < index; i++) {
            aux = aux->next.get();
        }
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(data);
        newNode->next = std::move(aux->next);
        aux->next = std::move(newNode);
        size++;
}

template <typename T>
void Linkedlist<T>::delete_element(T data) {
        if (!head) return;
        if (head->data == data) {
            head = std::move(head->next);
            size--;
            return;
        }
        Node<T>* aux = head.get();
        while (aux->next != nullptr && !(aux->next->data == data)) {
            aux = aux->next.get();
        }
        if (aux->next != nullptr) {
            aux->next = std::move(aux->next->next);
            size--;
    }
}

template <typename T>
void Linkedlist<T>::delete_at(int index) {
        if (index < 0 || index >= size) throw std::out_of_range("Índice fuera de rango");
        if (index == 0) {
            head = std::move(head->next);
        } else {
            Node<T>* aux = head.get();
            for (int i = 0; i < index - 1; i++) {
                aux = aux->next.get();
            }
            aux->next = std::move(aux->next->next);
        }
        size--;
}

template <typename T>
T Linkedlist<T>::get_at(int index) const {
        if (index < 0 || index >= size) throw std::out_of_range("Índice fuera de rango");
        Node<T>* aux = head.get();
        for (int i = 0; i < index; i++) aux = aux->next.get();
        return aux->data;
}

template <typename T>
void Linkedlist<T>::update_element(T old_data, T new_data) {
        Node<T>* aux = head.get();
        while (aux != nullptr) {
            if (aux->data == old_data) {
                aux->data = new_data;
                return;
            }
            aux = aux->next.get();
        }
}

template <typename T>
void Linkedlist<T>::update_at(int index, T new_data) {
        if (index < 0 || index >= size) throw std::out_of_range("Índice fuera de rango");
        Node<T>* aux = head.get();
        for (int i = 0; i < index; i++) aux = aux->next.get();
        aux->data = new_data;
}

template <typename T>
int Linkedlist<T>::find(T data) const {
        Node<T>* aux = head.get();
        int index = 0;
        while (aux != nullptr) {
            if (aux->data == data) return index;
            aux = aux->next.get();
            index++;
        }
        return -1; // No encontrado
}

// Sobrecarga [] que retorna referencia para obtener y actualizar
template <typename T>
T& Linkedlist<T>::operator[](int index) {
        if (index < 0 || index >= size) throw std::out_of_range("Índice fuera de rango");
        Node<T>* aux = head.get();
        for (int i = 0; i < index; i++) aux = aux->next.get();
        return aux->data;
}

template <typename T>
void Linkedlist<T>::print() const {
        Node<T>* aux = head.get();
        while (aux != nullptr) {
            std::cout << "[" << aux->data << "] -> ";
            aux = aux->next.get();
        }
        std::cout << "null\n";
}

// implementacion de sobrecarga de operador =
template <typename T>
Linkedlist<T>& Linkedlist<T>::operator=(const Linkedlist<T>& other) {
    if (this == &other) return *this; 
    head.reset();
    size = 0;
    Node<T>* aux = other.head.get();
    while (aux != nullptr) {
        push_back(aux->data);
        aux = aux->next.get();
    }
    return *this;
}

#endif