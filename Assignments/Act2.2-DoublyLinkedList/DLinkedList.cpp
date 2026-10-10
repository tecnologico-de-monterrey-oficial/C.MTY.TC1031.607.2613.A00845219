#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include "Node2.h"

using namespace std;

template <typename T>
class DoublyLinkedList {
private:
    Node2<T>* head;
    Node2<T>* tail;
    int size = 0;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}
    void addFirst(T data);
    void addLast(T data);
    void insert(int index, T data);
    bool deleteAt (int index);
    int findData (T data);
    bool deleteData (T data);
    T getData(int index);
    void updateData(T oldData, T newData);
    void updateAt(int index, T newData);
    T& operator[](int index);
    DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& other);
    void clear();
    void Bubblesort();
    void duplicate();
    void removeDuplicates();
    void print(); 
};

template <typename T>
void DoublyLinkedList<T>::addFirst(T data) {
    // validamos si la lista esta vacia
    if (head == nullptr) {
        // si esta vacía la lista
        // apunto head a un nuevo nodo con data
        head = new Node2<T>(data);
        // apunto tail a head
        tail = head;
        size++;
    } else {
        // lista no vacia
        // creamos un nuevo nodo
        Node2<T>* aux = new Node2<T>(data);
        // apuntamos el next de aux a head
        aux->next = head;
        // apuntamos el prev de head a aux
        head->prev = aux;
        // apuntamos head a aux
        head = aux;
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::addLast(T data) {
    // validar la lista
    if (head == nullptr) {
        // lista vacia
        // apunto head a un nuevo nodo con data
        head = new Node2<T>(data);
        // apunto tail a head
        tail = head;
        size++;
    } else {
        // la lista no está vacía
        // creamos un nuevo nodo
        Node2<T>* aux = new Node2<T>(data);
        // apuntamos el prev de aux a tail
        aux->prev = tail;
        // apuntamos el next de tail a aux
        tail->next = aux;
        // apuntamos tail a aux
        tail = aux;
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::insert(int index, T data) {
    // validamos que él índice sea válido
    if (index >= 0 && index <= size-1) {
        // validamos que el indice sea desde 0 hasta el penúltimo
        if (index != size-1) {
            // el index es desde 0 hasta el penúltimo (en medio)
            // creamos un indice auxiliar igual a 0
            int auxIndex = 0;
            // creamos un apuntador auxiliar igual a head
            Node2<T>* aux = head;
            // iteramos hasta encontrar el índice dato
            while (auxIndex < index) {
                // recorremos aux
                aux = aux->next;
                // incrementamos el indice auxiliar
                auxIndex++;
            }
            // creamos un nodo nuevo
            Node2<T>* auxNew = new Node2<T>(data);
            // el prev del nuevo lo apuntamos a aux
            auxNew->prev = aux;
            // el next del nuevo lo apuntamos a aux->next
            auxNew->next = aux->next;
            // el prev del siguiente de aux lo apuntamos al nuevo
            aux->next->prev = auxNew;
            // apuntamos aux next al nuevo
            aux->next = auxNew;
            // incrmenetamos size
            size++;
        } else {
            // el index es igual a size -1
            // hacemos como si fuera addLast
            // creamos un nuevo nodo
            Node2<T>* aux = new Node2<T>(data);
            // apuntamos el prev de aux a tail
            aux->prev = tail;
            // apuntamos el next de tail a aux
            tail->next = aux;
            // apuntamos tail a aux
            tail = aux;
            size++;
        }
    } else {
        throw out_of_range("Índice inválido");
    }
}

template <typename T>
bool DoublyLinkedList<T>::deleteAt(int index) {
    // validar si el indice es valido
    if (index >= 0 && index < size) {
        // validar si hay solo un elemento
        if  (head->next == nullptr) {
            // solo hay un elemento
            // creamos un nodo auxiliar
            Node2<T>* aux=head;
            // apuntar a head y tail
            head = nullptr;
            tail = nullptr;
            // liberar aux
            delete aux;
            size--;
            return true;

        } else {
            // caso hay mas de un elemento en lista
            if (index == 0) {
                Node2<T>* aux =head;
                // apuntar head a sig elemento
                head= head->next;
                // apuntar head al previo
                head->prev = nullptr;
                delete aux; // liberar aux
                // reducir size
                size--;
                return true;
            } else {
                if (index == size - 1) {
                    // borrar ultimo
                    // creamos un nodo auxiliar que apunte a tail
                    Node2<T>* aux = tail;
                    // apuntamos tail al elemento previo
                    tail = tail->prev;
                    // actualizamos el apuntador prev de head
                    tail->next = nullptr;
                    // liberamos aux
                    delete aux;
                    size--;
                    return true; 
                } else {
                    if (index  <= (size-1)/2) {
                        // por al izq
                        // indice
                        int auxIndex = 1;
                        // crear apuntardor auxiliar
                        Node2<T>* aux = head->next;
                        // recorrer lista mientras auxIndex menor que index
                        while (auxIndex < index) {
                            aux = aux->next;
                            // sumar auxIndex
                            auxIndex++;
                        }
                        //llegamos al nodo deseado
                        // aux->prev que apunte a aux->next
                        aux->prev->next = aux->next;
                        // aux->next que apunte a aux->prev
                        aux->next->prev = aux->prev;
                        delete aux;
                        size--;
                        return true;
                    } else {
                        // derecha
                        int auxIndex = size - 2;
                        Node2<T>* aux = tail->prev;
                        // recorrer lista mientras auxIndex mayor que index
                        while (auxIndex > index) {
                            aux = aux->prev;
                            auxIndex--;
                        }
                        // llegamos al nodo deseado
                        // aux->prev que apunte a aux->next
                        aux->prev->next = aux->next;
                        // aux->next que apunte a aux->prev
                        aux->next->prev = aux->prev;
                        delete aux;
                        size--;
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

template <typename T>
int DoublyLinkedList<T>::findData(T data) {
    // recorrer la lista desde head hasta tail
    Node2<T>* aux = head;
    int index = 0;
    while (aux != nullptr) {
        // si el dato es igual al dato del nodo actual, retornamos el índice
        if (aux->data == data) return index;
        aux = aux->next;
        index++;
    }
    return -1;
}

template <typename T>
bool DoublyLinkedList<T>::deleteData(T data) {
    // buscamos el índice del dato
    int index = findData(data);
    // si el índice es diferente de -1 llama a deleteAt con ese indice
    if (index != -1) {
        return deleteAt(index);
    }
    return false;
}

template <typename T>
T DoublyLinkedList<T>::getData(int index) {
    // validar indice
    if (index < 0 || index >= size) throw out_of_range("Índice inválido");
    // creamos un apuntador auxiliar que apunte a head
    Node2<T>* aux = head;
    for (int i = 0; i < index; i++) aux = aux->next;
    // retornamos el dato del nodo en el indice dado
    return aux->data;
}

template <typename T>
void DoublyLinkedList<T>::updateData(T oldData, T newData) {
    // recorremos la lista desde head hasta tail
    Node2<T>* aux = head;
    // buscamos el nodo que contenga oldData
    while (aux != nullptr) {
        if (aux->data == oldData) {
            aux->data = newData;
            return;
        }
        aux = aux->next;
    }
    throw out_of_range("Dato no encontrado");
}

template <typename T>
void DoublyLinkedList<T>::updateAt(int index, T newData) {
    // validar indice
    if (index < 0 || index >= size) throw out_of_range("Índice inválido");
    // creamos un apuntador auxiliar que apunte a head
    Node2<T>* aux = head;
    // recorremos la lista hasta el índice dado
    for (int i = 0; i < index; i++) aux = aux->next;
    aux->data = newData;
}

template <typename T>
T& DoublyLinkedList<T>::operator[](int index) {
    // validar indice
    if (index < 0 || index >= size) throw out_of_range("Índice inválido");
    // creamos un apuntador auxiliar que apunte a head
    Node2<T>* aux = head;
    // recorremos la lista hasta el índice dado
    for (int i = 0; i < index; i++) aux = aux->next;
    return aux->data;
}

template <typename T>
DoublyLinkedList<T>& DoublyLinkedList<T>::operator=(const DoublyLinkedList<T>& other) {
    // comprobamos si no es la misma lista
    if (this != &other) {
        clear();
        Node2<T>* aux = other.head;
        while (aux != nullptr) {
            addLast(aux->data);
            aux = aux->next;
        }
    }
    return *this;
}

template <typename T>
void DoublyLinkedList<T>::clear() {
    // liberamos la memoria de todos los nodos
    // prevenimos leaks
    while (head != nullptr) {
        Node2<T>* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    size = 0;
}

template <typename T>
void DoublyLinkedList<T>::Bubblesort() {
    // definimos un booleano como verdadero
    bool change = true;
    // iterar desde n hasta 1
    for (int i = size-1; i>0 && change; i--) {
        // cambio el valor de change a falso
        change = false;
        // iteramos desde 0 hasta qu sea menor que i
        for (int j=0; j<i; j++) {
            // comparamos el valor de j con el valor de j+1 para determinar si es mayor
            if ((*this)[j] > (*this)[j+1]) {
                // si es mayor
                // cambiamos change a verdadero
                change = true;
                // intercambiamos los valores
                swap((*this)[j], (*this)[j+1]);
            }
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::duplicate() {
    // duplicar cada elemento de la lista
    Node2<T>* aux = head;
    while (aux != nullptr) {
        Node2<T>* duplicateNode = new Node2<T>(aux->data);
        // apuntamos el prev del nodo duplicado a aux
        duplicateNode->prev = aux;
        // apuntamos el next del nodo duplicado al siguiente de aux
        duplicateNode->next = aux->next;
        
        if (aux->next != nullptr) {
            aux->next->prev = duplicateNode;
        }
        else {
            tail = duplicateNode;
        }
        // apuntamos el next de aux al nodo duplicado
        aux->next = duplicateNode;
        // avanzamos aux al siguiente nodo original
        aux = duplicateNode->next;
        size++;
    }
}

template <typename T>
void DoublyLinkedList<T>::removeDuplicates() {
    // si la lista esta vacia, no hay duplicados que eliminar
    if (head == nullptr) return;
    // sorteamos la lista los duplicados estaran juntos
    Bubblesort(); 
    Node2<T>* aux = head;
    // recorremos la lista mientras aux->next no sea nullptr
    while (aux->next != nullptr) {
        if (aux->data == aux->next->data) {
            Node2<T>* duplicate = aux->next;
            aux->next = duplicate->next;
            if (duplicate->next != nullptr) duplicate->next->prev = aux;
            else tail = aux;
            delete duplicate;
            size--;
        } else {
            aux = aux->next;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::print() {
    // recorremos la lista desde head hasta tail
    Node2<T>* aux = head;
    // imprimimos los datos de cada nodo
    while (aux != nullptr) {
        // imprimimos el dato del nodo actual
        cout << aux->data << " <-> ";
        aux = aux->next;
    }
    cout << "NULL" << endl;
}

void mostrarMenu() {
    cout << "\n--- MENU DOUBLY LINKED LIST ---" << endl;
    cout << "1. Agregar elemento al principio (addFirst)" << endl;
    cout << "2. Agregar elemento al final (addLast)" << endl;
    cout << "3. Insertar elemento en indice (insert)" << endl;
    cout << "4. Borrar elemento dado (deleteData)" << endl;
    cout << "5. Borrar elemento en posicion (deleteAt)" << endl;
    cout << "6. Obtener elemento de posicion (getData)" << endl;
    cout << "7. Actualizar elemento dado (updateData)" << endl;
    cout << "8. Actualizar elemento en posicion (updateAt)" << endl;
    cout << "9. Encontrar elemento (findData)" << endl;
    cout << "10. Usar operador [] para leer y actualizar" << endl;
    cout << "11. Duplicar lista (Operador =)" << endl;
    cout << "12. Limpiar lista (clear)" << endl;
    cout << "13. Ordenar lista (Bubblesort)" << endl;
    cout << "14. Duplicar cada elemento (duplicate)" << endl;
    cout << "15. Remover duplicados (removeDuplicates)" << endl;
    cout << "16. Mostrar lista" << endl;
    cout << "0. Salir" << endl;
    cout << "Opcion: ";
}

int main() {
    DoublyLinkedList<int> lista;
    DoublyLinkedList<int> copiaLista;
    int opcion, val, index, val2;
    srand(time(0));

    cout << "Desea crear la lista con datos aleatorios? (1 = Si, 0 = Capturar manualmente): ";
    cin >> opcion;
    if (opcion == 1) {
        for (int i = 0; i < 5; i++) {
            lista.addLast(rand() % 100);
        }
        cout << "Lista aleatoria generada." << endl;
    }

    do {
        mostrarMenu();
        cin >> opcion;
        
        try {
            if (opcion == 1) {
                cout << "Valor a agregar al principio: "; cin >> val;
                lista.addFirst(val);
            } 
            else if (opcion == 2) {
                cout << "Valor a agregar al final: "; cin >> val;
                lista.addLast(val);
            } 
            else if (opcion == 3) {
                cout << "Indice: "; cin >> index;
                cout << "Valor: "; cin >> val;
                lista.insert(index, val);
            } 
            else if (opcion == 4) {
                cout << "Valor a borrar: "; cin >> val;
                if(lista.deleteData(val)) cout << "Borrado exitoso.\n";
                else cout << "Elemento no encontrado.\n";
            } 
            else if (opcion == 5) {
                cout << "Indice a borrar: "; cin >> index;
                lista.deleteAt(index);
            } 
            else if (opcion == 6) {
                cout << "Indice a obtener: "; cin >> index;
                cout << "Valor: " << lista.getData(index) << endl;
            } 
            else if (opcion == 7) {
                cout << "Valor a actualizar: "; cin >> val;
                cout << "Nuevo valor: "; cin >> val2;
                lista.updateData(val, val2);
            } 
            else if (opcion == 8) {
                cout << "Indice a actualizar: "; cin >> index;
                cout << "Nuevo valor: "; cin >> val2;
                lista.updateAt(index, val2);
            } 
            else if (opcion == 9) {
                cout << "Valor a buscar: "; cin >> val;
                index = lista.findData(val);
                if(index != -1) cout << "Encontrado en indice: " << index << endl;
                else cout << "No encontrado.\n";
            } 
            else if (opcion == 10) {
                cout << "Indice a leer usando []: "; cin >> index;
                cout << "Valor actual: " << lista[index] << endl;
                cout << "Ingrese nuevo valor para esta posicion: "; cin >> val;
                lista[index] = val; 
            } 
            else if (opcion == 11) {
                copiaLista = lista;
                cout << "Lista duplicada en nueva variable. Mostrando copia:\n";
                copiaLista.print();
            } 
            else if (opcion == 12) {
                lista.clear(); 
                cout << "Lista limpiada.\n";
            } 
            else if (opcion == 13) {
                lista.Bubblesort(); 
                cout << "Lista ordenada.\n";
            } 
            else if (opcion == 14) {
                lista.duplicate(); 
                cout << "Elementos duplicados.\n";
            } 
            else if (opcion == 15) {
                lista.removeDuplicates(); 
                cout << "Duplicados removidos.\n";
            } 
            else if (opcion == 16) {
                lista.print();
            } 
            else if (opcion == 0) {
                cout << "Saliendo del programa..." << endl;
            } 
            else {
                cout << "Opcion no valida. Intente de nuevo." << endl;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
        }
        
    } while (opcion != 0);

    return 0;
}