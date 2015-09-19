#pragma once

#include <iostream>
#include "b-treenode.h"

using namespace std;

class BTree{
private:
	int tamano;	//Tamano del arbol
	BTreeNode *root;
public:
	BTree(int);
	~BTree();
	*BTreeNode busqueda(int);
	void insert(Key);
};