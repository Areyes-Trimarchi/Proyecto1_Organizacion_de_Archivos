#include "index.h"
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstring>
#include <stdio.h>

using namespace std;


/*ostream& operator<<(ostream& output, const Indice& city){
	output << city.id_ciu_index << "\t" << city.RRN_index << endl;
	return output;  
}*/

/*
	Constructor
	Tiene que verificar si existe indice, sino lo crea; si ya existia previamente, lo carga
*/
Index::Index(string nombre){
	this->direccion = nombre;
	ifstream file;
	file.open(direccion);

	if(!file.good()){
		cout << "No existe" << endl;
		create(direccion);
	} else{
		cout << "Cargando" << endl;
		load();
	}
	file.close();
}

Index::~Index(){

}

/*
	Agregar al indice
	Verifica que tipo agrega y funciona con ek metodo apropiado por tipo
*/
bool Index::add(Ciudad city, int rrn){
	orderIndexCiudad(indexCiudades, city, rrn);
	guardarCiudades();
	return true;
}

bool Index::add(Cliente client, int rrn){
	orderIndexCliente(indexClientesOLineas, client, rrn);
	guardarClientes();
	return true;
}

bool Index::add(LineaxCliente linea, int rrn){
	orderIndexLineaxCliente(indexClientesOLineas, linea, rrn);
	guardarLineas();
	return true;
}

/*
	Remover del indice
	Verifica que tipo elininara y trabaja con el metodo dependiendo del tipo
*/
bool Index::remove(Ciudad city){
	int RRN = busquedaCiudad(city);
	indexCiudades.erase(indexCiudades.begin() + RRN);
	guardarCiudades();
	return true;
}

bool Index::remove(Cliente client){
	int RRN = busquedaClientes(client);
	indexClientesOLineas.erase(indexClientesOLineas.begin() + RRN);
	guardarClientes();
	return true;
}

bool Index::remove(LineaxCliente linea){
	int RRN = busquedaLineas(linea);
	indexClientesOLineas.erase(indexClientesOLineas.begin() + RRN);
	guardarLineas();
	return true;
}

/*
	Retornar una ciudad es tipo Indice
*/
Indice Index::get(Ciudad city){
	int regresar;
	Indice i;
	i.RRN_index = -99;
	regresar = busquedaCiudad(city);
	if(regresar != -1)	
		return indexCiudades.at(regresar);
	else
		return i;
}

/*
	Retornar un cliente es de tipo IndiceClien
*/
IndiceClien Index::get(Cliente client){
	int regresar;
	regresar = busquedaClientes(client);
	IndiceClien i;
	i.RRN_index = -99;
	if(regresar != -1)
		return indexClientesOLineas.at(regresar);
	else
		return i;
}

/*
	Retornar una linea x cliente es de tipo IndiceClien
*/
IndiceClien Index::get(LineaxCliente linea){
	int regresar;
	regresar = busquedaLineas(linea);
	IndiceClien i;
	i.RRN_index = -99;
	if(regresar != -1)
		return indexClientesOLineas.at(regresar);
	else
		return i;
}

/*
	Retornar una ciudad en base al numero
*/
Indice Index::at(int pos, Ciudad city){
	return indexCiudades.at(pos);
}

/*
	Retornar un cliente en base al numero
*/
IndiceClien Index::at(int pos, Cliente client){
	return indexClientesOLineas.at(pos);

}

/*
	Retornar una linea x cliente en base al numero
*/
IndiceClien Index::at(int pos, LineaxCliente linea){
	return indexClientesOLineas.at(pos);
}

void Index::reindex(){

}

/*
	Metodo para crear el indice por si no ha sido creado
*/
void Index::create(string nombre){
	if(nombre ==  "indexCiudades.bin")
		createCiudades(nombre);
	else if(nombre ==  "indexClientes.bin"){
		char* hola;
		createClientes( strcpy(hola, nombre.c_str()) );
	}
	else
		createLineas(nombre);
}

