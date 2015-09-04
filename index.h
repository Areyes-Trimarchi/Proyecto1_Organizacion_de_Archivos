#include <string>

using namespace std;

#pragma once

class Index{

private:
	int capacity;
	unsigned int size;
	int sizeRegistros;
	int availList;
public:
	Index(int, string);
	~Index();
	bool add();
	bool remove();
	bool get();
	void reindex();
	void create(string);
	void createCiudades(string);
	void createClientes(string);
	void createLineas(string);
};