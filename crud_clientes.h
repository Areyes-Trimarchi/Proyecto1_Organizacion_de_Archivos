#ifndef CRUD_CLIENTES_H
#define CRUD_CLIENTES_H

#include <string>
#include <iostream>
#include <vector>

using namespace std;

struct Cliente{
	char idCliente[14];
	char nombre_cliente[40];
	int idCiudad;
	char genero;
};

struct Header{
	int availList;
	int sizeRegistro;
};

struct IndiceClien{
	char id_clie_index[14];
	int RRN_index;
};

class crud_clientes{
	vector<IndiceClien> indice_clientes;
public:
	crud_clientes();
	~crud_clientes();
	bool Index();
	bool Agregar();
	bool Borrar();
	bool Modificar();
	bool Listar();
	bool BuscarIndex();
	bool Buscar();
	bool Reindexar();
	bool VerificarIndex(char[14]);
};

#endif