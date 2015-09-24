#ifndef CRUD_CLIENTES_H
#define CRUD_CLIENTES_H

#include "index.h"
#include "b-tree.h"
#include <string>
#include <iostream>
#include <vector>

using namespace std;

class Crud_Clientes{
	vector<IndiceClien> indice_clientes;
	vector<Cliente> clientes;
public:
	Crud_Clientes();
	~Crud_Clientes();
	bool Indexar();
	bool Agregar();
	bool Borrar();
	bool Modificar();
	bool Listar();
	bool ListarArbol();
	bool BuscarIndex();
	bool Buscar();
	bool Reindexar();
	bool VerificarIndex(char[14]);
	void UpdateIndex(vector<IndiceClien>&, Cliente, int);
	int ElementoBorrado(int);
	void ReescribirArchivo(Header,Cliente,int);
	void CargarVectorClientes(Cliente,int);
};

#endif