#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>  
#include <string> 
using namespace std;

int menu();

struct llamada{
	int numero;
	string inicio;
	string final;
	string destino;
};

ostream& operator<<(ostream& output, const llamada& llamada){
	output << llamada.numero << "\t" << llamada.inicio << "\t" << llamada.final << "\t" << llamada.destino << endl;
	return output;  
}
istream& operator>>(istream& input, llamada& llamada){
	 input >> llamada.numero >> llamada.inicio >> llamada.final >> llamada.destino;
	 return input;
}

int main(int argc, char const *argv[]){
	int opcionMenu;
	
	vector<llamada> llamadas;
	string cont;
	do{
		cout << "MENU\n1)Leer Numeros\n2)Guardar Informacion\n3)Cargar Datos" << endl;
		cin >> opcionMenu;
		switch(opcionMenu){
			case 1:{
				llamada call;
				ifstream file("data.bin", ifstream::binary);
				int cont = 0 ;
				while(file.read(reinterpret_cast<char*>(&call), sizeof(call))){
					cout << call << endl;
					cout << cont << endl;
					cont++;
				}
			}
			break;
			case 2:{
				ofstream file("data.bin", ofstream::binary);
				int cont = 0 ;
				for (int i = 0; i < llamadas.size(); ++i){
					file.write(reinterpret_cast<const char*> (&llamadas.at(i)), sizeof(llamadas.at(i)));
					cout << "Funciones +++++++" << cont << endl;
					cont++;
				}
				cout << "Exito en la operacion" << endl;
				file.close();
			}
			break;
			case 3:{
				string line;

				vector<string> inicio;
				vector<string> final;
				vector<string> numeros;
				vector<string> ciudades;
				string NOMinicio;
				string NOMfinal;
				string NOMnumeros;
				string NOMciudades;
				cout << "Ingrese el nombre del archivo de llamads de inicio: " << endl;
				cin >> NOMinicio;
				cout << "Ingrese el nombre del archivo de llamads final: " << endl;
				cin >> NOMfinal;
				cout << "Ingrese el nombre del archivo de numeros telefonicos: " << endl;
				cin >> NOMnumeros;
				cout << "Ingrese el nombre del archivo de ciudades: " << endl;
				cin >> NOMciudades;
				ifstream numerosFILE;
				ifstream ciudadesFILE;

				llamada call;
				
				ifstream fileINICIO (NOMinicio);
				int pos = 0;
				if (fileINICIO.is_open()){
					while ( getline (fileINICIO,line) ){
						llamadas.push_back(call);
						cout << line << '\n';
						inicio.push_back(line);
						llamadas.at(pos).inicio = line;
						pos++;
				    }
				    fileINICIO.close();
				}

				pos = 0;
				ifstream fileFINAL (NOMfinal);
				if (fileFINAL.is_open()){
					while ( getline (fileFINAL,line) ){
						cout << line << '\n';
						final.push_back(line);
						llamadas.at(pos).final = line;
						pos++;
				    }
				    fileFINAL.close();
				}
				
				pos = 0;
				ifstream fileNUMEROS (NOMnumeros);
				if (numerosFILE.is_open()){
					while ( getline (numerosFILE,line) ){
						cout << line << '\n';
						numeros.push_back(line);
						llamadas.at(pos).numero = stoi (line,nullptr,16);
						pos++;
				    }
				    fileNUMEROS.close();
				}
				
				pos = 0;
				ifstream fileCIUDADES (NOMciudades);
				if (fileCIUDADES.is_open()){
					while ( getline (fileCIUDADES,line) ){
						cout << line << '\n';
						ciudades.push_back(line);
						call.destino = line;
						llamadas.at(pos).destino = line;
						pos++;
				    }
				    fileCIUDADES.close();
				}

				
				
			}
			break;
			default: cout << "Opcion invalida" << endl;
					cout << "MENU\n1)Leer Numeros\n2)Guardar Informacion" << endl;
					cin << opcionMenu;
			break;
		}
		cout << "Desea continural? [si/no]" << endl;
		cin >> cont;
	}while(cont == "si");
	return 0;
}

int menu(){
	int menu;
	cout << "MENU\n1)Leer Numeros\n2)Guardar Informacion" << endl;
	cin << menu;
	while(menu != 1 && menu != 2 && menu != 3){
		cout << "MENU\n1)Leer Numeros\n2)Guardar Informacion\n3)Cargar Datos" << endl;
		cin << menu;
	}
	return menu;
}