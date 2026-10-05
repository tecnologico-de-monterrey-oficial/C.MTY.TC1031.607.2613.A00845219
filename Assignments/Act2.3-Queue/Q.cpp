#include <iostream>
#include <string>
#include <memory>

using namespace std;

// clase cliente
struct Cliente {
    string nombre;
    int boletos;

    Cliente(string n, int b) : nombre(n), boletos(b) {}
};

// clase nodo
template <typename T>
struct Node {
    T dato;
    std::unique_ptr<Node<T>> next;

    Node(T valor) : dato(valor), next(nullptr) {}
};


// Clase queue
template <typename T>
class Queue {
    Nodo<T>* front;
    Nodo<T>* rear;
public: 
    Queue() : front(nullptr), rear(nullptr) {}
    // destructor de memmoria dinamica
    ~Queue() {
        while (!isEmpty()) {
            pop();
        }
    }
    // elemento al final de la fila
    void push (T valor) {
        Nodo<T>* newNode = new Nodo<T>(valor);
        is (isEmpty()) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }
    void Queue<T>::pop() {
        // ver que no este vacio
        if (front != nullptr) {
            // ver que haya solo un elemento
            if (front == rear) {
                // apuntador auxilar 
                Node<T>* aux=front;
                delete aux;
                front = nullptr;
                rear = nullptr;
            }
        }
        else {
            // apuntar a un nuevo nodo
            front = new Node<T>(valor);
            rear = front;
        }
    }
};