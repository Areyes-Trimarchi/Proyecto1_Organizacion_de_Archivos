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

struct IndiceLineas{
	char numero[9];
	int RRN_index;
};

class Index{

private:
	unsigned int size;
	int sizeRegistros;
	int availList;
	char direccion[14];
	vector<Indice> indexCiudades;
	vector<IndiceClien> indexClientes;
	vector<IndiceLineas> indexLineas;
public:
	Index(char[14]);
	~Index();
	bool add(Ciudad, int);
	bool add(Cliente, int);
	bool add(LineaxCliente, int);
	bool remove(Ciudad);
	bool remove(Cliente);
	bool remove(LineaxCliente);
	Indice get(Ciudad);
	IndiceClien get(Cliente);
	IndiceLineas get(LineaxCliente);
	Indice at(int, Ciudad);
	IndiceClien at(int, Cliente);
	IndiceLineas at(int, LineaxCliente);
	void reindex();
	void create(char [14]);
	void createCiudades(string);
	void createClientes(char*);
	void createLineas(string);
	bool orderIndexCiudad(vector<Indice>&, Ciudad, int);
	void orderIndexCliente(vector<IndiceClien>&, Cliente, int);
	bool orderIndexLineaxCliente(vector<IndiceLineas>&, LineaxCliente, int);
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
	IndiceLineas lineaRRN(int, LineaxCliente);
	void imprimirIndexLineas();
};
