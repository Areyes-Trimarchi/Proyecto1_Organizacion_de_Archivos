#include "crud_clientes.h"
#include "index.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <vector>

using namespace std;

ostream& operator<<(ostream& output, const Cliente& cliente){
	output <<"NOMBRE "<< cliente.name << "\t" <<" IDCLIENTE "<< cliente.idCliente << "\t" <<" GENERO "<< cliente.genero << "\t" <<" ID CIUDAD "<< cliente.idCiudad;
	return output;
}

Crud_Clientes::Crud_Clientes(){
	ifstream file_index;
	file_index.open("indexClientes.bin");
	if(file_index.fail()){
		Indexar();
	}else{
		IndiceClien index;
		while(file_index.read(reinterpret_cast<char*> (&index), sizeof(IndiceClien))){
			indice_clientes.push_back(index);
		}
	}
	file_index.close();
}

Crud_Clientes::~Crud_Clientes(){

}

bool Crud_Clientes::Indexar(){
	Index indice("clientes.bin");
	ifstream file_index;
	file_index.open("indexClientes.bin");
	IndiceClien index;
	while(file_index.read(reinterpret_cast<char*> (&index), sizeof(IndiceClien))){
		indice_clientes.push_back(index);
	}
	file_index.close();
}

bool Crud_Clientes::Agregar(){
	ifstream file_index;
	file_index.open("indexClientes.bin");
	if(file_index.fail()){
		cerr<<"OCURRIO UN ERROR ABRIENDO EL INDEX DE CLEINTES"<<endl;
	}else{
		cout<<"Agregar Cliente"<<endl;
		char nombre_Cliente[40];
		char id_Cliente[14];
		int id_Ciudad;
		char genero;
		Cliente client;
		cout<<"Ingrese el nombre del cliente: ";
		cin>>nombre_Cliente;
		cout<<"Ingrese el id del cliente(debe de contener 13 digitos): ";
		cin>>id_Cliente;
		int id_Cliente_size=0;
		for (int i = 0; i < 14; ++i)
		{
			if(id_Cliente[i]!='\0'){
				id_Cliente_size++;
			}
		}
		while(id_Cliente_size<13||VerificarIndex(id_Cliente)){
			cout<<"Ocurrio un error con el id que ingreso.\nIngrese el id del cliente(debe de contener 13 digitos): ";
			cin>>id_Cliente;
			for (int i = 0; i < 14; ++i)
			{
				if(id_Cliente[i]!='\0'){
					id_Cliente_size++;
				}
			}
		}
		cout<<"Ingrese el genero del cliente(M/F): ";
		cin>>genero;
		strncpy(client.idCliente,id_Cliente,14);
		strncpy(client.name,nombre_Cliente,40);
		client.genero=genero;
		Header head;
		ifstream file_cliente;
		file_cliente.open("clientes.bin");
		file_cliente.seekg(0);
		file_cliente.read(reinterpret_cast<char*>(&head), sizeof(Header));
		ofstream salida_cliente("clientes.bin", ofstream::binary);
		if(head.availList==-1){
			head.sizeRegistro=head.sizeRegistro+1;
			salida_cliente.write(reinterpret_cast<char*>(&client), sizeof(Cliente));
			salida_cliente.seekp(0);
			salida_cliente.write(reinterpret_cast<char*>(&head), sizeof(Header));
			int posicion=UpdateIndex(indice_clientes, client, head.sizeRegistro);
			cout<<"POSICIION "<<posicion<<endl;
			ofstream salida_index("indexClientes.bin", ofstream::binary);
			salida_index.seekp(posicion);
			salida_index.write(reinterpret_cast<const char*> (&indice_clientes.at(posicion)), sizeof(IndiceClien));
		}else{
			
		}
		file_cliente.close();
		file_index.close();
	}
	return true;
}

bool Crud_Clientes::Borrar(){
	return true;
}

bool Crud_Clientes::Modificar(){
	return true;
}

bool Crud_Clientes::Listar(){
	cout<<"Lista de Clientes"<<endl;
	Cliente client;
	ifstream file_cliente;
	file_cliente.open("clientes.bin");
	file_cliente.seekg(0);
	Header head;
	file_cliente.read(reinterpret_cast<char*>(&head), sizeof(Header));
	int sizeRegistros=head.sizeRegistro;
	int RRN;
	for (int i = 0; i < indice_clientes.size(); ++i)
	{
		RRN=indice_clientes.at(i).RRN_index;
		int ecuacion=(sizeof(Header)+((ElementoBorrado(RRN))*sizeof(Cliente))+(sizeof(Cliente)*RRN));
		file_cliente.seekg(ecuacion);
		file_cliente.read(reinterpret_cast<char*>(&client), sizeof(Cliente));
		cout<<client<<endl;	
	}
	file_cliente.close();

	return true;
}

