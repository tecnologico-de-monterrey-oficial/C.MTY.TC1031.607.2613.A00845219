#ifndef Linkedlist_h
#define Linkedlist_h

#include "Node.h"

template <typename T>
class Linkedlist {
private:
    std::unique_ptr<Node<T>> head;
    int size;
public:
    Linkedlist(); : head(nullptr), size(0) {}
    void push_front(T data);
    void push_back(T data);
    void print();
};

template <typename T>
Linkedlist<T>::Linkedlist() {

}

template <typename T>
void Linkedlist<T>::push_front(T data) {
    // crear nuevo nodo
    std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(data);
    // actualizar el siguiente del nuevo nodo al nodo actual
    newNode->next = std::move(head);
    // actualizar head del nuevo nodo
    head = std::move(newNode);
}

template <typename T>
void Linkedlist<T>::print() {
    // crear pointer auxiliar que apunte a head
    Node<T>* aux = head;
    // recorrer la lista hasta que aux sea diferente de nullptr
    while (aux!= nullptr) {
        std::cout << aux->data << " ";
        aux = aux->next;
    }
    std::cout << std::endl;
}

#endif