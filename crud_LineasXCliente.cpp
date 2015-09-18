#include "index.h"
<<<<<<< HEAD
#include "crud_lineasxcliente.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>		
#include <string>		
#include <sstream>
=======
#include <iostream>
#include <stdlib.h>
#include <fstream>
>>>>>>> IndiceFinal

using namespace std;

ostream& operator<<(ostream& output, const LineaxCliente& linea){
<<<<<<< HEAD
	output << "IDCLIENTE = " << linea.idCliente << "\tNUMERO = " << linea.numero << endl;
=======
	output << linea.idCliente << "\t" << linea.numero << endl;
>>>>>>> IndiceFinal
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

<<<<<<< HEAD
crud_lineasxcliente::crud_lineasxcliente(){

}

void crud_lineasxcliente::correr(){

	char nombre_archivo[14];
	strncpy(nombre_archivo,"indexLineasXCliente.bin",14);
	fstream file("lineaxclientes.bin", fstream::binary);
	file.open("lineaxclientes.bin");
	//ofstream fileSalida("ciudades.bin", ofstream::binary);
	Index indice(nombre_archivo);
=======
int elementoBorrado(int);

int main(int argc, char const *argv[]){

	//Index indice("indexCiudades.bin");
	fstream file("LineaxCliente.bin", fstream::binary);
	file.open("LineaxCliente.bin");
	//ofstream fileSalida("ciudades.bin", ofstream::binary);
	Index indice("indexLineasXCliente.bin");
>>>>>>> IndiceFinal

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
<<<<<<< HEAD
			cout << "Ingrese el numero de la linea telefonica: " << endl;
=======
			cout << "Ingrese el numero de la linea: " << endl;
>>>>>>> IndiceFinal
			cin >> numero;
			cout << "Ingrese el numero de cliente de la linea: " << endl;
			cin >> idCliente;
			LineaxCliente lineaNueva;
			strcpy(lineaNueva.numero, numero);
			strcpy(lineaNueva.idCliente, idCliente);
<<<<<<< HEAD

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
					availList = atoi(linea.numero);
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
=======
			indice.add(lineaNueva, sizeRegistros /*+ elementoBorrado(sizeRegistros)*/);
			//cout << "Pos 1 = " << file.tellp() << endl;
			if (availList == -1)
				file.seekp (0, file.end);
			else{
				LineaxCliente linea;
				//int rrn = indice.ciudadRRN(availList, city).RRN_index;
				//cout << "Avail = " << availList << "\tRRN = " << rrn << endl;
				int ecuacion = ( sizeof(Header) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(Ciudad) * availList) );
				file.seekg(0);
				file.seekg(ecuacion);
				file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxCliente));
				availList = atoi(linea.numero);
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
		break;
		case 2:{
			cout << "\tModificar una Ciudad" << endl;
>>>>>>> IndiceFinal

			char numero[9];
			char numeroNUEVO[9];
			char idCliente[14];
<<<<<<< HEAD
			cout << "Ingrese el numero de la linea telefonica a modificar: " << endl;
			cin >> numero;
			cout << "Ingrese el NUEVO numero de la linea telefonica: " << endl;
=======
			cout << "Ingrese el numero de la linea a modificar: " << endl;
			cin >> numero;
			cout << "Ingrese el NUEVO numero de la linea: " << endl;
>>>>>>> IndiceFinal
			cin >> numeroNUEVO;
			cout << "Ingrese el NUEVO numeroCliente de la linea: " << endl;
			cin >> idCliente;

			LineaxCliente lineaNueva;
			strcpy(lineaNueva.numero, numeroNUEVO);
			strcpy(lineaNueva.idCliente, idCliente);

			LineaxCliente lineaVieja;
			strcpy(lineaVieja.numero, numero);
			strcpy(lineaVieja.idCliente, "NOM");
<<<<<<< HEAD
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
=======
			IndiceClien ind = indice.get(lineaVieja);
			int meter = indice.lineaRRN(ind.RRN_index, lineaVieja).RRN_index;
			indice.remove(lineaVieja);
			int rrn = ind.RRN_index;
			int ecuacion = ( sizeof(Header) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(Ciudad) * rrn) );
			indice.add(lineaNueva, meter);

			file.seekp(0);
			file.seekp(ecuacion);
			file.write(reinterpret_cast<char*>(&lineaNueva), sizeof(LineaxCliente));
>>>>>>> IndiceFinal

		}
		break;
		case 3:{
			cout << "\tListar las LineaxCliente" << endl << endl;

			int opcionListar;
			cout << "1)Sin Borrados\n2)Con Borrados" << endl << endl;
<<<<<<< HEAD
			cin >> opcionListar;//11416   //499
=======
			cin >> opcionListar;
>>>>>>> IndiceFinal
			switch(opcionListar){
				case 1:{
					LineaxCliente linea;
					int rrn;
<<<<<<< HEAD
					for (int i = 0; i < sizeRegistros ; ++i){
						rrn = indice.at(i, linea).RRN_index;
						int ecuacion = ( sizeof(Header) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(LineaxCliente) * rrn) );
						//cout << "Ecuacion = " << ecuacion << "\tRRN = " << rrn;
=======
					cout << "sizeRegistros= " << sizeRegistros << endl;
					for (int i = 0; i < sizeRegistros ; ++i){
						rrn = indice.at(i, linea).RRN_index;
						int ecuacion = ( sizeof(Header) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(LineaxCliente) * rrn) );
						//cout << "Ecuacion = " << ecuacion << "\tRRN = " << rrn << endl;
>>>>>>> IndiceFinal
						file.seekg(0);
						file.seekg(ecuacion);
						file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxCliente));
						cout << linea;
					}
				}
				break;
				case 2:{
					LineaxCliente linea;
<<<<<<< HEAD
					int cont = 0;
					while(file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxCliente))){
						cout << cont << ": " << linea;
						cont++;
=======
					while(file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxCliente))){
						cout << linea;
>>>>>>> IndiceFinal
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
<<<<<<< HEAD
			cout << "Ingrese el numero de la linea telefonica a eliminar: " << endl;
=======
			cout << "Ingrese el numero de la linea a eliminar: " << endl;
>>>>>>> IndiceFinal
			cin >> numero;
			LineaxCliente lineaNueva;
			strcpy(lineaNueva.numero, numero);
			strcpy(lineaNueva.idCliente, "NOM");
<<<<<<< HEAD
			IndiceLineas ind = indice.get(lineaNueva);
			cout << "RRN borrar = " << ind.RRN_index << endl;
			//availList =  ind.RRN_index;
			bool borrar = indice.remove(lineaNueva);
			if (borrar){
				cout << "Entro = " << lineaNueva.numero << endl;
				int rrn = ind.RRN_index;
				int ecuacion = ( sizeof(Header) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(LineaxCliente) * rrn) );
				file.seekp(0);
				file.seekp(ecuacion);
				cout << "Ecuacion = " << ecuacion << endl;
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
=======
			IndiceClien ind = indice.get(lineaNueva);
			//availList =  ind.RRN_index;
			indice.remove(lineaNueva);
			int rrn = ind.RRN_index;
			int ecuacion = ( sizeof(Header) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(Ciudad) * rrn) );
			file.seekp(0);
			file.seekp(ecuacion);
			LineaxCliente lineaVieja;

			string s = to_string(-99);
			char const *pchar = s.c_str();
			strcpy(lineaVieja.numero, pchar);

			file.write(reinterpret_cast<char*>(&lineaVieja), sizeof(LineaxCliente));
			sizeRegistros--;
			head.sizeRegistro = sizeRegistros - 1;
			availList =  ind.RRN_index;
			head.availList = availList;
			file.seekp (0, file.beg);
			file.write(reinterpret_cast<char*>(&head), sizeof(Header));
