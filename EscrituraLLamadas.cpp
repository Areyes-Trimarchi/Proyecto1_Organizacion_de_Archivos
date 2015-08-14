#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>  
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
	cout << "MENU\n1)Leer Numeros\n2)Guardar Informacion" << endl;
	cin << opcionMenu;
	vector<llamada> llamadas;
	switch(opcionMenu){
		case 1:{

		}
		break;
		case 2:{
			ofstream file("data.bin", ofstream::binary);
			for (int i = 0; i < llamadas.size(); ++i){
				file.write(reinterpret_cast<const char*> (&llamadas.at(i)), sizeof(llamadas.at(i)));
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
			string NOMinicio;
			string NOMfinal;
			string NOMnumeros;
			cout << "Ingrese el nombre del archivo de llamads de inicio: " << endl;
			cin >> NOMinicio;
			cout << "Ingrese el nombre del archivo de llamads final: " << endl;
			cin >> NOMfinal;
			cout << "Ingrese el nombre del archivo de numeros telefonicos: " << endl;
			cin >> NOMnumeros;
			ifstream inicioFILE;
			ifstream finalFILE;
			ifstream numerosFILE;

			ifstream fileINICIO (NOMinicio);
			if (inicioFILE.is_open()){
				while ( getline (inicioFILE,line) ){
					cout << line << '\n';
					inicio.push_back(line);
			    }
			    fileINICIO.close();
			}

			ifstream fileFINAL (NOMfinal);
			if (finalFILE.is_open()){
				while ( getline (fileFINAL,line) ){
					cout << line << '\n';
					final.push_back(line);
			    }
			    fileFINAL.close();
			}
			
			ifstream fileNUMEROS (NOMnumeros);
			if (numerosFILE.is_open()){
				while ( getline (fileNUMEROS,line) ){
					cout << line << '\n';
					numeros.push_back(line);
			    }
			    fileNUMEROS.close();
			}
			
		}
		break;
		default: cout << "Opcion invalida" << endl;
				cout << "MENU\n1)Leer Numeros\n2)Guardar Informacion" << endl;
				cin << opcionMenu;
		break;
	}
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