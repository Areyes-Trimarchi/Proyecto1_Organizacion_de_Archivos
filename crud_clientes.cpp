#include "crud_clientes.h"
#include "index.h"
#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <vector>
#include <sstream>

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
	Cliente cliente;
	ifstream file_cliente("clientes.bin", ifstream::binary);
	file_cliente.seekg(8);
	while (file_cliente.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))){
		clientes.push_back(cliente);
	}
	file_cliente.close();	
}

Crud_Clientes::~Crud_Clientes(){

}

bool Crud_Clientes::Indexar(){
	char nombre_file[14];
	strncpy(nombre_file,"indexClientes.bin",14);
	Index indice(nombre_file);
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
		cerr<<"OCURRIO UN ERROR ABRIENDO EL INDEX DE CLIENTES"<<endl;
	}else{
		char nombre_Cliente[40];
		char idCliente[14];
		int id_Ciudad;
		char genero;
		Cliente client;
		cout<<"Ingrese el nombre del cliente: ";
		cin>>nombre_Cliente;
		cout<<"Ingrese el id del cliente(debe de contener 13 digitos): ";
		cin>>idCliente;
		int id_Cliente_size=0;
		for (int i = 0; i < 14; ++i)
			{
				if(idCliente[i]=='0'||idCliente[i]=='1'||idCliente[i]=='2'||idCliente[i]=='3'||idCliente[i]=='4'||idCliente[i]=='5'||idCliente[i]=='6'||idCliente[i]=='7'||idCliente[i]=='8'||idCliente[i]=='9'){
					id_Cliente_size++;
				}
			}
		while(id_Cliente_size<13||VerificarIndex(idCliente)){
			cout<<"Ocurrio un error con el id que ingreso.\nIngrese el id del cliente(debe de contener 13 digitos): ";
			cin>>idCliente;
			id_Cliente_size=0;
			for (int i = 0; i < 14; ++i)
			{
				if(idCliente[i]=='0'||idCliente[i]=='1'||idCliente[i]=='2'||idCliente[i]=='3'||idCliente[i]=='4'||idCliente[i]=='5'||idCliente[i]=='6'||idCliente[i]=='7'||idCliente[i]=='8'||idCliente[i]=='9'){
					id_Cliente_size++;
				}
			}
		}
		cout<<"Ingrese el genero del cliente(M/F): ";
		cin>>genero;
		cout<<"Ingrese la ciudad a la que pertenece el ID cliente: ";
		cin>>id_Ciudad;
		strncpy(client.idCliente,idCliente,14);
		strncpy(client.name,nombre_Cliente,40);
		client.genero=genero;
		client.idCiudad=id_Ciudad;
		Header head;
		ifstream file_cliente;
		file_cliente.open("clientes.bin");
		file_cliente.seekg(0);
		file_cliente.read(reinterpret_cast<char*>(&head), sizeof(Header));
		file_cliente.close();
		if(head.availList<0){
			head.sizeRegistro=head.sizeRegistro+1;
			ofstream salida_cliente("clientes.bin", ofstream::app);
			UpdateIndex(indice_clientes, client, head.sizeRegistro-1);
			salida_cliente.write(reinterpret_cast<const char*> (&client), sizeof(Cliente));
			salida_cliente.close();
			ReescribirArchivo(head,client,head.sizeRegistro-1);
		}else{
			ifstream file_cliente;
			file_cliente.open("clientes.bin");
			Cliente cliente;
			file_cliente.read(reinterpret_cast<char*>(&head), sizeof(Header));
			head.sizeRegistro=head.sizeRegistro+1;
			int RRN=head.availList;
			int nextavail;
			int ecuacion=(sizeof(Header)+(sizeof(Cliente)*RRN));
			file_cliente.seekg(ecuacion);
			file_cliente.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente));
			if(cliente.idCliente[1]=='-'){
				nextavail=(-1);
			}else{
				string new_avail;
				char tmp_avail[14];
				stringstream ss;
				for (int i = 1; i < 14; ++i)
				{
					if(cliente.idCliente[i]!='+'){
						tmp_avail[i-1]=cliente.idCliente[i];
					}else{
						tmp_avail[i-1]='+';
					}
				}
				ss<<tmp_avail;
				new_avail=ss.str();
				istringstream ( new_avail ) >> nextavail;
			}
			head.availList=nextavail;
			file_cliente.close();	
			for (int i = 0; i < indice_clientes.size(); ++i)
			{
				if(indice_clientes.at(i).RRN_index==RRN){
					indice_clientes.erase(indice_clientes.begin()+i);
					break;
				}
			}
			UpdateIndex(indice_clientes, client, RRN);
			ReescribirArchivo(head,client,RRN);	
		}
		file_index.close();
	}
	return true;
}

