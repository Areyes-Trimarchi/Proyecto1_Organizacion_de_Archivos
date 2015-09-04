#include "index.h"
#include <stdlib.h>
#include <fstream>
#include <map>
#include <iostream>

using namespace std;

struct Ciudad{
	char name[40];
	int idCiudad;
};

struct LineaxCliente{
	char numero[9];
	char* idCliente;
};

struct Cliente{
	char name[40];
	char genero;
	int idCiudad;
	char* idCliente;
};

Index::Index(int capacity, string nombre){
	this->capacity = capacity;
	ifstream file;
	file.open(nombre);
	if(file.fail()){
		create(nombre);
	}
}

Index::~Index(){

}

bool Index::add(){
	/*if (size == capacity) 
        return false;
    if (pos < 0 || pos > size)
        return false; // Fracaso en esta Operación
    if (pos != size) // Se evalua si no se esta metiendo al final
        for (int i = size; i > pos; i--) // Se recorre el arreglo de atras havia adelante
            this->data[i] = this->data[i-1]; // Se mueven los elementos para poder insertar
    this->data[pos] = data; // Se agregar el nuevo elemento
    size++;
    return true;*/
}

bool Index::remove(){
	/*
    if (pos < 0 || pos >= size)
        return NULL; // Indicar fracaso en la operación
    Object* retVal = data[pos];
    data[pos] = NULL;
    if (pos != size-1){ // Evalua si no se esta borrando el ultimo elemento
        for (int i = pos; i < size-1; i++)
            data[i] = data[i+1];
        data[size-1] = NULL;
    }
    size--; 
    return retVal;*/
}

bool Index::get(){
	//Busqueda Binaria

}
void Index::reindex(){

}

void Index::create(string nombre){
	if(nombre ==  "ciudades.bin"){
		createCiudades(nombre);
	} else if(nombre ==  "clientes.bin"){
		createClientes(nombre);
	} else{
		createLineas(nombre);
	}
}

void Index::createCiudades(string nombre){
	ifstream file;
	file.open(nombre);
	if(file.fail()){
		cerr << "Error al abrir el archivo." << endl;
	} else{
		file.read(reinterpret_cast<char*>(&sizeRegistros), sizeof(sizeRegistros));
		file.read(reinterpret_cast<char*>(&availList), sizeof(availList));

		int idCiudad;
		int RRN;
		map<int, int> ourMap; 
		for (int i = 0; i < sizeRegistros; ++i){
			Ciudad city;
			file.read(reinterpret_cast<char*>(&city), sizeof(city));
			idCiudad = city.idCiudad;
			ourMap[idCiudad] = i;
		}

		ofstream salida("indexCiudad.bin", ofstream::binary);
		for (auto& iterator: ourMap){
			salida.write(reinterpret_cast<const char*> (&iterator.first), sizeof(iterator.first));
			salida.write(reinterpret_cast<const char*> (&iterator.second), sizeof(iterator.second));
		}
	}
}

void Index::createClientes(string nombre){
	ifstream file;
	file.open(nombre);
	if(file.fail()){
		cerr << "Error al abrir el archivo." << endl;
	} else{
		file.read(reinterpret_cast<char*>(&sizeRegistros), sizeof(sizeRegistros));
		file.read(reinterpret_cast<char*>(&availList), sizeof(availList));

		char* idCliente;
		int RRN;
		map<char*, int> ourMap; 
		for (int i = 0; i < sizeRegistros; ++i){
			Cliente client;
			file.read(reinterpret_cast<char*>(&client), sizeof(client));
			idCliente = client.idCliente;
			ourMap[idCliente] = i;
		}

		ofstream salida("indexCliente.bin", ofstream::binary);
		for (auto& iterator: ourMap){
			salida.write(reinterpret_cast<const char*> (&iterator.first), sizeof(iterator.first));
			salida.write(reinterpret_cast<const char*> (&iterator.second), sizeof(iterator.second));
		}
	}
}

void Index::createLineas(string nombre){
	ifstream file;
	file.open(nombre);
	if(file.fail()){
		cerr << "Error al abrir el archivo." << endl;
	} else{
		file.read(reinterpret_cast<char*>(&sizeRegistros), sizeof(sizeRegistros));
		file.read(reinterpret_cast<char*>(&availList), sizeof(availList));

		char* idCliente;
		int RRN;
		map<char*, int> ourMap; 
		for (int i = 0; i < sizeRegistros; ++i){
			LineaxCliente lineas;
			file.read(reinterpret_cast<char*>(&lineas), sizeof(lineas));
			idCliente = lineas.idCliente;
			ourMap[idCliente] = i;
		}

		ofstream salida("indexLineasXCliente.bin", ofstream::binary);
		for (auto& iterator: ourMap){
			salida.write(reinterpret_cast<const char*> (&iterator.first), sizeof(iterator.first));
			salida.write(reinterpret_cast<const char*> (&iterator.second), sizeof(iterator.second));
		}
	}
}