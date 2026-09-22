#include <iostream>
#include <memory>
using namespace std;

#include "Fraction.h"
#include "Linkedlist.h"

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
    cout << *q << endl;

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


    return 0;
}