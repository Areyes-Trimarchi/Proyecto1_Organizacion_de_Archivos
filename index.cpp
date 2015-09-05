#include "index.h"
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

Index::Index(string nombre){
	cout << "Holassss" << endl;
	ifstream file;
	file.open(nombre);
	
	if(file.fail()){
		cout << "Hola2" << endl;
		create(nombre);
	}
}

Index::~Index(){

}

bool Index::add(){
	
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
		//createLineas(nombre);
	}
}

void Index::createCiudades(string nombre){
	
		
}

void Index::createClientes(string nombre){
	ifstream file;
	file.open(nombre);
	if(file.fail()){
		cerr << "Error al abrir el archivo." << endl;
	} else{
		Header head;
		file.seekg(0);
		file.read(reinterpret_cast<char*>(&head), sizeof(Header));
		sizeRegistros=head.sizeRegistro; 
		availList=head.availList;

		int RRN;
		vector<IndiceClien>index;
		file.seekg(8):
		for (int i = 0; i < sizeRegistros; ++i){
			Cliente client;
			file.read(reinterpret_cast<char*>(&client), sizeof(Cliente));

			RRN = i;
			orderIndexCliente(index, client, RRN);

		}
		ofstream salida("indexClientes.bin", ofstream::binary);
		for (int i = 0; i < index.size(); i++){
			salida.write(reinterpret_cast<const char*> (&index.at(i)), sizeof(IndiceClien));
		}
	}
}

void Index::createLineas(string nombre){
	
}

void Index::orderIndexCiudad(vector<Indice>& indexC, Ciudad city, int RRN){
	
}

void Index::orderIndexCliente(vector<IndiceClien>& indexC, Cliente client, int RRN){
	int tamano = indexC.size();
	IndiceClien indice;
	strcpy(indice.id_clie_index, client.idCliente);
	indice.RRN_index = RRN;

	vector<IndiceClien>::iterator it;
  	it = indexC.begin();

	if(tamano == 0)
		indexC.push_back(indice);
	else{
		int primerIndice = 0, ultimoIndice = tamano - 1, centro;
		while (primerIndice <= ultimoIndice)
	    {
	    	centro = (ultimoIndice + primerIndice)/2;
		    if (indexC.at(centro).id_clie_index == client.idCliente){
				cerr<<"Ya existe ese id"<<endl;
			}
		    else{
		 		if (client.idCliente < indexC.at(centro).id_clie_index){
		   			ultimoIndice=centro-1;
		   			if(ultimoIndice < 0)
		   				indexC.insert(it, indice);
		   			else if(ultimoIndice < primerIndice)
		   				indexC.insert(it + primerIndice, indice);
		   		}
		 		else{
		   			primerIndice=centro+1;
		   			if(primerIndice > tamano)
		   				indexC.push_back(indice);
		   			else if(primerIndice > ultimoIndice)
		   				indexC.insert(it + primerIndice, indice);
		   		}
		   	}
	    }
	}
}

void Index::orderIndexLineaxCliente(vector<IndiceClien>& indexC, LineaxCliente line, int RRN){
	
}