bool Crud_Clientes::Borrar(){
	Cliente client;
	char idCliente[14];
	cout<<"Ingrese un numero de identidad para localizar el cliente que borrara: ";
	cin>>idCliente;
	int id_Cliente_size=0;
	for (int i = 0; i < 14; ++i)
	{
		if(idCliente[i]=='0'||idCliente[i]=='1'||idCliente[i]=='2'||idCliente[i]=='3'||idCliente[i]=='4'||idCliente[i]=='5'||idCliente[i]=='6'||idCliente[i]=='7'||idCliente[i]=='8'||idCliente[i]=='9'){
			id_Cliente_size++;
		}
	}
	while(id_Cliente_size!=13){
		cout<<"Ocurrio un error con el id que ingreso.\nIngrese el id del cliente(debe de contener 13 digitos): ";
		cin>>idCliente;
		id_Cliente_size=0;
		for (int i = 0; i < 14; ++i)
		{
			if(idCliente[i]=='0'||idCliente[i]=='1'||idCliente[i]=='2'||idCliente[i]=='3'||idCliente[i]=='4'||idCliente[i]=='5'||idCliente[i]=='6'||idCliente[i]=='7'||idCliente[i]=='8'||idCliente[i]=='9'){
				id_Cliente_size++;
			}
		}
	}
	Header head;
	ifstream file_cliente;
	file_cliente.open("clientes.bin");
	int RRN;
	IndiceClien indice_clien;
	ifstream file_indice("indexClientes.bin", ifstream::binary);
	while (file_indice.read(reinterpret_cast<char*>(&indice_clien), sizeof(IndiceClien))){
		
		if(strncmp(idCliente,indice_clien.id_clie_index,13)==0){
			RRN=indice_clien.RRN_index;	
			break;
		}
	}
	file_indice.close();
	file_cliente.seekg(0);
	file_cliente.read(reinterpret_cast<char*>(&head), sizeof(Header));
	int availList=head.availList;
	int sizeRegistro=head.sizeRegistro;
	if(RRN<0||RRN>sizeRegistro-1){
		cout<<"El cliente que usted intenta borrar no existe "<<endl;
	}else{
		head.sizeRegistro=head.sizeRegistro-1;
		int ecuacion=(sizeof(Header)+(sizeof(Cliente)*RRN));
		file_cliente.seekg(ecuacion);
		file_cliente.read(reinterpret_cast<char*>(&client), sizeof(Cliente));
		cout<<"El cliente que esta siendo borrado es: "<<endl;
		cout<<client<<endl;
		if(availList<0){
			head.availList=RRN;
			client.idCliente[0]='*';
			client.idCliente[1]='-';
			for (int i = 2; i < 14; ++i)
			{
				client.idCliente[i]='+';
			}
			strncpy(indice_clien.id_clie_index,client.idCliente,14);
			ReescribirArchivo(head,client,RRN);
		}else{
			head.availList=RRN;
			client.idCliente[0]='*';
			stringstream ss;
			ss << availList;
			string new_availString=ss.str();
			cout<<"AVAILLIST NUEVO "<<new_availString<<" LENGTH "<<new_availString.length()<<endl;
			for (int i = 0; i < new_availString.length(); ++i)
			{
				client.idCliente[i+1]=new_availString[i];
			}
			for (int i = new_availString.length()+1; i < 14; ++i)
			{
				client.idCliente[i]='+';
			}
			strncpy(indice_clien.id_clie_index,client.idCliente,14);
			ReescribirArchivo(head,client,RRN);
		}
	}
	file_cliente.close();
	return true;
}

