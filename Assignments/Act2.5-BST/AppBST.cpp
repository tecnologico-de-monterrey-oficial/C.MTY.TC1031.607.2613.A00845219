// Clase Huicho
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

#include "BST.h"

int main(){
	BST miArbol;

	miArbol.add(7);
	miArbol.add(10);
	miArbol.add(21);
	miArbol.add(40);
	miArbol.add(6);
	miArbol.add(18);
	miArbol.add(9);
	miArbol.add(5);
	miArbol.add(2);
	miArbol.add(1);
	miArbol.visit(1);
	miArbol.visit(2);
	miArbol.visit(3);
	miArbol.visit(4);
	cout << "El árbol tiene: "<< miArbol.size() << " Nodos"<<endl;
	miArbol.remove(7);
	cout << "El árbol tiene: "<< miArbol.size() << " Nodos"<<endl;
	miArbol.visit(1);
	miArbol.visit(2);
	miArbol.visit(3);
	miArbol.visit(4);

/*
	if (miArbol.search(21)){
		cout << "SI encontró al 21" << endl;
	}
	else{
		cout << "NO encontró al 21" << endl;
	}
	if (miArbol.search(100)){
		cout << "SI encontró al 100" << endl;
	}
	else{
		cout << "NO encontró al 100" << endl;
	}
	if (miArbol.search(7)){
		cout << "SI encontró al 7" << endl;
	}
	else{
		cout << "NO encontró al 7" << endl;
	}
	if (miArbol.search(40)){
		cout << "SI encontró al 40" << endl;
	}
	else{
		cout << "NO encontró al 40" << endl;
	}
*/
	
	return 0;
}