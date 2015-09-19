#include "b-treenode.h"
#include <iostream>

using namespace std;

BTreeNode::BTreeNode(bool hoja, int ordenArbol){
	this->hoja = hoja;

	this->tamano = 0;
	this->minimo = (ordenArbol/2)-1;
	this->maximo = ordenArbol - 1;
	this->llaves =  new Key[ordenArbol-1];
	this->hijos = new BTreeNode *[ordenArbol];
}

BTreeNode::~BTreeNode(){

}

void BTreeNode::split(){

}

*BTreeNode BTreeNode::busqueda(int llaveBusqueda){
	int posicion = 0;
	for (int i = 0; i < tamano; i++){
		if(llaveBusqueda < llaves[i]->llave)
			posicion++;
	}

    if (keys[posicion] == k)
        return keys[posicion];
    if (leaf == true)
        return NULL;
    return C[posicion]->busqueda(llaveBusqueda);
}