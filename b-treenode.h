#pragma once

#include <iostream>

using namespace std;

//Esto es lo que se guarda en cada nodo
struct Key{
	int llave;	//Esto es la llave, que es diferente segun el tipo, en clientes seria el idCliente en ciudades el idCiudad y en lineas el numero
	int RRN; 
};

struct KeyChar{
	char llave[14];	//Esto es la llave, que es diferente segun el tipo, en clientes seria el idCliente en ciudades el idCiudad y en lineas el numero
	int RRN; 
};

class BTreeNode{
private:
	Key* llaves;	//Las llaves que contiene este nodo
	KeyChar* llavesChar;	//Las llaves que contiene este nodo pero con char
	int tamano;		//Tamano llaves actual
	int minimo;		//Numero minimo de llaves
	int maximo;		//Numero maximo de llaves
	BTreeNode** hijos;	//Los nodos hijos
	bool hoja;
public:
	BTreeNode(bool, int);
	~BTreeNode();
	void split(int, BTreeNode*);
	bool insert(Key);
	bool insert(KeyChar);
	BTreeNode* busqueda(int);
	BTreeNode* busqueda(char *);
	void inorder(bool);
	int LlaveExiste(Key);
	int LlaveExiste(KeyChar);
	bool Remove(Key);
	void Remove(KeyChar);
    Key getPrev(int);
    KeyChar GetPrev(int);
    Key getNext(int);
    KeyChar GetNext(int);
    void Llenar(int);
    void LlenarChar(int);
    void PrestadoPrev(int);
    void PrestadoPrevChar(int);
    void PrestadoNext(int);
    void PrestadoNextChar(int);
    void Merge(int);
    void MergeChar(int);

friend class BTree;

friend class crud_lineasxclienteArbol;

friend class crud_ciudadesArbol;
};