#include <iostream>
#include <memory>
#include <cstdlib>
#include <ctime>
using namespace std;

#include "Fraccion.h"
#include "Linkedlist.h"

// menu2 para desplegar las opciones de la lista
template <typename T>
void desplegarMenu(Linkedlist<T>& lista) {
    int opcion;
    do {
        cout << "\n--- Operaciones en la Lista ---" << endl;
        cout << "1. Agregar elemento al principio" << endl;
        cout << "2. Agregar elemento al final" << endl;
        cout << "3. Insertar despues de indice" << endl;
        cout << "4. Borrar elemento dado" << endl;
        cout << "5. Borrar elemento en posicion" << endl;
        cout << "6. Obtener elemento en posicion (metodo get)" << endl;
        cout << "7. Actualizar elemento dado" << endl;
        cout << "8. Actualizar elemento en posicion" << endl;
        cout << "9. Encontrar un elemento" << endl;
        cout << "10. Usar operador [] (leer y sobreescribir)" << endl;
        cout << "11. Imprimir lista" << endl;
        cout << "0. Salir para volver a iniciar" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        try {
            if (opcion == 1) {
                T val; cout << "Valor: "; cin >> val;
                lista.push_front(val);
            } else if (opcion == 2) {
                T val; cout << "Valor: "; cin >> val;
                lista.push_back(val);
            } else if (opcion == 3) {
                int idx; T val; cout << "Indice y Valor: "; cin >> idx >> val;
                lista.insert_after(idx, val);
            } else if (opcion == 4) {
                T val; cout << "Valor a borrar: "; cin >> val;
                lista.delete_element(val);
            } else if (opcion == 5) {
                int idx; cout << "Indice a borrar: "; cin >> idx;
                lista.delete_at(idx);
            } else if (opcion == 6) {
                int idx; cout << "Indice: "; cin >> idx;
                cout << "Elemento: " << lista.get_at(idx) << endl;
            } else if (opcion == 7) {
                T oldVal, newVal; cout << "Valor a cambiar y Nuevo valor: "; cin >> oldVal >> newVal;
                lista.update_element(oldVal, newVal);
            } else if (opcion == 8) {
                int idx; T newVal; cout << "Indice y Nuevo valor: "; cin >> idx >> newVal;
                lista.update_at(idx, newVal);
            } else if (opcion == 9) {
                T val; cout << "Valor a buscar: "; cin >> val;
                int pos = lista.find(val);
                if (pos != -1) cout << "Encontrado en indice: " << pos << endl;
                else cout << "No encontrado." << endl;
            } else if (opcion == 10) {
                int idx; cout << "Indice: "; cin >> idx;
                cout << "Valor actual: " << lista[idx] << endl;
                T newVal; cout << "Nuevo valor: "; cin >> newVal;
                lista[idx] = newVal; // Utilizando la sobrecarga
            } else if (opcion == 11) {
                lista.print();
            }
        } catch (const std::exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    } while (opcion != 0);
}

// Sobrecarga de cin para atrapar la clase Fracción desde la consola sin errores
std::istream& operator>>(std::istream& is, Fraction& f) {
    int num, den;
    cout << "\n(Escribe numerador y denominador separados por espacio): ";
    is >> num >> den;
    f.setNumerator(num);
    f.setDenominator(den);
    return is;
}

// este programa es para probar el uso de pointers y smart pointers
int main() {

    int x = 42;
    int* p = &x;
    
    // imprimir valores de x y p
    cout << x << endl;
    cout << &x << endl;
    cout << p << endl;
    cout << *p << endl;

    // cambiar el valor de x con el pointer p
    cout << "valores de q" << endl;
    int* q = new int(5);
    cout << q << endl;
    cout << *q << endl;

    // eliminar el pointer q
    delete q;
    cout << q << endl;
    // cout << *q << endl; <-- Recomendación: Comentar esto para evitar el Segmentation Fault ya que "q" fue eliminado.

    // cruz pointer
    Fraction* f = new Fraction(2, 3);

    f->print();
    cout << f->getDenominator() << "/" << f->getNumerator() << endl;
    delete f;
    f = nullptr;

    // smart pointer
    std::unique_ptr<Fraction> g = std::make_unique<Fraction>(3, 4);
    g->print();
    cout << g->getDenominator() << "/" << g->getNumerator() << endl;


    srand(time(0));
    cout << "\n============================================\n";
    cout << "Bienvenido. De que tipo de datos deseas crear la lista?\n";
    cout << "1. Lista de Enteros (int)\n";
    cout << "2. Lista de Fracciones (Fraction)\n";
    cout << "Elige una opcion: ";
    int tipo; cin >> tipo;

    cout << "\nComo deseas iniciar la lista?\n";
    cout << "1. Vacia (Datos capturados)\n";
    cout << "2. Con datos aleatorios\n";
    cout << "Elige una opcion: ";
    int modo; cin >> modo;

    if (tipo == 1) {
        Linkedlist<int> listaEntera;
        if (modo == 2) {
            for (int i=0; i<5; i++) listaEntera.push_back(rand() % 100);
            cout << "Lista generada: "; listaEntera.print();
        }
        desplegarMenu(listaEntera);
    } else if (tipo == 2) {
        Linkedlist<Fraction> listaFraccion;
        if (modo == 2) {
            for (int i=0; i<5; i++) listaFraccion.push_back(Fraction(rand()%10, rand()%9 + 1));
            cout << "Lista generada: "; listaFraccion.print();
        }
        desplegarMenu(listaFraccion);
    } else {
        cout << "Opcion no valida." << endl;
    }

    return 0;
}