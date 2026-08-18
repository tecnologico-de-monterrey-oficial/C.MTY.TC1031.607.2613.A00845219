#include <iostream>
#include "List.h"
using namespace std;

/*
int sum(int a, int b) {
    return a+b;
}

double sum(double a, double b) {
    return a+b;
}

string sum(string a, string b) {
    return a +b;
}
*/
template <typename T>

T sum(T a, T b) {
    return a + b;
}

int main() {
    string a = "hola";
    string b = " crayola";
    cout<<"Sum of "<<a<<" and "<<b<<" is: "<<sum(a,b)<<endl; 
    int c = 5;
    int d = 10;
    cout<<"Sum of "<<c<<" and "<<d<<" is: "<<sum(c,d)<<endl;
    double e = 5.5;
    double f = 10.5;
    cout<<"Sum of "<<e<<" and "<<f<<" is: "<<sum(e,f)<<endl;

    List<int> list;
    list.insert(5);
    list.insert(10);
    list.insert(15);

    cout<<"Lista original "<<endl;
    list.print();
    
    cout<<"\nInsertando 20 en la posicion 1 (insertAt):"<< endl;
    list.insertAt(1, 20);
    list.print();
    
    cout<<"\nIntentando insertar en posicion invalida (10):"<<endl;
    list.insertAt(10, 100);
    
    cout<<"\nEl elemento mayor (getMax) es: " << list.getMax()<<endl;
    cout<<"El tamano de la lista (getSize) es: " << list.getSize() << endl;
    cout<<"El dato en la posicion 2 (getData) es: " << list.getData(2) << endl;
    
    // elimina la posicion 1 (removeAt)
    list.removeAt(1);
    list.print();

    // eliminando el ultimo elemento (removeLast)
    list.removeLast();
    list.print();

    // string
    List<string> listStr;
    listStr.insert("Laptop");
    listStr.insert("bottle");
    listStr.insert("iphone");

    cout << "\nLista de strings original:" << endl;
    listStr.print();
    
    cout << "\nInsertando 'teclado' en la posicion 0:" << endl;
    listStr.insertAt(0, "teclado");
    listStr.print();
    // encontrando el maximo (getMax)
    cout <<"\nEl elemento mayor alfabeticamente (getMax) es: " << listStr.getMax() << endl;

    return 0;
}