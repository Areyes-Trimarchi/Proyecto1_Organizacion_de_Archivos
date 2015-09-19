#pragma once

#include <iostream>

using namespace std;

//Esto es lo que se guarda en cada nodo
struct Key{
	int llave;	//Esto es la llave, que es diferente segun el tipo, en clientes seria el idCliente en ciudades el idCiudad y en lineas el numero
	int RRN; 
};

class BTreeNode{
private:
	Key *llaves;	//Las llaves que contiene este nodo
	int tamano;		//Tamano llaves actual
	int minimo;		//Numero minimo de llaves
	int maximo;		//Numero maximo de llaves
	BTreeNode **hijos;	//Los nodos hijos
	bool hoja;
public:
	BTreeNode(arguments);
	~BTreeNode();
	void split();
	*BTreeNode busqueda(int);
};