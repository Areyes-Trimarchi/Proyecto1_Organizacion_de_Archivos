#include "index.h"
#include "crud_LineasXCliente.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>		
#include <string>		
#include <sstream>

using namespace std;

ostream& operator<<(ostream& output, const LineaxCliente& linea){
	output << "IDCLIENTE = " << linea.idCliente << "\tNUMERO = " << linea.numero << endl;
	return output;  
}
istream& operator>>(istream& input, LineaxCliente& linea){
	 input >> linea.idCliente >> linea.numero;
	 return input;
}
/*ostream& operator<<(ostream& output, const Indice& city){
	output << city.id_ciu_index << "\t" << city.RRN_index << endl;
	return output;  
}*/

/*
	struct LineaxCliente{
	char numero[9];
	char idCliente[14];
};
*/

crud_lineasxcliente::crud_lineasxcliente(){

}

void crud_lineasxcliente::correr(){

	char nombre_archivo[14];
	strncpy(nombre_archivo,"indexLineasXCliente.bin",14);
	//ofstream fileSalida("ciudades.bin", ofstream::binary);
	Index indice(nombre_archivo);
	fstream file("lineaxclientes.bin", fstream::binary);
	file.open("lineaxclientes.bin");

	Header head;
	file.seekg(0);
	file.read(reinterpret_cast<char*>(&head), sizeof(Header));
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
			LineaxCliente lineaNueva;
			strcpy(lineaNueva.numero, numero);
			strcpy(lineaNueva.idCliente, idCliente);

			bool continuarGuardando = indice.add(lineaNueva, sizeRegistros /*+ elementoBorrado(sizeRegistros)*/);
			//cout << "Pos 1 = " << file.tellp() << endl;
			if (continuarGuardando){																
				if (availList == -1)
					file.seekp (0, file.end);
				else{
					LineaxCliente linea;
					//int rrn = indice.ciudadRRN(availList, city).RRN_index;
					//cout << "Avail = " << availList << "\tRRN = " << rrn << endl;
					int ecuacion = ( sizeof(Header) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(LineaxCliente) * availList) );	
					file.seekg(0);
					file.seekg(ecuacion);
					file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxCliente));
					availList = atoi(linea.idCliente);
					head.availList = availList;

					file.seekp(0);
					file.seekp(ecuacion);
				}
				//cout << "Pos 2 = " << file.tellp() << endl;
				file.write(reinterpret_cast<char*>(&lineaNueva), sizeof(LineaxCliente));
				//cout << "Pos 3 = " << file.tellp() << endl;
				file.seekp (0, file.beg);
				//cout << "Pos 4 = " << file.tellp() << endl;
				sizeRegistros++;
				head.sizeRegistro = head.sizeRegistro + 1;
				file.write(reinterpret_cast<char*>(&head), sizeof(Header));
				//cout << "Pos 5 = " << file.tellp() << endl;
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

			LineaxCliente lineaNueva;
			strcpy(lineaNueva.numero, numeroNUEVO);
			strcpy(lineaNueva.idCliente, idCliente);

			LineaxCliente lineaVieja;
			strcpy(lineaVieja.numero, numero);
			strcpy(lineaVieja.idCliente, "NOM");
			IndiceLineas ind = indice.get(lineaVieja);
			bool borrar = indice.remove(lineaVieja);
			if(borrar){
				int meter = indice.lineaRRN(ind.RRN_index, lineaVieja).RRN_index;
				
				int rrn = ind.RRN_index;
				int ecuacion = ( sizeof(Header) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(LineaxCliente) * rrn) );
				indice.add(lineaNueva, meter);

				file.seekp(0);
				file.seekp(ecuacion);
				file.write(reinterpret_cast<char*>(&lineaNueva), sizeof(LineaxCliente));
			}

		}
		break;
		case 3:{
			cout << "\tListar las LineaxCliente" << endl << endl;

			int opcionListar;
			cout << "1)Sin Borrados\n2)Con Borrados" << endl << endl;
			cin >> opcionListar;//11416   //499
			switch(opcionListar){
				case 1:{
					LineaxCliente linea;
					int rrn;
					for (int i = 0; i < sizeRegistros ; ++i){
						rrn = indice.at(i, linea).RRN_index;
						int ecuacion = ( sizeof(Header) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(LineaxCliente) * rrn) );
						file.seekg(0);
						file.seekg(ecuacion);
						file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxCliente));
						cout << linea;
					}
				}
				break;
				case 2:{
					LineaxCliente linea;
					while(file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxCliente))){
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
			LineaxCliente lineaNueva;
			strcpy(lineaNueva.numero, numero);
			strcpy(lineaNueva.idCliente, "NOM");
			IndiceLineas ind = indice.get(lineaNueva);
			cout << "RRN borrar = " << ind.RRN_index << endl;
			//availList =  ind.RRN_index;
			bool borrar = indice.remove(lineaNueva);
			if (borrar){
				int rrn = ind.RRN_index;
				int ecuacion = ( sizeof(Header) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(LineaxCliente) * rrn) );
				file.seekp(0);
				file.seekp(ecuacion);
				LineaxCliente lineaVieja;

				strcpy(lineaVieja.numero, "-99");
				stringstream ss;
				ss<<availList;

				//strcpy(lineaVieja.numero, "-99");
				string s = ss.str();
				char const *pchar = s.c_str();
				strcpy(lineaVieja.idCliente, pchar);


				file.write(reinterpret_cast<char*>(&lineaVieja), sizeof(LineaxCliente));
				sizeRegistros--;
				head.sizeRegistro = sizeRegistros;
				availList =  ind.RRN_index;
				head.availList = availList;
				file.seekp (0, file.beg);
				file.write(reinterpret_cast<char*>(&head), sizeof(Header));
			}
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
					LineaxCliente linea;
					file.seekg(0, file.beg);
					file.read(reinterpret_cast<char*>(&head), sizeof(Header));
					bool encontro = false;
					while(file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxCliente))){
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
					LineaxCliente linea;
					strcpy(linea.numero, numero);
					strcpy(linea.idCliente, "NOM");
					IndiceLineas ind = indice.get(linea);
					int rrn = ind.RRN_index;
					file.seekg(0, file.beg);
					file.read(reinterpret_cast<char*>(&head), sizeof(Header));
					if(rrn != -99){
						int ecuacion = ( sizeof(Header) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(LineaxCliente) * rrn) );
						file.seekg(0);
						file.seekg(ecuacion);
						file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxCliente));
						cout << "Busqueda realizada con exito.\nLa linea telefonica que busca es: " << linea; 
					} else
						cout << "La linea telefonica no existe en la base de datos." << endl;
				}
				break;
			}
		}
		break;
		case 6:{
			char nombre_archivo[14];
			strncpy(nombre_archivo,"indexLineasXCliente.bin",14);
			cout << "\tReindexar" << endl;
			indice.create(nombre_archivo);
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