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

*BTreeNode BTree::busqueda(int llaveBusqueda){
	if(root == NULL)
		return NULL;
	return root->busqueda(llaveBusqueda)
}

void BTree::insert(Key llave){
	 if (root == NULL){
        root = new BTreeNode(tamano, true);
        root->keys[0] = llave;
        root->tamano = 1;
    } else{
    	if (root->tamano == root->maximo){
            BTreeNode *neo = new BTreeNode(tamano, false);
 
            // Make old root as child of new root
            neo->hijos[0] = root;
 
            // Split the old root and move 1 key to the new root
            neo->splitChild(0, root);
 
            // New root has two children now.  Decide which of the
            // two children is going to have new key
            int i = 0;
            if (neo->llaves[0] < llave)
                i++;
            neo->hijos[i]->insertNonFull(llave);
 
            // Change root
            root = neo;
        }
        else  // If root is not full, call insertNonFull for root
            root->insertNonFull(llave);
    }
}