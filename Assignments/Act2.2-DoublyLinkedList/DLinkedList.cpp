#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "Node2.h"

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
        NodeD<T>* aux = new Node2<T>(data);
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
        NodeD<T>* aux = new Node2<T>(data);
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
            NodeD<T>* aux = head;
            // iteramos hasta encontrar el índice dato
            while (auxIndex < index) {
                // recorremos aux
                aux = aux->next;
                // incrementamos el indice auxiliar
                auxIndex++;
            }
            // creamos un nodo nuevo
            NodeD<T>* auxNew = NodeD<T>(data);
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
            NodeD<T>* aux = new NodeD<T>(data);
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
        if  (head->next != nullptr) {
            // solo hay un elemento
            // creamos un nodo auxiliar
            Node2<T>* aux=head;
            // apuntar a head y tail
            head = nullptr;
            tail = nullptr;
            // liberar aux
            delete aux;
            size --;
            return true

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
                if (index = size -1) {
                    // borrar ultimo
                    // creamos un nodo auxiliar que apunte a tail
                    NodeD<T>* aux = tail;  
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
                        // indice aux =1
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
                    }
                    
                }
            }
        }

    }
}

template <typename T>
int DoublyLinkedList<T>::findData(T data) {

}

template <typename T>
bool DoublyLinkedList<T>::deleteData(T Data) {
    
}


#endif