bool Crud_Clientes::Modificar(){
	Borrar();
	Agregar();
	return true;
}

bool Crud_Clientes::Listar(){
	cout<<"Lista de Clientes"<<endl;
	CargarVectorIndice();
	Cliente client;
	ifstream file_cliente;
	file_cliente.open("clientes.bin");
	file_cliente.seekg(0);
	Header head;
	file_cliente.read(reinterpret_cast<char*>(&head), sizeof(Header));
	int sizeRegistros=head.sizeRegistro;
	int RRN;
	IndiceClien indice_clien;
	ifstream file_indice("indexClientes.bin", ifstream::binary);
	while (file_indice.read(reinterpret_cast<char*>(&indice_clien), sizeof(IndiceClien))){
		
		RRN=indice_clien.RRN_index;
		//cout<<"BORRADOS "<<((ElementoBorrado(RRN)*sizeof(Cliente))<<endl;
		int ecuacion=(sizeof(Header)+(sizeof(Cliente)*RRN));
		file_cliente.seekg(ecuacion);
		file_cliente.read(reinterpret_cast<char*>(&client), sizeof(Cliente));
		if(client.idCliente[0]!='*'){
			cout<<client<<endl;
		}
	}
	file_indice.close();
	file_cliente.close();

	return true;
}

bool Crud_Clientes::BuscarIndex(){
	Cliente client;
	cout<<"Buscar por Indice"<<endl;
	char idCliente[14];
	cout<<"Ingrese un numero de identidad para realizar la busqueda: ";
	cin>>idCliente;
	int id_Cliente_size=0;
	for (int i = 0; i < 14; ++i)
	{
		if(idCliente[i]=='0'||idCliente[i]=='1'||idCliente[i]=='2'||idCliente[i]=='3'||idCliente[i]=='4'||idCliente[i]=='5'||idCliente[i]=='6'||idCliente[i]=='7'||idCliente[i]=='8'||idCliente[i]=='9'){
			id_Cliente_size++;
		}
	}
	while(id_Cliente_size!=13){
		cout<<"Ocurrio un error con el id que ingreso.\nIngrese el id del cliente(debe de contener 13 digitos): ";
		cin>>idCliente;
		id_Cliente_size=0;
		for (int i = 0; i < 14; ++i)
		{
			if(idCliente[i]=='0'||idCliente[i]=='1'||idCliente[i]=='2'||idCliente[i]=='3'||idCliente[i]=='4'||idCliente[i]=='5'||idCliente[i]=='6'||idCliente[i]=='7'||idCliente[i]=='8'||idCliente[i]=='9'){
				id_Cliente_size++;
			}
		}
	}
	Header head;
	cout<<"El cliente que usted busca es: "<<endl;
	ifstream file_cliente;
	file_cliente.open("clientes.bin");
	int RRN;
	IndiceClien indice_clien;
	ifstream file_indice("indexClientes.bin", ifstream::binary);
	while (file_indice.read(reinterpret_cast<char*>(&indice_clien), sizeof(IndiceClien))){
		
		if(strncmp(idCliente,indice_clien.id_clie_index,13)==0){
			RRN=indice_clien.RRN_index;	
			break;
		}
	}
	file_indice.close();
	file_cliente.seekg(0);
	file_cliente.read(reinterpret_cast<char*>(&head), sizeof(Header));
	if(RRN<0||RRN>head.sizeRegistro-1){
		cout<<"El cliente que usted busca no existe "<<endl;
	}else{
		//((ElementoBorrado(RRN)*sizeof(Cliente));//ELEMENTO QUE NO APARECE
		int ecuacion=(sizeof(Header)+(sizeof(Cliente)*RRN));
		file_cliente.seekg(ecuacion);
		file_cliente.read(reinterpret_cast<char*>(&client), sizeof(Cliente));
		cout<<client<<endl;
	}
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
			if(idCliente[i]=='0'||idCliente[i]=='1'||idCliente[i]=='2'||idCliente[i]=='3'||idCliente[i]=='4'||idCliente[i]=='5'||idCliente[i]=='6'||idCliente[i]=='7'||idCliente[i]=='8'||idCliente[i]=='9'){
				id_Cliente_size++;
			}
		}
	while(id_Cliente_size!=13){
		cout<<"Ocurrio un error con el id que ingreso.\nIngrese el id del cliente(debe de contener 13 digitos): ";
		cin>>idCliente;
		id_Cliente_size=0;
		for (int i = 0; i < 14; ++i)
		{
			if(idCliente[i]=='0'||idCliente[i]=='1'||idCliente[i]=='2'||idCliente[i]=='3'||idCliente[i]=='4'||idCliente[i]=='5'||idCliente[i]=='6'||idCliente[i]=='7'||idCliente[i]=='8'||idCliente[i]=='9'){
				id_Cliente_size++;
			}
		}
	}
	cout<<"El cliente que usted busca es: "<<endl;
	ifstream file_cliente;
	file_cliente.open("clientes.bin");
	file_cliente.seekg(sizeof(Header));
	int contador=0;
	while (file_cliente.read(reinterpret_cast<char*>(&client), sizeof(Cliente))){
		if(strncmp(idCliente,client.idCliente,13)==0){
			cout << client << endl;
			contador++;
			break;
		}
	}
	if(contador==0){
		cout<<"El cliente que usted busca no existe "<<endl;
	}
	file_cliente.close();
	return true;
}

