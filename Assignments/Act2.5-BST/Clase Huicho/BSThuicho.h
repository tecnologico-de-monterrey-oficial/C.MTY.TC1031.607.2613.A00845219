// Clase Huicho
#include "NodeThuicho.h"
class BST{
	public:
		BST();
		~BST();
		bool search(int data);
		void add(int data);
		void remove(int data);
		void visit(int tipo);
		int size();
/*
		int height();	// size + max
		void ancestors(int dato);  // search + pila
		int whatlevelamI(int dato); // search + contador
*/
	private:
		NodeT *root;	
		void preOrden(NodeT *r);
		void inOrden(NodeT *r);
		void postOrden(NodeT *r);
		void levelxlevel();
		void destruye(NodeT *r);
		int howManyChildren(NodeT *r);
		int pred(NodeT *r);
		int succ(NodeT *r);
		int sizeHelper(NodeT *r);
};

BST::BST(){
	root = nullptr;
}

BST::~BST(){
	destruye(root);
}

//Complejidad: O(n)
void BST::destruye(NodeT *r){
	if (r != nullptr){
		destruye(r->getLeft());
		destruye(r->getRight());
		delete r;
	}
}

// Complejidad: O(altura)
int BST::pred(NodeT *r){
	NodeT *curr = r->getLeft();
	while (curr->getRight() != nullptr){
		curr = curr->getRight();
	}
	return curr->getData();
}

int BST::succ(NodeT *r){
	NodeT *curr = r->getRight();
	while (curr->getLeft() != nullptr){
		curr = curr->getLeft();
	}
	return curr->getData();
}

// Complejidad: O(1)
int BST::howManyChildren(NodeT *r){
	int cont = 0;
	if (r->getLeft() != nullptr){
		cont++;
	}
	if (r->getRight() != nullptr){
		cont++;
	}
	return cont;
}

// Complejidad: O(altura del árbol)
bool BST::search(int data){
	NodeT *curr = root;
	while (curr != nullptr){
		if (curr->getData() == data){
			return true;
		}
/*
		if (curr->getData() > data){
			curr = curr->getLeft();
		}
		else{
			curr = curr->getRight();
		}
*/
		curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
	}
	return false;
}

// Complejidad: O(altura del árbol)
void BST::add(int data){
	NodeT *curr = root;
	NodeT *father = nullptr;
	while (curr != nullptr){
		if (curr->getData() == data){
			return;
		}
		father = curr;
		curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
	}
	if (father == nullptr){
		root = new NodeT(data);
	}
	else{
/*
		if (father->getData() > data){
			father->setLeft(new NodeT(data));
		}
		else{
			father->setRight(new NodeT(data));
		}
*/
		(father->getData() > data) ? father->setLeft(new NodeT(data)) :
									 father->setRight(new NodeT(data));
	}

}

void BST::remove(int data){
	NodeT *curr = root;
	NodeT *father = nullptr;
	while (curr != nullptr && curr->getData() != data){
		father = curr;
		curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
	}
	if (curr == nullptr){
		return;
	}
	int cantHijos = howManyChildren(curr);
	switch (cantHijos){
		case 0: if (father == nullptr){
					root = nullptr;
				}
				else{
					if (father->getData() > data){
						father->setLeft(nullptr);
					}
					else{
						father->setRight(nullptr);
					}
				}
				delete curr;
				break;
		case 1: if (father == nullptr){   // El que quiero borrar es raíz y tiene 1 hijo
					if (curr->getLeft() != nullptr){
						root = curr->getLeft();
					}
					else{
						root = curr->getRight();
					}
				}
				else{
					if (father->getData() > data){
						// El que quiero borrar esta a la izq del padre
						if (curr->getLeft() != nullptr){
							// El único hijo esta a la izq del que quiero borrar
							father->setLeft(curr->getLeft());
						}
						else{
							// El único hijo esta a la der del que quiero borrar
							father->setLeft(curr->getRight());
						}
					}
					else{
						// El que quiero borrar esta a la der del padre
						if (curr->getLeft() != nullptr){
							// El único hijo esta a la izq del que quiero borrar
							father->setRight(curr->getLeft());
						}
						else{
							// El único hijo esta a la der del que quiero borrar
							father->setRight(curr->getRight());
						}
					}
				}
				delete curr;
				break;
		case 2: int sucesor = succ(curr);
				remove(sucesor);
				curr->setData(sucesor);
				break;
	}

}

//Complejidad: O(n)
void BST::preOrden(NodeT *r){
	if (r != nullptr){
		cout << r->getData() << " ";
		preOrden(r->getLeft());
		preOrden(r->getRight());
	}
}

//Complejidad: O(n)
void BST::inOrden(NodeT *r){
	if (r != nullptr){
		inOrden(r->getLeft());
		cout << r->getData() << " ";
		inOrden(r->getRight());
	}
}

//Complejidad: O(n)
void BST::postOrden(NodeT *r){
	if (r != nullptr){
		postOrden(r->getLeft());
		postOrden(r->getRight());		
		cout << r->getData() << " ";
	}
}

//Complejidad: O(n)
void BST::levelxlevel(){
	queue<NodeT*> q;
	if (root != nullptr){
		q.push(root);
		while (!q.empty()){
			cout << q.front()->getData()<< " ";
			if (q.front()->getLeft() != nullptr){
				q.push(q.front()->getLeft());
			}
			if (q.front()->getRight() != nullptr){
				q.push(q.front()->getRight());
			}	
			q.pop();	
		}
	}
}

//Complejidad: O(n)
void BST::visit(int tipo){  // vist
	switch (tipo){
		case 1 : preOrden(root);
				 break;
		case 2 : inOrden(root);
				 break;
		case 3 : postOrden(root);
				 break;
		case 4 : levelxlevel();
				 break;
	}
	cout << endl;
}

// Complejidad: O(n)
int BST::sizeHelper(NodeT *r){
	if (r == nullptr){
		return 0;
	}
	return 1 + sizeHelper(r->getLeft()) + sizeHelper(r->getRight());
}

//Complejidad: O(n)
int BST::size(){
	return sizeHelper(root);
}