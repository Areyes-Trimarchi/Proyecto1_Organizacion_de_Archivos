#include "b-tree.h"
#include "crud_CiudadesArbol.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>		
#include <string>		
#include <sstream>

using namespace std;

ostream& operator<<(ostream& output, const CiudadArbol& city){
	output << "IDCIUDAD = " << city.idCiudad << "\tNOMBRE = " << city.name << endl;
	return output;  
}
istream& operator>>(istream& input, CiudadArbol& city){
	 input >> city.idCiudad >> city.name;
	 return input;
}
/*ostream& operator<<(ostream& output, const Indice& city){
	output << city.id_ciu_index << "\t" << city.RRN_index << endl;
	return output;  
}*/


crud_ciudadesArbol::crud_ciudadesArbol(){

}

void crud_ciudadesArbol::correr(){

	char nombre_archivo[25];
	strncpy(nombre_archivo,"indexCiudades.bin",25);
	fstream file("ciudades.bin", fstream::binary);
	file.open("ciudades.bin");

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
			cout << "\tAgregar una Ciudad" << endl;

			int ID;
			char NOM[40];
			cout << "Ingrese el id de la ciudad: " << endl;
			cin >> ID;
			cout << "Ingrese el nombre de la ciudad: " << endl;
			cin >> NOM;
			CiudadArbol ciudadNueva;
			ciudadNueva.idCiudad = ID;
			strcpy(ciudadNueva.name, NOM);

			Key llave;
			llave.llave = ciudadNueva.idCiudad;
			llave.RRN = sizeRegistros;
			bool continuarGuardando = tree.insert(llave);
			if(continuarGuardando){								
				if (availList == -1)
					file.seekp (0, file.end);
				else{
					CiudadArbol city;
					int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(CiudadArbol) * availList) );	
					file.seekg(0);
					file.seekg(ecuacion);
					file.read(reinterpret_cast<char*>(&city), sizeof(CiudadArbol));
					availList = atoi(city.name);
					head.availList = availList;

					file.seekp(0);
					file.seekp(ecuacion);
				}
				file.write(reinterpret_cast<char*>(&ciudadNueva), sizeof(CiudadArbol));
				file.seekp (0, file.beg);
				sizeRegistros++;
				head.sizeRegistro = head.sizeRegistro + 1;
				file.write(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
			}
			tree.inorder(nombre_archivo);
		}
		break;
		case 2:{
			cout << "\tModificar una Ciudad" << endl;

			int ID;
			int IDNUEVO;
			char NOM[40];
			cout << "Ingrese el id de la ciudad a modificar: " << endl;
			cin >> ID;
			cout << "Ingrese el NUEVO id de la ciudad: " << endl;
			cin >> IDNUEVO;
			cout << "Ingrese el NUEVO nombre de la ciudad: " << endl;
			cin >> NOM;

			CiudadArbol ciudadNueva;
			ciudadNueva.idCiudad = IDNUEVO;
			strcpy(ciudadNueva.name, NOM);

			CiudadArbol ciudadVieja;
			ciudadVieja.idCiudad = ID;
			strcpy(ciudadVieja.name, "NOM");

			BTreeNode* nodo = tree.busqueda(ID);
			Key llave;
			if(nodo != NULL){
				for (int i = 0; i < nodo->tamano; ++i) {
					if(nodo->llaves[i].llave == ID)
						llave.RRN = nodo->llaves[i].RRN;
				}
				llave.llave = ID;
				bool borrar = tree.Remove(llave);
				tree.inorder(nombre_archivo);
				if(borrar){
					llave.llave = IDNUEVO; 
					bool continuarGuardando = tree.insert(llave);
					if(continuarGuardando){							

						int rrn = llave.RRN;
						int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(CiudadArbol) * rrn) );

						file.seekp(0);
						file.seekp(ecuacion);
						file.write(reinterpret_cast<char*>(&ciudadNueva), sizeof(CiudadArbol));
						file.seekp (0, file.beg);
					} else
						cout << "El id ya existe" << endl;
				}
			} else
				cout << "El id no fue encotrado" << endl;
		}
		break;
		case 3:{
			cout << "\tListar las Ciudades" << endl << endl;

			int opcionListar;
			cout << "1)Sin Borrados\n2)Con Borrados" << endl << endl;
			cin >> opcionListar;
			//indice.create("indexCiudades.bin");		<-----------
			switch(opcionListar){
				case 1:{
					CiudadArbol city;
					int rrn;
					for (int i = 0; i < sizeRegistros ; ++i){
						//rrn = indice.at(i, city).RRN_index;
						int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(CiudadArbol) * rrn) );	
						file.seekg(0);
						file.seekg(ecuacion);
						file.read(reinterpret_cast<char*>(&city), sizeof(CiudadArbol));
						cout << city;
					}
				}
				break;
				case 2:{
					CiudadArbol city;
					while(file.read(reinterpret_cast<char*>(&city), sizeof(CiudadArbol))){
						cout << city;
					}
				}
				break;
			}
			
		}
		break;
		case 4:{
			cout << "\tEliminar una Ciudad" << endl;

			int ID;
			cout << "Ingrese el id de la ciudad a eliminar: " << endl;
			cin >> ID;
			CiudadArbol ciudadNueva;
			ciudadNueva.idCiudad = ID;
			strcpy(ciudadNueva.name, "NOM");
			
			BTreeNode* nodo = tree.busqueda(ID);
			Key llave;
			if(nodo != NULL){
				for (int i = 0; i < nodo->tamano; ++i) {
					if(nodo->llaves[i].llave == ID)
						llave.RRN = nodo->llaves[i].RRN;
				}
				llave.llave = ID;
				bool borrar = tree.Remove(llave);
				tree.inorder(nombre_archivo);
				if(borrar){
					int rrn = llave.RRN;
					int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(CiudadArbol) * rrn) );		
					file.seekp(0);
					file.seekp(ecuacion);
					CiudadArbol borrada;

					borrada.idCiudad = -99;
					stringstream ss;
					ss << availList;
					string s = ss.str();
					char const *pchar = s.c_str();
					strcpy(borrada.name, pchar);

					file.write(reinterpret_cast<char*>(&borrada), sizeof(CiudadArbol));
					sizeRegistros--;
					head.sizeRegistro = head.sizeRegistro - 1;
					availList =  llave.RRN;
					head.availList = availList;
					file.seekp (0, file.beg);
					file.seekp (0);
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
					int idBuscar;
					cout << "Ingrese el ID de la Ciudad que desea encontrar: " << endl;
					cin >> idBuscar;
					CiudadArbol city;
					file.seekg(0, file.beg);
					file.read(reinterpret_cast<char*>(&head), sizeof(HeaderArbol));
					bool encontro = false;
					while(file.read(reinterpret_cast<char*>(&city), sizeof(CiudadArbol))){
						if(idBuscar == city.idCiudad){
							encontro = true;
							break;
						}
					}
					if(encontro)
						cout << "Busqueda realizada con exito.\nLa ciudad que busca es: ";// << city;
					else
						cout << "La ciudad no existe en la base de datos." << endl;
				}
				break;
				case 2:{
					int idBuscar;
					cout << "Ingrese el ID de la Ciudad que desea encontrar: " << endl;
					cin >> idBuscar;
					CiudadArbol city;
					city.idCiudad = idBuscar;
					strcpy(city.name, "NOM");

					BTreeNode* nodo = tree.busqueda(idBuscar);
					Key llave;
					if(nodo != NULL){
						for (int i = 0; i < nodo->tamano; ++i) {
							if(nodo->llaves[i].llave == idBuscar)
								llave.RRN = nodo->llaves[i].RRN;
						}
						int rrn = llave.RRN;

					
						int ecuacion = ( sizeof(HeaderArbol) + ( sizeof(CiudadArbol) * rrn) );	
						file.seekg(0);
						file.seekg(ecuacion);
						file.read(reinterpret_cast<char*>(&city), sizeof(CiudadArbol));
						cout << "Busqueda realizada con exito.\nLa ciudad que busca es: " << city;
					} else
						cout << "La ciudad no existe en la base de datos." << endl;
				}
				break;
			}
		}
		break;
		case 6:{
			char nombre_archivo[25];
			strncpy(nombre_archivo,"indexCiudades.bin",25);
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