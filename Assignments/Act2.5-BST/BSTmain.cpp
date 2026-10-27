#include <iostream>
using namespace std;

#include "BST.h"

int main() {
    BST<int> bst;
    int opcion;
    int valor;

    do {
        cout << "\n--- MENU ARBOL BINARIO DE BUSQUEDA (BST) ---" << endl;
        cout << "1. Insertar valor" << endl;
        cout << "2. Mostrar recorridos (inorder, preorder, postorder)" << endl;
        cout << "3. Buscar un valor" << endl;
        cout << "4. Mostrar la altura del arbol" << endl;
        cout << "5. Mostrar los ancestros de un nodo" << endl;
        cout << "6. Consultar el nivel de un nodo" << endl;
        cout << "7. Ver arbol completo" << endl;
        cout << "0. Salir" << endl;
        cout << "Ingrese una opcion: ";
        cin >> opcion;

        if (opcion == 1) {
            cout << "Ingrese el valor a insertar: ";
            cin >> valor;
            bst.insert(valor);
            cout << "Valor insertado." << endl;
            cout << "Arbol actual:" << endl;
            bst.print();
        } 
        else if (opcion == 2) {
            cout << "Recorrido InOrder: ";
            bst.visit("inOrder");
            cout << "Recorrido PreOrder: ";
            bst.visit("preOrder");
            cout << "Recorrido PostOrder: ";
            bst.visit("postOrder");
        } 
        else if (opcion == 3) {
            cout << "Ingrese el valor a buscar: ";
            cin >> valor;
            if (bst.find(valor)) {
                cout << "El valor " << valor << " SI se encuentra en el arbol." << endl;
            } else {
                cout << "El valor " << valor << " NO se encuentra en el arbol." << endl;
            }
        } 
        else if (opcion == 4) {
            cout << "La altura del arbol es: " << bst.height() << endl;
        } 
        else if (opcion == 5) {
            cout << "Ingrese el nodo para buscar sus ancestros: ";
            cin >> valor;
            bst.ancestors(valor);
        } 
        else if (opcion == 6) {
            cout << "Ingrese el nodo para consultar su nivel: ";
            cin >> valor;
            int nivel = bst.WhatLevelAmI(valor);
            if (nivel != -1) {
                cout << "El nodo " << valor << " se encuentra en el nivel " << nivel << "." << endl;
            } else {
                cout << "El nodo no existe en el arbol." << endl;
            }
        }
        else if (opcion == 7) {
            cout << "Arbol actual:" << endl;
            bst.print();
        }
        else if (opcion == 0) {
            cout << "Saliendo del programa..." << endl;
        } 
        else {
            cout << "Opcion no valida. Intente de nuevo." << endl;
        }

    } while (opcion != 0);

    return 0;
}