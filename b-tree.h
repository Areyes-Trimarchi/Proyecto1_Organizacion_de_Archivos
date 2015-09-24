#pragma once

#include <iostream>
#include "b-treenode.h"

using namespace std;

struct CiudadArbol{
	char name[40];
	int idCiudad;
};

struct LineaxClienteArbol{
	char numero[9];
	char idCliente[14];
};

struct ClienteArbol{
	char nombre[40];
	char genero;
	int idCiudad;
	char idCliente[14];
};

struct HeaderArbol{
	int availList;
	int sizeRegistro;
};

struct Llamada{
	char numero[9];
	string inicio;
	string final;
	char destino[9];
};

class BTree{
private:
	int tamano;	//Tamano del arbol
	BTreeNode *root;
public:
	BTree(int,char[25]);
	~BTree();
	BTreeNode* busqueda(int);
	BTreeNode* busqueda(char *);
	bool insert(Key);
	bool insert(KeyChar);
	bool Remove(Key);
	bool Remove(KeyChar);
	void inorder(char[25]);
	void create(char[25]);
	void createCiudadArboles();
	void createClienteArbols();
	void createLineas();
};