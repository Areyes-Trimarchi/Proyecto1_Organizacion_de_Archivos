#include "b-treenode.h"
#include "b-tree.h"
#include <iostream>

using namespace std;

BTree::BTree(int tamano){
	this->tamano = tamano;
	this->root = NULL;
}

BTree::~BTree(){

}

BTreeNode* BTree::busqueda(int llaveBusqueda){
	if(root == NULL)
		return NULL;
	return root->busqueda(llaveBusqueda);
}

void BTree::insert(Key llave){
	 if (root == NULL){															//Si no existe raiz
        root = new BTreeNode(tamano, true);										//Se crea la raiz
        root->llaves[0] = llave;
        root->tamano = 1;
    } else{
    	if (root->tamano == root->maximo){										//Mira si la raiz no tiene el tamano maximo
            BTreeNode *neo = new BTreeNode(false, tamano);
            neo->hijos[0] = root;												//Crea un nuevo nodo que contendra a la raiz actul como hijo
 
            neo->split(0, root);												
 
            int i = 0;
            if (neo->llaves[0].llave < llave.llave)							//Decidir cual de los dos hijos de la raiz tendra los hijos
                i++;
            neo->hijos[i]->insert(llave);
 
            root = neo;															//Actualizar la raiz
        }
        else 
            root->insert(llave);												//Insertar normal
    }
}

void BTree::traverse(){  
	if (root != NULL) 
		root->traverse(); 
}