bool Crud_Clientes::Reindexar(){
	return true;
}

bool Crud_Clientes::VerificarIndex(char idCliente[14]){
	IndiceClien indice_clien;
	ifstream file_indice("indexClientes.bin", ifstream::binary);
	while (file_indice.read(reinterpret_cast<char*>(&indice_clien), sizeof(IndiceClien))){
		
		if(strncmp(idCliente,indice_clien.id_clie_index,13)==0){
			return true;
		}
	}
	file_indice.close();
	return false;
}

void Crud_Clientes::UpdateIndex(vector<IndiceClien>& indexC, Cliente client, int RRN){
	int tamano = indexC.size();
	IndiceClien indice;
	strcpy(indice.id_clie_index, client.idCliente);
	indice.RRN_index = RRN;

	vector<IndiceClien>::iterator it;
  	it = indexC.begin();

	if(tamano == 0){
		indexC.push_back(indice);
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
	Cliente cliente;
	ifstream file("clientes.bin", ifstream::binary);
	file.seekg(8);
	while (file.read(reinterpret_cast<char*>(&cliente), sizeof(Cliente))&&contador<RRN){
		if(cliente.idCliente[0]=='*'){
			borrados++;	
		}
		contador++;
	}
	file.close();
	return borrados;
}

void Crud_Clientes::ReescribirArchivo(Header head,Cliente cliente,int RRN){
	CargarVectorClientes(cliente,RRN);
	ofstream salida_index("indexClientes.bin", ofstream::binary);
	for (int i = 0; i < indice_clientes.size(); i++){
		salida_index.write(reinterpret_cast<const char*> (&indice_clientes.at(i)), sizeof(IndiceClien));
	}
	salida_index.close();
	ofstream salida_cliente("clientes.bin", ofstream::binary);
	salida_cliente.seekp(0);
	salida_cliente.write(reinterpret_cast<const char*> (&head), sizeof(Header));
	salida_cliente.seekp(8);
	for (int i = 0; i < clientes.size(); i++){
		salida_cliente.write(reinterpret_cast<const char*> (&clientes.at(i)), sizeof(Cliente));
	}
	salida_cliente.close();

}

void Crud_Clientes::CargarVectorClientes(Cliente cliente,int RRN){
	int entro=0;
	for (int i = 0; i < clientes.size(); ++i)
	{
		if(i==RRN&&RRN<clientes.size()){
			clientes.at(i)=cliente;
			entro++;
			break;
		}
	}
	if(entro==0){
		clientes.push_back(cliente);
	}
}

void Crud_Clientes::CargarVectorIndice(){
	indice_clientes.clear();
	IndiceClien indice_clien;
	ifstream file("indexClientes.bin", ifstream::binary);
	while (file.read(reinterpret_cast<char*>(&indice_clien), sizeof(IndiceClien))){
		indice_clientes.push_back(indice_clien);
	}
	file.close();
}