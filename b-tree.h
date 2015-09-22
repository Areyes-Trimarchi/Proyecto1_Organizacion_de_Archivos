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
	char name[40];
	char genero;
	int idCiudad;
	char idCliente[14];
};

struct HeaderArbol{
	int availList;
	int sizeRegistro;
};

class BTree{
private:
	int tamano;	//Tamano del arbol
	BTreeNode *root;
public:
	BTree(int, const char *);
	~BTree();
	BTreeNode* busqueda(int);
	bool insert(Key);
	bool insert(KeyChar);
	void Remove(Key*);
	void inorder(const char *);
	void create(const char *);
	void createCiudades(const char *);
	void createClientes(const char *);
	void createLineas(const char *);
};