bool Crud_Clientes::BuscarIndex(){
	Cliente client;
	cout<<"Buscar por Indice"<<endl;;
	char idCliente[14];
	cout<<"Ingrese un numero de identidad para realizar la busqueda: ";
	cin>>idCliente;
	int id_Cliente_size=0;
	for (int i = 0; i < 14; ++i)
	{
		if(idCliente[i]!='\0'){
			id_Cliente_size++;
		}
	}
	while(id_Cliente_size<13){
		cout<<"Ocurrio un error con el id que ingreso.\nIngrese el id del cliente(debe de contener 13 digitos): ";
		cin>>idCliente;
	}
	int RRN;
	for (int i = 0; i < indice_clientes.size(); ++i)
	{
		if(strncmp(idCliente,indice_clientes.at(i).id_clie_index,13)==0){
			RRN=indice_clientes.at(i).RRN_index;	
		}
	}
	cout<<"El cliente que usted busca es: "<<endl;
	ifstream file_cliente;
	file_cliente.open("clientes.bin");
	int ecuacion=(sizeof(Header)+((ElementoBorrado(RRN))*sizeof(Cliente))+(sizeof(Cliente)*RRN));
	file_cliente.seekg(ecuacion);
	file_cliente.read(reinterpret_cast<char*>(&client), sizeof(Cliente));
	cout<<client<<endl;
	file_cliente.close();
	return true;
}

bool Crud_Clientes::Buscar(){
	cout<<"Buscar sin Indice"<<endl;;
	Cliente client;
	char idCliente[14];
	cout<<"Ingrese un numero de identidad para realizar la busqueda: ";
	cin>>idCliente;
	int id_Cliente_size=0;
	for (int i = 0; i < 14; ++i)
	{
		if(idCliente[i]!='\0'){
			id_Cliente_size++;
		}
	}
	while(id_Cliente_size<13){
		cout<<"Ocurrio un error con el id que ingreso.\nIngrese el id del cliente(debe de contener 13 digitos): ";
		cin>>idCliente;
		for (int i = 0; i < 14; ++i)
		{
			if(idCliente[i]!='\0'){
				id_Cliente_size++;
			}
		}
	}
	cout<<"El cliente que usted busca es: "<<endl;
	ifstream file_cliente;
	file_cliente.open("clientes.bin");
	file_cliente.seekg(sizeof(Header));
	while (file_cliente.read(reinterpret_cast<char*>(&client), sizeof(Cliente))){
		if(strncmp(idCliente,client.idCliente,13)==0){
			cout << client << endl;
			break;
		}
	}
	file_cliente.close();
	return true;
}

bool Crud_Clientes::Reindexar(){
	return true;
}

bool Crud_Clientes::VerificarIndex(char idCliente[14]){
	for (int i = 0; i < indice_clientes.size(); ++i)
	{
		if(strncmp(idCliente,indice_clientes.at(i).id_clie_index,14)==0){
			return true;
		}
	}
	return false;
}

int Crud_Clientes::UpdateIndex(vector<IndiceClien>& indexC, Cliente client, int RRN){
	int posicion;
	int tamano = indexC.size();
	IndiceClien indice;
	strcpy(indice.id_clie_index, client.idCliente);
	indice.RRN_index = RRN;

	vector<IndiceClien>::iterator it;
  	it = indexC.begin();

	if(tamano == 0){
		indexC.push_back(indice);
		posicion=0;
	}else{
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
		   			if(ultimoIndice < 0){
		   				indexC.insert(it, indice);
		   			}
		   			else if(ultimoIndice < primerIndice){
		   				indexC.insert(it + primerIndice, indice);
		   			}
		   		}
		 		else{
		   			primerIndice=centro+1;
		   			if(primerIndice > tamano){
		   				indexC.push_back(indice);
		   			}
		   			else if(primerIndice > ultimoIndice){
		   				indexC.insert(it + primerIndice, indice);
		   			}
		   		}
		   	}
	    }
	}
}

int Crud_Clientes::ElementoBorrado(int RRN){
	int borrados=0,contador=0;
	char asterisco[1];
	asterisco[0]='*';
	Cliente cliente;
	ifstream file("clientes.bin", ifstream::binary);
	file.seekg(8);
	while (file.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))&&contador<RRN){
		if(strncmp(cliente.idCliente,asterisco,1)==0){
			borrados++;	
		}
		contador++;
	}
	file.close();
	return borrados;
}