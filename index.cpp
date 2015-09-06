#include "index.h"
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstring>
#include <stdio.h>

using namespace std;

/*
	Constructor
	Tiene que verificar si existe indice, sino lo crea; si ya existia previamente, lo carga
*/
Index::Index(string nombre){
	this->direccion = nombre;
	ifstream file;
	file.open(direccion);
	
	if(file.fail()){
		cout << "Hola2" << endl;
		create(direccion);
	}
}

Index::~Index(){

}

/*
	Agregar al indice
	Verifica que tipo agrega y funciona con ek metodo apropiado por tipo
*/
bool Index::add(Ciudad city){
	orderIndexCiudad(indexCiudades, city, indexCiudades.size());
	return true;
}

bool Index::add(Cliente client){
	orderIndexCliente(indexClientesOLineas, client, indexCiudades.size());
	return true;
}

bool Index::add(LineaxCliente linea){
	orderIndexLineaxCliente(indexClientesOLineas, linea, indexCiudades.size());
	return true;
}

/*
	Remover del indice
	Verifica que tipo elininara y trabaja con el metodo dependiendo del tipo
*/
bool Index::remove(Ciudad city){
	int RRN = busquedaCiudad(city);
	indexCiudades.at(RRN).id_ciu_index = -99;
}

bool Index::remove(Cliente client){
	int RRN = busquedaClientes(client);
	indexClientesOLineas.at(RRN).id_clie_index[0] = '*';
}

bool Index::remove(LineaxCliente linea){
	int RRN = busquedaLineas(linea);
	indexClientesOLineas.at(RRN).id_clie_index[0] = '*';
}

/*
	Retornar una ciudad es tipo Indice
*/
Indice Index::get(Ciudad city){
	int regresar;
	regresar = busquedaCiudad(city);
	return indexCiudades.at(regresar);
}

/*
	Retornar un cliente es de tipo IndiceClien
*/
IndiceClien Index::get(Cliente client){
	int regresar;
	regresar = busquedaClientes(client);
	return indexClientesOLineas.at(regresar);
}

/*
	Retornar una linea x cliente es de tipo IndiceClien
*/
IndiceClien Index::get(LineaxCliente linea){
	int regresar;
	regresar = busquedaLineas(linea);
	return indexClientesOLineas.at(regresar);
}

void Index::reindex(){

}

/*
	Metodo para crear el indice por si no funciona
*/
void Index::create(string nombre){
	if(nombre ==  "ciudades.bin")
		createCiudades(nombre);
	else if(nombre ==  "clientes.bin")
		createClientes(nombre);
	else
		createLineas(nombre);
}

/*
	Metodo para crear ciudades
*/
void Index::createCiudades(string nombre){
	ifstream file;
	file.open(nombre);
	if(file.fail()){
		cerr << "Error al abrir el archivo." << endl;
	} else{
		file.read(reinterpret_cast<char*>(&sizeRegistros), sizeof(sizeRegistros));
		file.read(reinterpret_cast<char*>(&availList), sizeof(availList));

		int RRN;
		vector<Indice>index;
		
		for (int i = 0; i < sizeRegistros; ++i){
			Ciudad city;
			file.read(reinterpret_cast<char*>(&city), sizeof(city));

			RRN = i;
			orderIndexCiudad(index, city, RRN);

		}
		cout << "Pene``````" << index.size() << endl;
		ofstream salida("indexCiudad.bin", ofstream::binary);
		for (int i = 0; i < index.size(); i++){
			salida.write(reinterpret_cast<const char*> (&index.at(i).id_ciu_index), sizeof(index.at(i).id_ciu_index));
			salida.write(reinterpret_cast<const char*> (&index.at(i).RRN_index), sizeof(index.at(i).RRN_index));
		}
	}
}

/*
	Metodo para crear Clientes
*/
void Index::createClientes(string nombre){
	ifstream file;
	file.open(nombre);
	if(file.fail()){
	} else{
		cout<<"ENTRO ELSE"<<endl;
		Header head;
		file.seekg(0);
		file.read(reinterpret_cast<char*>(&head), sizeof(Header));
		sizeRegistros=head.sizeRegistro; 
		availList=head.availList;

		int RRN;
		vector<IndiceClien> index_cliente;
		file.seekg(8);
		for (int i = 0; i < sizeRegistros; ++i){
			Cliente client;
			file.read(reinterpret_cast<char*>(&client), sizeof(Cliente));

			RRN = i;
			orderIndexCliente(index_cliente, client, RRN);

		}
		ofstream salida("indexClientes.bin", ofstream::binary);
		for (int i = 0; i < index_cliente.size(); i++){
			salida.write(reinterpret_cast<const char*> (&index_cliente.at(i)), sizeof(IndiceClien));
		}
	}
}

