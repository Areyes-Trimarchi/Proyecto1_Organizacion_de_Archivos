#include "index.h"
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <string>	
#include <unistd.h>

using namespace std;


ostream& operator<<(ostream& output, const IndiceLineas& city){
	output << " idCliente = " << city.numero << "\t" << "\tRRN = " << city.RRN_index << endl;
	return output;  
}

ostream& operator<<(ostream& output, const Indice& city){
	output  << " idCliente = "<< city.id_ciu_index << "\tRRN = " << city.RRN_index << endl;
	return output;  
}
/*ostream& operator<<(ostream& output, const LineaxCliente& city){
	output << city.numero << "\t" << city.idCliente << endl;
	return output;  
}
/*
	Constructor
	Tiene que verificar si existe indice, sino lo crea; si ya existia previamente, lo carga
*/
Index::Index(const char *nombre){
	strncpy(direccion,nombre,14);
	ifstream file;
	file.open(nombre);
	//bool cont = fexists(nombre);
	//int res = access(nombre, F_OK);
	if(!file.good()){
		cout << "Creando" << endl;
		create(nombre);
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
	bool guardar;
	guardar = orderIndexCiudad(indexCiudades, city, rrn);
	guardarCiudades();
	cargarCiudades();
	if(guardar)
		return true;
	else
		return false;
}

bool Index::add(Cliente client, int rrn){
	orderIndexCliente(indexClientes, client, rrn);
	guardarClientes();
	cargarClientes();
	return true;
}

bool Index::add(LineaxCliente linea, int rrn){
	bool guardar;
	guardar = orderIndexLineaxCliente(indexLineas, linea, rrn);
	guardarLineas();
	cargarLineas();
	if(guardar)
		return true;
	else
		return false;
}

/*
	Remover del indice
	Verifica que tipo elininara y trabaja con el metodo dependiendo del tipo
*/
bool Index::remove(Ciudad city){
	int RRN = busquedaCiudad(city);
	if (  RRN != -1 ){
		indexCiudades.erase(indexCiudades.begin() + RRN);
		guardarCiudades();
		return true;
	} else
		return false;
}

bool Index::remove(Cliente client){
	int RRN = busquedaClientes(client);
	if(RRN != -1){
		indexClientes.erase(indexClientes.begin() + RRN);
		guardarClientes();
		return true;
	} else
		return false;
}

bool Index::remove(LineaxCliente linea){
	int RRN = busquedaLineas(linea);
	if ( RRN != -1 ){
		indexLineas.erase(indexLineas.begin() + RRN);
		guardarLineas();
		return true;
	} else
		return false;
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
		return indexClientes.at(regresar);
	else
		return i;
}

/*
	Retornar una linea x cliente es de tipo IndiceClien
*/
IndiceLineas Index::get(LineaxCliente linea){
	int regresar;
	regresar = busquedaLineas(linea);
	IndiceLineas i;
	i.RRN_index = -99;
	if(regresar != -1)
		return indexLineas.at(regresar);
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
	return indexClientes.at(pos);

}

/*
	Retornar una linea x cliente en base al numero
*/
IndiceLineas Index::at(int pos, LineaxCliente linea){
	return indexLineas.at(pos);
}

void Index::reindex(){

}

/*
	Metodo para crear el indice por si no ha sido creado
*/
void Index::create(const char *nombre){
	if(strncmp(nombre, "indexCiudades.bin", 14) == 0 )
		createCiudades(nombre);
	else if(strncmp(nombre, "indexClientes.bin", 14) == 0 ){
		char* hola;
		createClientes( nombre );
	}
	else
		createLineas(nombre);
}

/*
	Metodo para crear ciudades
*/
void Index::createCiudades(const char * nombre){
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
		int skip = 0;
		
		cout << "3 sizeRegistros = " << sizeRegistros << "\tAvail = " << availList  << "\tUltimo = " << head.sizeRegistro << endl;
		for (int i = 0; i < sizeRegistros; i++){
			Ciudad city;
			file.read(reinterpret_cast<char*>(&city), sizeof(Ciudad));

			if(skip == 0)
				RRN = i;
			else
				RRN = i + skip;
			orderIndexCiudad(index, city, RRN);
			if(city.idCiudad == -99){
				i--;
				skip++;
			}
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
void Index::createClientes(const char * nombre){
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
void Index::createLineas(const char * nombre){
	ifstream file;
	file.open("lineaxclientes.bin");
	if(!file.is_open()){
		cerr << "Error al abrir el archivo." << endl;
	} else{
		Header head;

		file.seekg(0);
		file.read(reinterpret_cast<char*>(&head), sizeof(Header));
		sizeRegistros = head.sizeRegistro; 
		availList = head.availList;

		int RRN;
		vector<IndiceLineas> index;
		int skip = 0;
		
		cout << "3 sizeRegistros = " << sizeRegistros << "\tAvail = " << availList  << "\tUltimo = " << head.sizeRegistro << endl;
		for (int i = 0; i < sizeRegistros; ++i){
			LineaxCliente lineas;
			file.read(reinterpret_cast<char*>(&lineas), sizeof(LineaxCliente));

			if(skip == 0)
				RRN = i;
			else
				RRN = i + skip;
			orderIndexLineaxCliente(index, lineas, RRN);
			if(strncmp (lineas.numero, "-99", 9) == 0){
				i--;
				skip++;
			}

		}
		ofstream salida("indexLineasXCliente.bin", ofstream::binary);
		for (int i = 0; i < index.size(); i++){
			salida.write(reinterpret_cast<const char*> (&index.at(i)), sizeof(IndiceLineas));
		}
		salida.close();
	}
	file.close();
}

/*
	Ordena el vector del indice de las ciudades
*/
bool Index::orderIndexCiudad(vector<Indice>& indexC, Ciudad city, int RRN){
	int tamano = indexC.size();
	Indice indice;
	indice.id_ciu_index = city.idCiudad;
	indice.RRN_index = RRN;

	vector<Indice>::iterator it;
  	it = indexC.begin();

	if(tamano == 0 && city.idCiudad != -99)
		indexC.push_back(indice);
	else if(city.idCiudad != -99){
		int primerIndice = 0, ultimoIndice = tamano - 1, centro;
		while (primerIndice <= ultimoIndice)
	    {
	    	centro = (ultimoIndice + primerIndice)/2;
		    if (indexC.at(centro).id_ciu_index == city.idCiudad){
				cerr<<"Ya existe ese id"<<endl;
				return false;
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
	return true;
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
				break;
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
bool Index::orderIndexLineaxCliente(vector<IndiceLineas>& indexC, LineaxCliente line, int RRN){
	int tamano = indexC.size();
	IndiceLineas indice;
	strcpy(indice.numero, line.numero);
	indice.RRN_index = RRN;

	vector<IndiceLineas>::iterator it;
  	it = indexC.begin();
	if(tamano == 0 && strncmp (line.numero, "-99", 9) != 0)
		indexC.push_back(indice);
	else if(strncmp (line.numero, "-99", 9) != 0){
		int primerIndice = 0, ultimoIndice = tamano - 1, centro;
		while (primerIndice <= ultimoIndice)
	    {
	    	centro = (ultimoIndice + primerIndice)/2;
		    if ( strncmp(indexC.at(centro).numero, line.numero, 9) == 0 ){
		    	cout << line.numero << endl;
				cerr<<"Ya existe ese id"<<endl;
				return false;
			}
		    else{
		 		if ( strncmp(line.numero, indexC.at(centro).numero, 9) < 0 ){
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
	indexLineas = indexC;
	return true;
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
	    if (strncmp(indexClientes.at(centro).id_clie_index, client.idCliente, 14) == 0 ){
			return centro;
		}
	    else{
	 		if (strncmp(client.idCliente, indexClientes.at(centro).id_clie_index, 14) < 0 ){
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
	int primerIndice = 0, ultimoIndice = indexLineas.size() - 1, centro;

	while (primerIndice <= ultimoIndice)
    {
    	centro = (ultimoIndice + primerIndice)/2; 
	    if (strncmp(indexLineas.at(centro).numero, linea.numero, 9) == 0 ) {
			return centro;
		}
	    else{
	 		if (strncmp(linea.numero, indexLineas.at(centro).numero, 9) < 0 ){
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
	if(strncmp(this->direccion, "indexCiudades.bin", 14) == 0 )
		cargarCiudades();
	else if(strncmp(this->direccion, "indexClientes.bin", 14) == 0 ){
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
		indexCiudades.clear();
		int i = 0;
		while(file.read(reinterpret_cast<char*>(&indi), sizeof(Indice))){
			indexCiudades.push_back(indi);
			i++;
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
		indexClientes.clear();
		while(file.read(reinterpret_cast<char*>(&indi), sizeof(IndiceClien))){
			indexClientes.push_back(indi);
		}
	}
}

void Index::cargarLineas(){
	ifstream file;
	file.open("indexLineasXCliente.bin");
	if(file.fail()){
		cerr << "Error al abrir el archivo." << endl;
	} else{
		IndiceLineas indi;
		indexLineas.clear();
		while(file.read(reinterpret_cast<char*>(&indi), sizeof(IndiceLineas))){
			indexLineas.push_back(indi);
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
	for (int i = 0; i < indexClientes.size(); i++){
		salida.write(reinterpret_cast<const char*> (&indexClientes.at(i)), sizeof(IndiceClien));
	}
	salida.close();
}

void Index::guardarLineas(){
	ofstream salida("indexLineasXCliente.bin", ofstream::binary);
	for (int i = 0; i < indexLineas.size(); i++){
		salida.write(reinterpret_cast<const char*> (&indexLineas.at(i)), sizeof(IndiceLineas));
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

IndiceLineas Index::lineaRRN(int rrn, LineaxCliente linea){
	IndiceLineas c;
	for (int i = 0; i < indexLineas.size(); ++i)
		if(rrn == indexLineas.at(i).RRN_index)
			return indexLineas.at(i);
	return c;
}

void Index::imprimirIndexLineas(){
	for (int i = 0; i < indexLineas.size(); ++i){
		cout << i << ": " << indexLineas.at(i);
	}
}

bool Index::fexists(const char *filename) {
	ifstream ifile(filename);
  	return ifile;
}