#include "crud_clientes.h"
#include "index.h"
#include <iostream>
#include <string>

using namespace std;

crud_clientes::crud_clientes(){
	ifstream file_index;
	file_index.open("indexClientes.bin");
	if(file_index.fail()){
		Index();
	}else{
		IndiceClien index;
		while(file_index.read(reinterpret_cast<const char*> (&index.at(i)), sizeof(IndiceClien))){
			indice_clientes.push_back(index);
		}
	}
	file_index.close();
}

crud_clientes::~crud_clientes(){

}

bool crud_clientes::Index(){
	Index indice(10,"clientes.bin");
	ifstream file_index;
	file_index.open("indexClientes.bin");
	IndiceClien index;
	while(file_index.read(reinterpret_cast<const char*> (&index.at(i)), sizeof(IndiceClien))){
		indice_clientes.push_back(index);
	}
	file_index.close();
}

bool crud_clientes::Agregar(){
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
		while(id_Cliente.size()<13||VerificarIndex(char[14])){
			cout<<"Ingrese el id del cliente(debe de contener 13 digitos): ";
			cin>>id_Cliente;
		}
		cout<<"Ingrese el genero del cliente(M/F): ";
		cin>>genero;

		client.idCliente=id_Cliente;
		client.nombre_cliente=nombre_Cliente;
		client.genero=genero;
		Header head;
		ifstream file_cliente;
		file_cliente.open();
		file_cliente.seekg(0);
		file_cliente.read(reinterpret_cast<char*>(&head), sizeof(Header));
		if(head.availList==-1){

		}else{
			
		}
		file_index.close();
	}
	return true;
}

bool crud_clientes::Borrar(){
	return true;
}

bool crud_clientes::Modificar(){
	return true;
}

bool crud_clientes::Listar(){
	return true;
}

bool crud_clientes::BuscarIndex(){
	cout<<"Buscar por Indice";
	string id_Cliente;
	cout<<"Ingrese un numero de identidad para realizar la busqueda: ";
	cin>>id_Cliente;
	return true;
}

bool crud_clientes::Buscar(){
	cout<<"Buscar sin Indice";
	string id_Cliente;
	cout<<"Ingrese un numero de identidad para realizar la busqueda: ";
	cin>>id_Cliente;
	return true;
}

bool crud_clientes::Reindexar(){
	return true;
}

bool VerificarIndex(char idCliente[14]){
	for (int i = 0; i < indice_clientes.size(); ++i)
	{
		/* code */
	}
	return false;
}