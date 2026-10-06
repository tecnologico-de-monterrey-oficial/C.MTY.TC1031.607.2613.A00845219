#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

// clase cliente
struct Cliente {
    string nombre;
    int boletos;

    // Se agrega un constructor por defecto para poder crear la variable en el main
    Cliente() : nombre(""), boletos(0) {}
    Cliente(string n, int b) : nombre(n), boletos(b) {}
};

// clase nodo 
template <typename T>
struct Node {
    T dato;
    Node<T>* next;
    Node(T valor) : dato(valor), next(nullptr) {}
};

// Clase queue
template <typename T>
class Queue {
private:
    Node<T>* frontNode; 
    Node<T>* rear;
    int count; // contador de elementos en la fila

public: 
    Queue() : frontNode(nullptr), rear(nullptr), count(0) {}
    
    // destructor de memoria dinamica
    ~Queue() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const {
        return frontNode == nullptr;
    }

    int getSize() const {
        return count;
    }

    // elemento al final de la fila
    void push(T valor) {
        Node<T>* newNode = new Node<T>(valor);
        if (isEmpty()) {
            frontNode = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
        count++;
    }

    // adaptado para regresar el valor y manejar correctamente la memoria
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Excepcion: No se pudo borrar, la fila esta vacia.");
        }
        
        Node<T>* aux = frontNode;
        T valor = aux->dato; // Guardamos el dato antes de borrar el nodo
        
        if (frontNode == rear) { // Si solo hay un elemento
            frontNode = nullptr;
            rear = nullptr;
        } else {
            frontNode = frontNode->next;
        }
        
        delete aux;
        count--;
        return valor;
    }

    // Obtener el elemento al frente sin borrarlo
    T front() {
        if (isEmpty()) {
            throw std::runtime_error("Excepcion: No hay datos en la fila.");
        }
        return frontNode->dato;
    }
};

// Función principal con tu Queue original y el menú con if / else if
int main() {
    Queue<Cliente> fila;
    int opcion;

    do {
        cout << "\n--- Fila de Boletos ---\n";
        cout << "1. Nuevo cliente se forma en la fila\n";
        cout << "2. Atender al siguiente cliente formado\n";
        cout << "3. Ver al siguiente cliente en la fila sin atenderlo aun\n";
        cout << "4. Mostrar cuantas personas quedan en la fila\n";
        cout << "5. Salir\n";
        cout << "Seleccione una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            Cliente newClient;
            cout << "Ingrese el nombre del cliente: ";
            cin >> ws; 
            getline(cin, newClient.nombre);
            cout << "Ingrese la cantidad de boletos que desea comprar: ";
            cin >> newClient.boletos;
            
            fila.push(newClient);
            cout << ">> " << newClient.nombre << " se ha formado en la fila\n";
        } 
        else if (opcion == 2) {
            try {
                Cliente clienteAtendido = fila.pop();
                cout << ">> Atendiendo a " << clienteAtendido.nombre 
                     << ". Ha comprado " << clienteAtendido.boletos << " boleto(s)\n";
                
                if (clienteAtendido.boletos >= 10) {
                    cout << "Se han comprado muchos boletos!" << endl;
                } 
                else if (clienteAtendido.boletos < 1) {
                    cout << "No se compraron boletos" << endl;
                }
            } catch (const runtime_error& e) {
                cout << ">> " << e.what() << "\n";
            }
        } 
        else if (opcion == 3) {
            try {
                Cliente siguiente = fila.front();
                cout << ">> El siguiente en la fila es " << siguiente.nombre 
                     << ", esperando comprar " << siguiente.boletos << " boleto(s)\n";
            } catch (const runtime_error& e) {
                cout << ">> " << e.what() << "\n";
            }
        } 
        else if (opcion == 4) {
            cout << ">> Personas esperando en la fila: " << fila.getSize() << "\n";
        } 
        else if (opcion == 5) {
            cout << ">> Saliendo del sistema de filas...\n";
        } 
        else {
            cout << ">> Opcion invalida. Intente nuevamente.\n";
        }

    } while (opcion != 5);

    return 0;
}