>>>>>>> IndiceFinal
		}
		break;
		case 5:{
			int opcionBuscar;
			cout << "1)Sin indice\n2)Con indice" << endl;
			cin >> opcionBuscar;
			switch(opcionBuscar){
				case 1:{
					char numero[9];
<<<<<<< HEAD
					cout << "Ingrese el numero de la linea telefonica que desea encontrar: " << endl;
=======
					cout << "Ingrese el ID de la Ciudad que desea encontrar: " << endl;
>>>>>>> IndiceFinal
					cin >> numero;
					LineaxCliente linea;
					file.seekg(0, file.beg);
					file.read(reinterpret_cast<char*>(&head), sizeof(Header));
					bool encontro = false;
					while(file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxCliente))){
<<<<<<< HEAD
						if(strncmp (numero, linea.numero, 9) == 0 ){
=======
						if(numero == linea.numero){
>>>>>>> IndiceFinal
							encontro = true;
							break;
						}
					}
					if(encontro)
<<<<<<< HEAD
						cout << "Busqueda realizada con exito.\nLa linea telefonica que busca es: " << linea ; 
					else
						cout << "La linea telefonica no existe en la base de datos." << endl;
=======
						cout << "Busqueda realizada con exito.\nLa ciudad que busca es: " << linea;
					else
						cout << "La ciudad no existe en la base de datos." << endl;
>>>>>>> IndiceFinal
				}
				break;
				case 2:{
					char numero[9];
<<<<<<< HEAD
					cout << "Ingrese el numero de la linea que desea encontrar: " << endl;
=======
					cout << "Ingrese el ID de la Ciudad que desea encontrar: " << endl;
>>>>>>> IndiceFinal
					cin >> numero;
					LineaxCliente linea;
					strcpy(linea.numero, numero);
					strcpy(linea.idCliente, "NOM");
<<<<<<< HEAD
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
=======
					IndiceClien ind = indice.get(linea);
					int rrn = ind.RRN_index;
					if(rrn != -99){
						int ecuacion = ( sizeof(Header) + /*( elementoBorrado(rrn) * sizeof(Ciudad) ) + */( sizeof(Ciudad) * rrn) );
						file.seekg(0);
						file.seekg(ecuacion);
						file.read(reinterpret_cast<char*>(&linea), sizeof(LineaxCliente));
						cout << "Busqueda realizada con exito.\nLa ciudad que busca es: " << linea;
					} else
						cout << "La ciudad no existe en la base de datos." << endl;
>>>>>>> IndiceFinal
				}
				break;
			}
		}
		break;
		case 6:{
<<<<<<< HEAD
			char nombre_archivo[14];
			strncpy(nombre_archivo,"indexLineasXCliente.bin",14);
			cout << "\tReindexar" << endl;
			indice.create(nombre_archivo);
=======
			cout << "\tReindexar" << endl;
			indice.create("indexLineaxCliente.bin");
>>>>>>> IndiceFinal
			cout << "Reindexado con exito." << endl;
		}
		break;
		default:{
			cout << "Error." << endl;
		}
		break;
	}
	file.close();
<<<<<<< HEAD
=======
	return 0;
}

int elementoBorrado(int RRN){
	int borrados = 0;
	int azterizco = -99;
	//char azterizco[1];
	//azterizco[0] = '*';
	Ciudad city;
	int cont = 0;
	ifstream file("LineaxCliente.bin", ifstream::binary);
	file.seekg(8);
	while(file.read(reinterpret_cast<char*>(&city), sizeof(Ciudad))){
		if(city.idCiudad == azterizco && cont < RRN)
			borrados++;
		cont++;
	}
	file.close();
	return borrados;
>>>>>>> IndiceFinal
}