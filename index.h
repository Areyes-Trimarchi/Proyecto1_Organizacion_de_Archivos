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
	string direccion;
	vector<Indice> indexCiudades;
	vector<IndiceClien> indexClientesOLineas;
public:
	Index(string);
	~Index();
	bool add(Ciudad, int);
	bool add(Cliente, int);
	bool add(LineaxCliente, int);
	bool remove(Ciudad);
	bool remove(Cliente);
	bool remove(LineaxCliente);
	Indice get(Ciudad);
	IndiceClien get(Cliente);
	IndiceClien get(LineaxCliente);
	Indice at(int, Ciudad);
	IndiceClien at(int, Cliente);
	IndiceClien at(int, LineaxCliente);
	void reindex();
	void create(string);
	void createCiudades(string);
	void createClientes(char*);
	void createLineas(string);
	void orderIndexCiudad(vector<Indice>&, Ciudad, int);
	void orderIndexCliente(vector<IndiceClien>&, Cliente, int);
	void orderIndexLineaxCliente(vector<IndiceClien>&, LineaxCliente, int);
	int busquedaCiudad(Ciudad);
	int busquedaClientes(Cliente);
	int busquedaLineas(LineaxCliente);
	void load();
	void cargarCiudades();
	void cargarClientes();
	void cargarLineas();
	void guardarCiudades();
	void guardarClientes();
	void guardarLineas();
	Indice ciudadRRN(int, Ciudad);
	IndiceClien clienteRRN(int, Cliente);
	IndiceClien lineaRRN(int, LineaxCliente);
};
