#include <string>
#include <vector>

using namespace std;

#pragma once

struct Ciudad{
	char name[40];
	int idCiudad;
};

struct LineaxCliente{
	char numero[9];
	char idCliente[14];
};

struct Cliente{
	char name[40];
	char genero;
	int idCiudad;
	char idCliente[14];
};

struct Header{
	int availList;
	int sizeRegistro;
};

struct Indice{
	int id_ciu_index;
	int RRN_index;
};

struct IndiceClien{
	char id_clie_index[14];
	int RRN_index;
};

class Index{

private:
	unsigned int size;
	int sizeRegistros;
	int availList;
public:
	Index(string);
	~Index();
	bool add();
	bool remove();
	bool get();
	void reindex();
	void create(string);
	void createCiudades(string);
	void createClientes(string);
	void createLineas(string);
	void orderIndexCiudad(vector<Indice>&, Ciudad, int);
	void orderIndexCliente(vector<IndiceClien>&, Cliente, int);
	void orderIndexLineaxCliente(vector<IndiceClien>&, LineaxCliente, int);
};