/*
	Metodo para crear ciudades
*/
void Index::createCiudades(string nombre){
	ifstream file;
	file.open("ciudades.bin");
	if(!file.is_open()){
		cerr << "Error al abrir el archivo. Aqui es el error" << endl;
	} else{
		Header head;

		file.seekg(0);
		file.read(reinterpret_cast<char*>(&head), sizeof(Header));
		sizeRegistros = head.sizeRegistro; 
		availList = head.availList;

		int RRN;
		vector<Indice>index;
		
		cout << "3 sizeRegistros = " << sizeRegistros << "\tAvail = " << availList  << "\tUltimo = " << head.sizeRegistro << endl;
		for (int i = 0; i < sizeRegistros; ++i){
			Ciudad city;
			file.read(reinterpret_cast<char*>(&city), sizeof(Ciudad));

			RRN = i;
			orderIndexCiudad(index, city, RRN);

		}
		ofstream salida("indexCiudades.bin", ofstream::binary);
		for (int i = 0; i < index.size(); i++){
			salida.write(reinterpret_cast<const char*> (&index.at(i)), sizeof(Indice));
		}
		salida.close();
	}
	file.clear();
	file.seekg(0);
	file.close();
}

/*
	Metodo para crear Clientes
*/
void Index::createClientes(char* nombre){
	ifstream file;
	file.open("clientes.bin");
	if(!file.is_open()){
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
		salida.close();
	}
}

/*
	Metodo para crear lineas
*/
void Index::createLineas(string nombre){
	ifstream file;
	file.open("lineasxcliente.bin");
	if(!file.is_open()){
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
			salida.write(reinterpret_cast<const char*> (&index.at(i)), sizeof(IndiceClien));
		}
		salida.close();
	}
	file.close();
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
	else if(city.idCiudad != -99){
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

void Index::load(){
	if(this->direccion ==  "indexCiudades.bin")
		cargarCiudades();
	else if(this->direccion ==  "indexClientes.bin"){
		char* hola;
		cargarClientes();
	}
	else
		cargarLineas();
}

void Index::cargarCiudades(){
	ifstream file;
	file.open("indexCiudades.bin");
	if(file.fail()){
		cerr << "Error al abrir el archivo." << endl;
	} else{
		Indice indi;
		while(file.read(reinterpret_cast<char*>(&indi), sizeof(Indice))){
			indexCiudades.push_back(indi);
		}
	}
}

void Index::cargarClientes(){
	ifstream file;
	file.open("indexClientes.bin");
	if(file.fail()){
		cerr << "Error al abrir el archivo." << endl;
	} else{
		IndiceClien indi;
		while(file.read(reinterpret_cast<char*>(&indi), sizeof(IndiceClien))){
			indexClientesOLineas.push_back(indi);
		}
	}
}

void Index::cargarLineas(){
	ifstream file;
	file.open("indexLineasXCliente.bin");
	if(file.fail()){
		cerr << "Error al abrir el archivo." << endl;
	} else{
		IndiceClien indi;
		while(file.read(reinterpret_cast<char*>(&indi), sizeof(IndiceClien))){
			indexClientesOLineas.push_back(indi);
		}
	}
}

void Index::guardarCiudades(){
	ofstream salida("indexCiudades.bin", ofstream::binary);
	for (int i = 0; i < indexCiudades.size(); i++){
		salida.write(reinterpret_cast<const char*> (&indexCiudades.at(i)), sizeof(Indice));
	}
	salida.close();
}

void Index::guardarClientes(){
	ofstream salida("indexClientes.bin", ofstream::binary);
	for (int i = 0; i < indexClientesOLineas.size(); i++){
		salida.write(reinterpret_cast<const char*> (&indexClientesOLineas.at(i)), sizeof(IndiceClien));
	}
	salida.close();
}

void Index::guardarLineas(){
	ofstream salida("indexLineasXCliente.bin", ofstream::binary);
	for (int i = 0; i < indexClientesOLineas.size(); i++){
		salida.write(reinterpret_cast<const char*> (&indexClientesOLineas.at(i)), sizeof(IndiceClien));
	}
	salida.close();
}

Indice Index::ciudadRRN(int rrn, Ciudad city){
	Indice c;
	for (int i = 0; i < indexCiudades.size(); ++i)
		if(rrn == indexCiudades.at(i).RRN_index){
			return indexCiudades.at(i);
		}
	return c;
}

IndiceClien Index::clienteRRN(int rrn, Cliente client){

}

IndiceClien Index::lineaRRN(int rrn, LineaxCliente linea){
	IndiceClien c;
	for (int i = 0; i < indexClientesOLineas.size(); ++i)
		if(rrn == indexClientesOLineas.at(i).RRN_index)
			return indexClientesOLineas.at(i);
	return c;
}