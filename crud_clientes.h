#ifndef CRUD_CLIENTES_H
#define CRUD_CLIENTES_H

#include <string>
#include <iostream>

using namespace std;

struct Cliente{
	string idCliente;
	string nombre_cliente;
	int idCiudad;
	char genero;
};

class crud_clientes{

public:
	crud_clientes();
	~crud_clientes();
	bool Agregar();
	bool Borrar();
	bool Modificar();
	bool Listar();
	bool BuscarIndex();
	bool Buscar();
	bool Reindexar();
};

#endif