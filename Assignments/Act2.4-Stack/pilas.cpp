#include <iostream>
#include <string>
#include <memory>

using namespace std;

// clase para almacenar info de PaginaWeb
struct PaginaWeb {
        string titulo;
        string url;
};

// Nodo para construir el Stack dinámico
template <typename T>
struct Node {
    T data;
    Node* next;
    Node(T val) : data(val), next(nullptr) {}
};

// ADT stack 
template <typename T>
class Stack {
private:
    Node<T>* topNode;
    int count; // contador del stack

public:
    Stack() : topNode(nullptr), count(0) {}

    // destructor para liberar memoria
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // push hace que el nodo se agregue al tope del stack
    void push(T value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = topNode;
        topNode = newNode;
        count++;
    }

    // pop elimina el nodo del tope del stack y devuelve su valor
    T pop() {
        if (isEmpty()) {
            throw out_of_range("El stack está vacío.");
        }
        Node<T>* temp = topNode;
        T poppedValue = temp->data;
        topNode = topNode->next;
        delete temp;
        count--;
        return poppedValue;
    }

    // top devuelve el valor del nodo en el tope del stack sin eliminarlo
    T top() const {
        if (isEmpty()) {
            throw out_of_range("El stack está vacío.");
        }
        return topNode->data;
    }

    bool isEmpty() const {
        return topNode == nullptr;
    }

    int size() const {
        return count;
    }
};

// main-menu
int main() {
    Stack<PaginaWeb> historial, titulo;
    int opcion;

    do {
        cout << "\n--- Historial Web ---" << endl;
        cout << "1. Visitar una nueva pagina" <<endl;
        cout << "2. Retrodecer a la pagina anterior" << endl;
        cout << "3. Ver la pagina actual"<< endl;
        cout << "4. Mostrar cuantas paginas hay en el historial" << endl;
        cout << "5. Salir" <<endl;
        cout << "Elige una opcion: ";
        cin >> opcion;

        // validar que la entrada se sea un numero entero
        if (cin.fail()) {
            cin.clear(); // limpia el error
            cin.ignore(10000, '\n'); // limpia el buffer
            cout << ">> Entrada invalida" << endl;
            continue;
        }

        // visita a nueva pagina
        if (opcion==1) {
                PaginaWeb nuevaPag;
                cout << ">> Titulo de la pagina: ";
                getline(cin >> ws, nuevaPag.titulo);
                cout << ">> URL ";
                getline(cin >> ws, nuevaPag.url);
                historial.push(nuevaPag);
                cout << "[Exito] Pagina registrada en historial." << endl;;
            }
        // ir a la pagina anterior (ir a la fila 1 atras)
        else if (opcion==2) {
            try {
                PaginaWeb cerrada = historial.pop();
                cout << "[Atras] Se cerro la pagina: " << cerrada.titulo << " (" << cerrada.url << ")" << endl;
            } 
            catch (const out_of_range& e) {
                cout << "[Error] No hay paginas anteriores en el historial." << endl;
            };
            }
        // ver la pagina actual
        else if (opcion==3) {
            try {
                PaginaWeb actual = historial.top();
                cout << "[Actual] " << actual.titulo << " | URL: " << actual.url << endl;
            } 
            catch (const out_of_range& e) {
                cout << "[Info] El navegador esta en blanco. No hay paginas." << endl;
            };
        }
        // historial de paginas
        else if (opcion==4) {
            cout << "[Logs] Paginas en el historial: " << historial.size() << endl;;
        }
        else if (opcion==5) {
            cout << "Cerrando el navegador..." << endl;;
        }
        else {
            cout << "Error: Opción no valida" << endl;
        }
        
    } while (opcion != 5);
    return 0;
};