/*
	Metodo para crear lineas
*/
void Index::createLineas(string nombre){
	ifstream file;
	file.open(nombre);
	if(file.fail()){
		cerr << "Error al abrir el archivo." << endl;
	} else{
		file.read(reinterpret_cast<char*>(&sizeRegistros), sizeof(sizeRegistros));
		file.read(reinterpret_cast<char*>(&availList), sizeof(availList));

		int RRN;
		vector<IndiceClien>index;
		
		for (int i = 0; i < sizeRegistros; ++i){
			LineaxCliente lineas;
			file.read(reinterpret_cast<char*>(&lineas), sizeof(lineas));

			RRN = i;
			orderIndexLineaxCliente(index, lineas, RRN);

		}
		ofstream salida("indexLineasXCliente.bin", ofstream::binary);
		for (int i = 0; i < index.size(); i++){
			salida.write(reinterpret_cast<const char*> (&index.at(i).id_clie_index), sizeof(index.at(i).id_clie_index));
			salida.write(reinterpret_cast<const char*> (&index.at(i).RRN_index), sizeof(index.at(i).RRN_index));
		}
	}
}

/*
	Ordena el vector del indice de las ciudades
*/
void Index::orderIndexCiudad(vector<Indice>& indexC, Ciudad city, int RRN){
	int tamano = indexC.size();
	Indice indice;
	indice.id_ciu_index = city.idCiudad;
	indice.RRN_index = RRN;

	vector<Indice>::iterator it;
  	it = indexC.begin();

	if(tamano == 0)
		indexC.push_back(indice);
	else{
		int primerIndice = 0, ultimoIndice = tamano - 1, centro;
		while (primerIndice <= ultimoIndice)
	    {
	    	centro = (ultimoIndice + primerIndice)/2;
		    if (indexC.at(centro).id_ciu_index == city.idCiudad){
				indexC.insert(it + centro, indice);
			}
		    else{
		 		if (city.idCiudad < indexC.at(centro).id_ciu_index){
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
	indexCiudades = indexC;
}

/*
	Ordena el vector del indice de los clientes
*/
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
	    		if (strncmp(indexC.at(centro).id_clie_index,client.idCliente,14)==0){
				cerr<<"Ya existe ese id"<<endl;
			}
	    		else{
 				if (strncmp(client.idCliente,indexC.at(centro).id_clie_index,14)<0){
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

/*
	Ordena el vector del indice de las lineas x cliente
*/
void Index::orderIndexLineaxCliente(vector<IndiceClien>& indexC, LineaxCliente line, int RRN){
	int tamano = indexC.size();
	IndiceClien indice;
	strcpy(indice.id_clie_index, line.idCliente);
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
		    if ( strncmp(indexC.at(centro).id_clie_index, line.idCliente, 14) == 0 ){
				indexC.insert(it + centro, indice);
			}
		    else{
		 		if ( strncmp(line.idCliente, indexC.at(centro).id_clie_index, 14) == 0 ){
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
	indexClientesOLineas = indexC;
}

/*
	Metodo para buscar una ciudad, retorna la posicion en el vector
*/
int Index::busquedaCiudad(Ciudad city){
	int primerIndice = 0, ultimoIndice = indexCiudades.size() - 1, centro;

	while (primerIndice <= ultimoIndice)
    {
    	centro = (ultimoIndice + primerIndice)/2;
	    if (indexCiudades.at(centro).id_ciu_index == city.idCiudad){
			return centro;
		}
	    else{
	 		if (city.idCiudad < indexCiudades.at(centro).id_ciu_index){
	   			ultimoIndice=centro-1;
	   		}
	 		else{
	   			primerIndice=centro+1;
	   		}
	   	}
    }
    return -1;
}

/*
	Metodo para buscar un cliente, retorna la posicion en el vector
*/
int Index::busquedaClientes(Cliente client){
	int primerIndice = 0, ultimoIndice = indexCiudades.size() - 1, centro;

	while (primerIndice <= ultimoIndice)
    {
    	centro = (ultimoIndice + primerIndice)/2;
	    if (strncmp(indexClientesOLineas.at(centro).id_clie_index, client.idCliente, 14) == 0 ){
			return centro;
		}
	    else{
	 		if (strncmp(client.idCliente, indexClientesOLineas.at(centro).id_clie_index, 14) < 0 ){
	   			ultimoIndice=centro-1;
	   		}
	 		else{
	   			primerIndice=centro+1;
	   		}
	   	}
    }
    return -1;
}

/*
	Metodo para buscar una linea x cliente, retorna la posicion en el vector
*/
int Index::busquedaLineas(LineaxCliente linea){
	int primerIndice = 0, ultimoIndice = indexCiudades.size() - 1, centro;

	while (primerIndice <= ultimoIndice)
    {
    	centro = (ultimoIndice + primerIndice)/2;
	    if (strncmp(indexClientesOLineas.at(centro).id_clie_index, linea.idCliente, 14) == 0 ){
			return centro;
		}
	    else{
	 		if (strncmp(linea.idCliente, indexClientesOLineas.at(centro).id_clie_index, 14) < 0 ){
	   			ultimoIndice=centro-1;
	   		}
	 		else{
	   			primerIndice=centro+1;
	   		}
	   	}
    }
    return -1;
}
