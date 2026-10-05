#include <iostream>
#include <string>
#include <stdexcept>
#include "Node2.h" // archivo de nodos

using namespace std;

// definir la clase Q
template <typename T>
class Queue {
private:
    // punteros al primer y ultimo nodo de Q
    // count contador para saber cuantos elementos hay en el Q
    NodeD<T>* head;
    NodeD<T>* tail;
    int count;

public:
    // constructor y destructor
    Queue() : head(nullptr), tail(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty()) {
            pop();
        }
    }

    // PUSH
    // Funcion agregar un elemento al Q
    void push(const T& element) {
        NodeD<T>* newNode = new NodeD<T>(element); 
        if (isEmpty()) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        count++;
    }

    // POP
    // Funcion que borra el primer elemento agregado al a Q y regresa su valor
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Error: No hay nadie en la fila");
        }
        NodeD<T>* temp = head;
        T value = temp->data;
        head = head->next;
        
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr; 
        }
        
        delete temp;
        count--;
        return value;
    }

    // FRONT
    // Funcion para agarrar el valor del primer elemento agregado al Q
    T front() {
        if (isEmpty()) {
            throw std::runtime_error("Error: No hay datos en la fila");
        }
        return head->data;
    }

    bool isEmpty() const {
        return count == 0;
    }

    int getSize() const {
        return count;
    }
};

// struct que representa un cliente 
// struct es publico por default
struct Cliente {
    string nombre;
    int boletos;
};

// main-menu
int main() {
    Queue<Cliente> fila;
    Cliente boletos;
    int opcion;
    // Agrega personas a la fila para luego atenderlas, 
    do {
        cout << "\n--- Fila de boletos ---\n";
        cout << "1. Nuevo cliente se forma en la fila\n";
        cout << "2. Atender al siguiente cliente formado\n";
        cout << "3. Ver al siguiente cliente en la fila sin atenderlo aun\n";
        cout << "4. Mostrar cuantas personas quedan en la fila\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        // nuevo cliente en la fila
        if (opcion == 1) {
            Cliente newClient;
            cout << "Ingrese el nombre del cliente: ";
            cin >> ws; // limpia la entrada
            getline(cin, newClient.nombre);
            cout << "Ingrese la cantidad de boletos que desea comprar: ";
            cin >> newClient.boletos;
            
            fila.push(newClient);
            cout << ">> " << newClient.nombre << " se ha formado en la fila.\n";
        } 
        // atender al cliente que sigue
        else if (opcion == 2) {
            try {
                Cliente clienteAtendido = fila.pop();
                cout << ">> Atendiendo a " << clienteAtendido.nombre 
                     << ". Ha comprado " << clienteAtendido.boletos << " boleto(s).\n";
                    if (clienteAtendido.boletos >= 10) {
                        cout << "Se han comprado muchos boletos!" << endl;
                    }
                    else if (clienteAtendido.boletos < 1) {
                        cout << "No se compraron boletos " << endl;
                    }
            } catch (const runtime_error& e) {
                cout << ">> " << e.what() << "\n";
            }
        } 
        // ver al siguiente cliente sin atenderlo
        else if (opcion == 3) {
            try {
                Cliente siguiente = fila.front();
                cout << ">> El siguiente en la fila es " << siguiente.nombre 
                     << ", esperando comprar " << siguiente.boletos << " boleto(s)\n";
            } catch (const runtime_error& e) {
                cout << ">> " << e.what() << "\n";
            }
        } 
        // ver cuantos quedan en la fila
        else if (opcion == 4) {
            cout << ">> Personas esperando en la fila: " << fila.getSize() << "\n";
        } 
        else if (opcion == 5) {
            cout << ">> Saliendo del sistema de filas... \n";
        } 
        else {
            cout << ">> Opcion invalida. Intente nuevamente \n";
        }

    } while (opcion != 5);
        return 0;
};