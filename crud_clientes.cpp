#include "crud_clientes.h"
//#include "index.h"
#include <iostream>
#include <string>

using namespace std;

crud_clientes::crud_clientes(){

}

crud_clientes::~crud_clientes(){

}

bool crud_clientes::Agregar(){
	cout<<"Agregar Cliente"<<endl;
	string id_Cliente;
	string nombre_Cliente;
	int id_Ciudad;
	char genero;
	Cliente client;
	cout<<"Ingrese el nombre del cliente: ";
	cin>>nombre_Cliente;
	cout<<"Ingrese el id del cliente(debe de contener 13 digitos): ";
	cin>>id_Cliente;
	while(id_Cliente.size()<13){
		cout<<"Ingrese el id del cliente(debe de contener 13 digitos): ";
		cin>>id_Cliente;
	}
	cout<<"Ingrese el genero del cliente(M/F): ";
	cin>>genero;

	client.idCliente=id_Cliente;
	client.nombre_cliente=nombre_Cliente;
	client.genero=genero;
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