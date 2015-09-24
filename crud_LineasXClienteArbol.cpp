#include "b-tree.h"
#include "crud_LineasXClienteArbol.h"
#include "b-treenode.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>		
#include <string>		
#include <sstream>

using namespace std;

ostream& operator<<(ostream& output, const LineaxClienteArbol& linea){
	output << "IDCLIENTE = " << linea.idCliente << "\tNUMERO = " << linea.numero << endl;
	return output;  
}
istream& operator>>(istream& input, LineaxClienteArbol& linea){
	 input >> linea.idCliente >> linea.numero;
	 return input;
}

crud_lineasxclienteArbol::crud_lineasxclienteArbol(){

}

void crud_lineasxclienteArbol::correr(){

	char nombre_archivo[25];
	strncpy(nombre_archivo,"indexLineasXCliente.bin",25);
 
	fstream file("lineaxclientes.bin", fstream::binary);
	file.open("lineaxclientes.bin");

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
			cout << "\tAgregar una LineaxCliente" << endl;

			char numero[9];
			char idCliente[14];
			cout << "Ingrese el numero de la linea telefonica: " << endl;
			cin >> numero;
			cout << "Ingrese el numero de cliente de la linea: " << endl;
			cin >> idCliente;
			LineaxClienteArbol lineaNueva;
			strcpy(lineaNueva.numero, numero);
			strcpy(lineaNueva.idCliente, idCliente);

			KeyChar llave;

			strcpy(llave.llave, lineaNueva.numero);
			bool continuarGuardando;
			if (availList == -1)
				llave.RRN = sizeRegistros;
			else
				llave.RRN = availList;
			continuarGuardando = tree.insert(llave);
			if (continuarGuardando){																
				if (availList == -1)
					file.seekp (0, file.end);
				else{
					LineaxClienteArbol linea;
					int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(LineaxClienteArbol) * availList) );	
					file.seekg(0);
					file.seekg(ecuacion);
					file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxClienteArbol));
					availList = atoi(linea.idCliente);
					head.availList = availList;

					file.seekp(0);
					file.seekp(ecuacion);
				}
				file.write(reinterpret_cast<char*>(&lineaNueva), sizeof(LineaxClienteArbol));
				file.seekp (0, file.beg);
				sizeRegistros++;
				head.sizeRegistro = head.sizeRegistro + 1;
				file.write(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
			}
		}
		break;
		case 2:{
			cout << "\tModificar una Linea" << endl;

			char numero[9];
			char numeroNUEVO[9];
			char idCliente[14];
			cout << "Ingrese el numero de la linea telefonica a modificar: " << endl;
			cin >> numero;
			cout << "Ingrese el NUEVO numero de la linea telefonica: " << endl;
			cin >> numeroNUEVO;
			cout << "Ingrese el NUEVO numeroCliente de la linea: " << endl;
			cin >> idCliente;

			LineaxClienteArbol lineaNueva;
			strcpy(lineaNueva.numero, numeroNUEVO);
			strcpy(lineaNueva.idCliente, idCliente);

			BTreeNode* nodo = tree.busqueda(numero);
			KeyChar llave;
			if(nodo != NULL){
				for (int i = 0; i < nodo->tamano; ++i) {
					if( strncmp(nodo->llavesChar[i].llave, numero, 14) == 0 )
						llave.RRN = nodo->llavesChar[i].RRN;
				}
				strcpy(llave.llave, numero);
				bool borrar = tree.Remove(llave);
				tree.inorder(nombre_archivo);
				if(borrar){
					strcpy(llave.llave, numeroNUEVO);
					bool continuarGuardando = tree.insert(llave);
					if(continuarGuardando){							

						int rrn = llave.RRN;
						int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(LineaxClienteArbol) * rrn) );

						file.seekp(0);
						file.seekp(ecuacion);
						file.write(reinterpret_cast<char*>(&lineaNueva), sizeof(LineaxClienteArbol));
						file.seekp (0, file.beg);
					} else
						cout << "El numero del cliente ya existe" << endl;
				}
			} else
				cout << "El numero no fue encotrado" << endl;
		}
		break;
		case 3:{
			cout << "\tListar las LineaxCliente" << endl << endl;

			int opcionListar;
			cout << "1)Sin Borrados\n2)Con Borrados" << endl << endl;
			cin >> opcionListar;//11416   //499
			switch(opcionListar){
				case 1:{
					LineaxClienteArbol linea;
					int rrn;
					for (int i = 0; i < sizeRegistros ; ++i){
						//rrn = indice.at(i, linea).RRN_index;
						//int ecuacion = ( sizeof(HeaderArbol) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(LineaxClienteArbol) * rrn) );
						file.seekg(0);
						//file.seekg(ecuacion);
						file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxClienteArbol));
						cout << linea;
					}
				}
				break;
				case 2:{
					LineaxClienteArbol linea;
					while(file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxClienteArbol))){
						cout << linea;
					}
				}
				break;
			}
			
		}
		break;
		case 4:{
			cout << "\tEliminar una LineaxCliente" << endl;

			char numero[9];
			char idCliente[14];
			cout << "Ingrese el numero de la linea telefonica a eliminar: " << endl;
			cin >> numero;
			LineaxClienteArbol lineaNueva;
			strcpy(lineaNueva.numero, numero);
			strcpy(lineaNueva.idCliente, "NOM");
			//IndiceLineas ind = indice.get(lineaNueva);
			char* num1 = numero;

			BTreeNode* nodo = tree.busqueda(num1);
			KeyChar llave;
			if(nodo != NULL){
				for (int i = 0; i < nodo->tamano; ++i) {
					if(strncmp(nodo->llavesChar[i].llave, numero, 14) == 0)
						llave.RRN = nodo->llavesChar[i].RRN;
				}
				strcpy(llave.llave, lineaNueva.numero);

				bool borrar = tree.Remove(llave);
				tree.inorder(nombre_archivo);

				if (borrar){
					int rrn = llave.RRN;
					int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(LineaxClienteArbol) * rrn) );
					file.seekp(0);
					file.seekp(ecuacion);
					LineaxClienteArbol lineaVieja;

					strcpy(lineaVieja.numero, "-99");
					stringstream ss;
					ss<<availList;

					string s = ss.str();
					char const *pchar = s.c_str();
					strcpy(lineaVieja.idCliente, pchar);


					file.write(reinterpret_cast<char*>(&lineaVieja), sizeof(LineaxClienteArbol));
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
					char numero[9];
					cout << "Ingrese el numero de la linea telefonica que desea encontrar: " << endl;
					cin >> numero;
					LineaxClienteArbol linea;
					file.seekg(0, file.beg);
					file.read(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
					bool encontro = false;
					while(file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxClienteArbol))){
						if(strncmp (numero, linea.numero, 9) == 0 ){
							encontro = true;
							break;
						}
					}
					if(encontro)
						cout << "Busqueda realizada con exito.\nLa linea telefonica que busca es: " << linea ; 
					else
						cout << "La linea telefonica no existe en la base de datos." << endl;
				}
				break;
				case 2:{
					char numero[9];
					cout << "Ingrese el numero de la linea que desea encontrar: " << endl;
					cin >> numero;
					LineaxClienteArbol linea;
					strcpy(linea.numero, numero);
					strcpy(linea.idCliente, "NOM");

					file.seekg(0, file.beg);
					file.read(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
					BTreeNode* nodo = tree.busqueda(numero);
					KeyChar llave;
					if(nodo != NULL){
						for (int i = 0; i < nodo->tamano; ++i) {
							if( strncmp(nodo->llavesChar[i].llave, numero, 14) == 0 )
								llave.RRN = nodo->llavesChar[i].RRN;
						}
						int rrn = llave.RRN;
						int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(LineaxClienteArbol) * rrn) );
						file.seekg(0);
						file.seekg(ecuacion);
						file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxClienteArbol));
						cout << "Busqueda realizada con exito.\nLa linea telefonica que busca es: " << linea; 
					
					} else
						cout << "La linea telefonica no existe en la base de datos." << endl;
				}
				break;
			}
		}
		break;
		case 6:{
			char nombre_archivo[25];
			strncpy(nombre_archivo,"indexLineasXCliente.bin",25);
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