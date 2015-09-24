#include "b-tree.h"
#include "crud_clientesarbol.h"
#include "b-treenode.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>		
#include <string>		
#include <sstream>

using namespace std;

ostream& operator<<(ostream& output, const ClienteArbol& linea){
	output << "IDCLIENTE = " << linea.idCliente << "\tNOMBRE = " << linea.nombre<<"\tCIUDAD = "<<linea.idCiudad<<"\tGENERO = "<<linea.genero<< endl;
	return output;  
}
istream& operator>>(istream& input, ClienteArbol& linea){
	 input >> linea.idCliente >> linea.nombre>>linea.idCiudad>>linea.genero;
	 return input;
}

crud_ClientesArbol::crud_ClientesArbol(){

}

void crud_ClientesArbol::correr(){

	char nombre_archivo[25];
	strncpy(nombre_archivo,"indexClientes.bin",25);
 
	fstream file("indexClientes.bin", fstream::binary);
	file.open("indexClientes.bin");

	BTree tree(5, nombre_archivo);

	HeaderArbol head;
	file.seekg(0);
	file.read(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
	int sizeRegistros = head.sizeRegistro;
	int availList =  head.availList;

	int opcionMenuPrincipal;
	cout << "******* MENU *******\n1) Agregar\n" <<
	"2) Modificar\n" <<
	"3) Listar\n" <<
	"4) Borrar\n" <<
	"5) Buscar\n" <<
	"6) Reindexar" << endl;
	cin >> opcionMenuPrincipal;
	cout << "availList = " << availList << "\t sizeRegistro = " << sizeRegistros << endl; 
	switch(opcionMenuPrincipal){
		case 1:{
			cout << "\tAgregar un Cliente" << endl;

			char nombre[40];
			char idCliente[14];
			int idCiudad;
			char genero;
			cout << "Ingrese el id del cliente: " << endl;
			cin >> idCliente;
			cout << "Ingrese el nombre del cliente: " << endl;
			cin >> nombre;
			cout << "Ingrese el genero: " << endl;
			cin >> genero;
			cout << "Ingrese el id de ciudad: " << endl;
			cin >> idCiudad;
			ClienteArbol clienteNuevo;
			strcpy(clienteNuevo.idCliente, idCliente);
			strcpy(clienteNuevo.nombre, nombre);
			clienteNuevo.genero=genero;
			clienteNuevo.idCiudad=idCiudad;

			KeyChar llave;
			//unsigned long num = atoi(lineaNueva.numero);
			//llave.llave = num;
			strcpy(llave.llave, clienteNuevo.idCliente);
			bool continuarGuardando;
			if (availList < -1)
				llave.RRN = sizeRegistros;
			else
				llave.RRN = availList;
			continuarGuardando = tree.insert(llave);
			if (continuarGuardando){																
				if (availList < -1)
					file.seekp (0, file.end);
				else{
					ClienteArbol cliente;
					int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(ClienteArbol) * availList) );	
					file.seekg(0);
					file.seekg(ecuacion);
					file.read(reinterpret_cast<char*>(&cliente), sizeof(ClienteArbol));
					int nextavail;
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

					file.seekp(0);
					file.seekp(ecuacion);
				}
				file.write(reinterpret_cast<char*>(&clienteNuevo), sizeof(ClienteArbol));
				file.seekp (0, file.beg);
				sizeRegistros++;
				head.sizeRegistro = head.sizeRegistro + 1;
				file.write(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
			}
		}
		break;
		case 2:{
			cout << "\tModificar una Cliente" << endl;

			char nombre[40];
			char idClienteNUEVO[14];
			char idCliente[14];
			char genero;
			int idCiudad;
			cout << "Ingrese el id del cliente a modificar: " << endl;
			cin >> idCliente;
			cout << "Ingrese el NUEVO id del cliente: " << endl;
			cin >> idClienteNUEVO;
			cout << "Ingrese el NUEVO nombre del cliente: " << endl;
			cin >> nombre;
			cout << "Ingrese el NUEVO genero del cliente: " << endl;
			cin >> genero;
			cout << "Ingrese la NUEVA id de la cciudad del cliente: " << endl;
			cin >> idCiudad;

			ClienteArbol clienteNuevo;
			strcpy(clienteNuevo.idCliente, idCliente);
			strcpy(clienteNuevo.nombre, nombre);
			clienteNuevo.genero=genero;
			clienteNuevo.idCiudad=idCiudad;

			BTreeNode* nodo = tree.busqueda(idCliente);
			KeyChar llave;
			if(nodo != NULL){
				for (int i = 0; i < nodo->tamano; ++i) {
					if( strncmp(nodo->llavesChar[i].llave, idCliente, 14) == 0 )
						llave.RRN = nodo->llavesChar[i].RRN;
				}
				strcpy(llave.llave, idCliente);
				bool borrar = tree.Remove(llave);
				tree.inorder(nombre_archivo);
				if(borrar){
					strcpy(llave.llave, idClienteNUEVO);
					bool continuarGuardando = tree.insert(llave);
					if(continuarGuardando){							

						int rrn = llave.RRN;
						int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(ClienteArbol) * rrn) );

						file.seekp(0);
						file.seekp(ecuacion);
						file.write(reinterpret_cast<char*>(&clienteNuevo), sizeof(ClienteArbol));
						file.seekp (0, file.beg);
					} else
						cout << "El numero del cliente ya existe" << endl;
				}
			} else
				cout << "El numero no fue encotrado" << endl;
		}
		break;
		case 3:{
			cout << "\tListar las Cliente" << endl << endl;

			int opcionListar;
			cout << "1)Sin Borrados\n2)Con Borrados" << endl << endl;
			cin >> opcionListar;//11416   //499
			switch(opcionListar){
				case 1:{
					ClienteArbol cliente;
					int rrn;
					for (int i = 0; i < sizeRegistros ; ++i){
						//rrn = indice.at(i, linea).RRN_index;
						//int ecuacion = ( sizeof(HeaderArbol) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(LineaxClienteArbol) * rrn) );
						file.seekg(0);
						//file.seekg(ecuacion);
						file.read(reinterpret_cast<char*>(&cliente), sizeof(ClienteArbol));
						cout << cliente;
					}
				}
				break;
				case 2:{
					ClienteArbol cliente;
					while(file.read(reinterpret_cast<char*>(&cliente), sizeof(ClienteArbol))){
						cout << cliente;
					}
				}
				break;
			}
			
		}
		break;
		case 4:{
			cout << "\tEliminar un Cliente" << endl;

			char nombre[40];
			char idCliente[14];
			char genero;
			cout << "Ingrese el id de la persona a eliminar: " << endl;
			cin >> idCliente;
			ClienteArbol clienteNuevo;
			strcpy(clienteNuevo.idCliente, idCliente);
			strcpy(clienteNuevo.nombre, "NOM");
			clienteNuevo.genero='M';
			clienteNuevo.idCiudad=4;
			//IndiceLineas ind = indice.get(lineaNueva);
			char*  busqueda= idCliente;

			BTreeNode* nodo = tree.busqueda(busqueda);
			KeyChar llave;
			if(nodo != NULL){
				for (int i = 0; i < nodo->tamano; ++i) {
					if(strncmp(nodo->llavesChar[i].llave, idCliente, 14) == 0)
						llave.RRN = nodo->llavesChar[i].RRN;
				}
				strcpy(llave.llave, clienteNuevo.idCliente);

				bool borrar = tree.Remove(llave);
				tree.inorder(nombre_archivo);

				if (borrar){
					int rrn = llave.RRN;
					int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(ClienteArbol) * rrn) );
					file.seekp(0);
					file.seekp(ecuacion);
					ClienteArbol clienteViejo;
					stringstream ss;
					ss<<"-1"<<availList;

					string s = ss.str();
					char const *pchar = s.c_str();
					strcpy(clienteViejo.idCliente, pchar);


					file.write(reinterpret_cast<char*>(&clienteViejo), sizeof(ClienteArbol));
					sizeRegistros--;
					head.sizeRegistro = sizeRegistros;
					availList =  llave.RRN;
					head.availList = availList;
					file.seekp (0, file.beg);
					file.write(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
					cout << "Borro con exito." << endl;
				}
			} else
				cout << "El id no fue encotrado" << endl;
		}
		break;
		case 5:{
			int opcionBuscar;
			cout << "1)Sin indice\n2)Con indice" << endl;
			cin >> opcionBuscar;
			switch(opcionBuscar){
				case 1:{
					char idCliente[14];
					cout << "Ingrese el id del Cliente que desea encontrar: " << endl;
					cin >> idCliente;
					ClienteArbol cliente;
					file.seekg(0, file.beg);
					file.read(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
					bool encontro = false;
					while(file.read(reinterpret_cast<char*>(&cliente), sizeof(ClienteArbol))){
						if(strncmp (idCliente, cliente.idCliente, 14) == 0 ){
							encontro = true;
							break;
						}
					}
					if(encontro)
						cout << "Busqueda realizada con exito.\nEl cliente que busca es: " << cliente ; 
					else
						cout << "El cliente no existe en la base de datos." << endl;
				}
				break;
				case 2:{
					char idCliente[14];
					cout << "Ingrese el id del cliente que desea encontrar: " << endl;
					cin >> idCliente;
					ClienteArbol cliente;
					strcpy(cliente.idCliente, idCliente);
					strcpy(cliente.nombre, "NOM");
					cliente.genero='M';
					cliente.idCiudad=4;

					file.seekg(0, file.beg);
					file.read(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
					BTreeNode* nodo = tree.busqueda(idCliente);
					KeyChar llave;
					if(nodo != NULL){
						for (int i = 0; i < nodo->tamano; ++i) {
							if( strncmp(nodo->llavesChar[i].llave, idCliente, 14) == 0 )
								llave.RRN = nodo->llavesChar[i].RRN;
						}
						int rrn = llave.RRN;
						int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(ClienteArbol) * rrn) );
						file.seekg(0);
						file.seekg(ecuacion);
						file.read(reinterpret_cast<char*>(&cliente), sizeof(ClienteArbol));
						cout << "Busqueda realizada con exito.\nEl cliente que busca es: " << cliente; 
					
					} else
						cout << "El cliente no existe en la base de datos." << endl;
				}
				break;
			}
		}
		break;
		case 6:{
			char nombre_archivo[14];
			strncpy(nombre_archivo,"indexCliente.bin",14);
			cout << "\tReindexar" << endl;
			tree.create(nombre_archivo);
			cout << "Reindexado con exito." << endl;
		}
		break;
		default:{
			cout << "Error." << endl;
		}
		break;
	}
	file.close();
}