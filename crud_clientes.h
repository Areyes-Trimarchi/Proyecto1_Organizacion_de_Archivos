#ifndef CRUD_CLIENTES_H
#define CRUD_CLIENTES_H

#include "index.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Crud_Clientes{
	vector<IndiceClien> indice_clientes;
public:
	Crud_Clientes();
	~Crud_Clientes();
	bool Indexar();
	bool Agregar();
	bool Borrar();
	bool Modificar();
	bool Listar();
	bool BuscarIndex();
	bool Buscar();
	bool Reindexar();
	bool VerificarIndex(char[14]);
	int UpdateIndex(vector<IndiceClien>&, Cliente, int);
	int ElementoBorrado(int);
};

#endif
