#if !defined(BST_H)
#define BST_H

#include "NodeT.h"

template <typename T>
class BST {
private:
    NodeT<T>* root;
    void printTree(NodeT<T>* node, string prefix, bool isRight, bool isRoot);
    void preOrder(NodeT<T>* node);
    void inOrder(NodeT<T>* node);
    void postOrder(NodeT<T>* node);
public:
    BST() : root(nullptr) {}
    void insert(T data);
    bool find(T data);
    void print();
    void visit(string method);
    void remove(T data);
};

template <typename T>
void BST<T>::insert(T data) {
    // Validamos si el árbol está vacío
    if (root == nullptr) {
        // el árbol está vacío
        // apuntamos root al nuevo nodo
        root = new NodeT<T>(data);
    } else {
        // el árbol no está vacío
        // creamos un apuntador aux igual a root
        NodeT<T>* aux = root;
        // creamos un apuntador father igual a root
        NodeT<T>* father = root;
        // itero en el árbol hasta encontrar donde voy a insertar el nodo
        while (aux != nullptr) {
            // valido si aux->data es igual a data
            if (aux->data == data) {
                // son iguales
                return;
            } else {
                // hacemos father igual a aux
                father = aux;
                // recorremos aux
                //if (data < aux->data ? aux = aux->left : aux = aux->right);  
                if (data < aux->data) {
                    aux = aux->left;
                } else {
                    aux = aux->right;
                }
            }
        }
        // inserto el nodo en el lado correspondiente
        if (data < father->data) {
            // el nodo va al lado izquierdo de father
            father->left = new NodeT<T>(data);
        } else {
            // el nodo va al lado derecho de father
            father->right = new NodeT<T>(data);
        }
    }
}

template <typename T>
bool BST<T>::find(T data) {
    // validamos que el árbol no este vacío
    if (root == nullptr) {
        // el árbol está vacío
        // retornamos false
        return false;
    } else {
        // el árbol no está vacío
        // creamos un apuntador aux igual a root
        NodeT<T>* aux = root;
        // itero en el árbol hasta encontrar el nodo a buscar o que no lo encuentre
        while (aux != nullptr) {
            // valido si aux->data es igual a data
            if (aux->data == data) {
                // son iguales, regreso true
                return true;
            } else {
                // recorremos aux
                // (data < aux->data) ? aux = aux->left : aux = aux->right;  
                if (data < aux->data) {
                    aux = aux->left;
                } else {
                    aux = aux->right;
                }
            }
        }
        // no se encontró el dato a buscar, regreso false
        return false;
    }
}

template <typename T>
void BST<T>::remove(T data) {
    // validamos si el árbol esta vacío
    if (root != nullptr) {
        // validamos si el nodo a borrar es root
        if (root->data == data) {
            // validamos si no tiene hijos
            if (root->left == nullptr && root->right == nullptr) {
                // root no tienes hijos
                // creamos un nodo aux igual a root
                NodeT<T>* aux = root;
                // asignamos nulos a root
                root = nullptr;
                // removemos aux
                delete aux;
                // nos salimos de la función
                return;
            }
            // validamos si tiene un hijo
            if (root->left == nullptr || root->right == nullptr) {
                // root solo tiene un hijo
                // creamos una puntador auxiliar igual a root
                NodeT<T>* aux = root;
                // movemos root al hijo
                root = (root->left == nullptr) ? root->right : root->left;
                // removemos aux
                delete aux;
                // nos salimos de la función
                return;
            }
            // root tiene dos hijos
            // creamos un apuntador aux igual a root
            NodeT<T>* aux = root;
            // validamos que el apuntador right de aux->left sea nulos
            if (aux->left->right == nullptr) {
                // aux->left es el más grande del lado izquierdo
                // creamos un apuntador que apunte a aux->left
                NodeT<T>* auxRemove = aux->left;
                // actulizamo el valor de aux por el valor de auxRemove
                aux->data = auxRemove->data;
                // asignamos a aux->left, auxRemove->left
                aux->left = auxRemove->left;
                // removemos auxRemove
                delete auxRemove;
                // nos salimos de la función
                return;
            } else {
                // el más grande del lado izquierdo no es aux->left
                // creamos un apuntador que va a ser el padre del que voy a remover igual a aux->left
                NodeT<T>* fatherRemove = aux->left;
                // creamos un apuntador hacia el hijo derecho de fatherRemove
                NodeT<T>* auxRemove = fatherRemove->right;
                // iteramos hastra encontrar el mas grande
                while (auxRemove->right != nullptr) {
                    // recorremos los apuntadores hacia la derecha
                    fatherRemove = auxRemove;
                    auxRemove = auxRemove->right;
                }
                // ya encontramos al más grande del lado izquierdo
                // igualamos aux->data igual a auxRemove->data
                aux->data = auxRemove->data;
                // actualizamos con nules el lado derecho de fatherRemove
                fatherRemove->right = nullptr;
                // removemos auxRemove
                delete auxRemove;
                // nos salimos de la función
                return;
            }
        } else {
            // no quiero borrar raíz
            // busco el nodo a borrar
            // creamos un apuntador father igual a root
            NodeT<T>* father = root;
            // creamos un aputador aux igual al hijo corrspondiente
            NodeT<T>* aux = (data < root->data) ? root->left : root->right;
            // itero en el árbol hasta encontrar el nodo a buscar o que no lo encuentre
            while (aux != nullptr) {
                // valido si aux->data es igual a data
                if (aux->data == data) {
                    // son iguales, regreso true
                    // lo removemos
                    // validamos si no tiene hijos
                    if (aux->left == nullptr && aux->right == nullptr) {
                        // aux no tienes hijos
                        // asignamos nulos al hijo correspondiente de father
                        (data < father->data) ? father->left = nullptr : father->right = nullptr;
                        // removemos aux
                        delete aux;
                        // nos salimos de la función
                        return;
                    }
                    // validamos si tiene un hijo
                    if (aux->left == nullptr || root->right == nullptr) {
                        // aux solo tiene un hijo
                        if (data < father->data) {
                            // el hijo esta a la izquierda del padre
                            father->left = (aux->left != nullptr) ? aux->left : aux->right;
                        } else {
                            // el hijo esta a la derecha del padre
                            father->right = (aux->left != nullptr) ? aux->left : aux->right;
                        }
                        // removemos aux
                        delete aux;
                        // nos salimos de la función
                        return;
                    }
                    // aux tiene dos hijos
                    // validamos que el apuntador right de aux->left sea nulos
                    if (aux->left->right == nullptr) {
                        // aux->left es el más grande del lado izquierdo
                        // creamos un apuntador que apunte a aux->left
                        NodeT<T>* auxRemove = aux->left;
                        // actulizamo el valor de aux por el valor de auxRemove
                        aux->data = auxRemove->data;
                        // asignamos a aux->left, auxRemove->left
                        aux->left = auxRemove->left;
                        // removemos auxRemove
                        delete auxRemove;
                        // nos salimos de la función
                        return;
                    } else {
                        // el más grande del lado izquierdo no es aux->left
                        // creamos un apuntador que va a ser el padre del que voy a remover igual a aux->left
                        NodeT<T>* fatherRemove = aux->left;
                        // creamos un apuntador hacia el hijo derecho de fatherRemove
                        NodeT<T>* auxRemove = fatherRemove->right;
                        // iteramos hastra encontrar el mas grande
                        while (auxRemove->right != nullptr) {
                            // recorremos los apuntadores hacia la derecha
                            fatherRemove = auxRemove;
                            auxRemove = auxRemove->right;
                        }
                        // ya encontramos al más grande del lado izquierdo
                        // igualamos aux->data igual a auxRemove->data
                        aux->data = auxRemove->data;
                        // actualizamos con nules el lado derecho de fatherRemove
                        fatherRemove->right = nullptr;
                        // removemos auxRemove
                        delete auxRemove;
                        // nos salimos de la función
                        return;
                    }
                } else {
                    // recorremos aux y father
                    father = aux;
                    aux = (data < aux->data) ? aux->left : aux->right;  
                }
            }
            // no se encontró el dato a buscar, arrojamos una excepción
            throw out_of_range("El nodo a borrar no existe");
        }
    }
}

template <typename T>
void BST<T>::printTree(NodeT<T>* node, string prefix, bool isRight, bool isRoot) {
    if (node == nullptr) return;
    printTree(node->right, prefix + (isRoot ? "" : (isRight ? "      " : "|     ")), true, false);
    cout << prefix << (isRoot ? "" : (isRight ? ".---- " : "`---- ")) << node->data << endl;
    printTree(node->left,  prefix + (isRoot ? "" : (isRight ? "|     " : "      ")), false, false);
}

template <typename T>
void BST<T>::preOrder(NodeT<T>* node) {
    if (node != nullptr) {
        // imprimimos data
        cout << node->data << " ";
        // hacemos preOrder con left
        preOrder(node->left);
        // hacemos preOrder con right
        preOrder(node->right);
    }
}

template <typename T>
void BST<T>::inOrder(NodeT<T>* node) {
    if (node != nullptr) {
        // hacemos inOrder con left
        inOrder(node->left);
        // imprimimos data
        cout << node->data << " ";
        // hacemos inOrder con right
        inOrder(node->right);
    }
}

template <typename T>
void BST<T>::postOrder(NodeT<T>* node) {
    if (node != nullptr) {
        // hacemos inOrder con left
        postOrder(node->left);
        // hacemos inOrder con right
        postOrder(node->right);
        // imprimimos data
        cout << node->data << " ";
    }
}

template <typename T>
void BST<T>::visit(string method) {
    if (method == "preOrder") {
        preOrder(root);
    }
    if (method == "inOrder") {
        inOrder(root);
    }
    if (method == "postOrder") {
        postOrder(root);
    }
    cout << endl;
}

template <typename T>
void BST<T>::print() {
    if (root == nullptr) { 
        cout << "(arbol vacio)" << endl; 
        return; 
    }
    printTree(root, "", false, true);
}


#endif // BST_H