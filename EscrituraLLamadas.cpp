#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <vector>  
#include <cstring> 
#include <string> 
using namespace std;

int menu();

struct llamada{
	char numero[9];
	string inicio;
	string final;
	char destino[9];
};

ostream& operator<<(ostream& output, const llamada& llamada){
	output << "Numero = " << llamada.numero << "\tInicio = " << llamada.inicio << "\tFinal = " << llamada.final << "\tDestino = " << llamada.destino << endl;
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
				ifstream file("llamadas.bin", ifstream::binary);
				while(file.read(reinterpret_cast<char*>(&call), sizeof(llamada))){
					cout << call << endl;
				}
				file.close();
			}
			break;
			case 2:{
				ofstream file("llamadas.bin", ofstream::binary);
				for (int i = 0; i < llamadas.size(); ++i){
					cout << "Numero = " << llamadas.at(i).numero << "\tInicio = " << llamadas.at(i).inicio << "\tFinal = " << llamadas.at(i).final << "\tDestino = " << llamadas.at(i).destino << endl;
					file.write(reinterpret_cast<const char*> (&llamadas.at(i)), sizeof(llamada));
				}
				cout << "Exito en la operacion" << endl;
				file.close();
			}
			break;
			case 3:{
				string line;

				vector<string> inicio;
				vector<string> final;
				vector<char*> numeros;
				vector<char*> destino;
				string NOMinicio;
				string NOMfinal;
				string NOMnumeros;
				char a1[25];
				char a2[25];
				char a3[25];
				cout << "Ingrese el nombre del archivo de llamads de inicio: " << endl;
				cin >> NOMinicio;
				cout << "Ingrese el nombre del archivo de llamads final: " << endl;
				cin >> NOMfinal;
				cout << "Ingrese el nombre del archivo de numeros telefonicos: " << endl;
				cin >> NOMnumeros;

				llamada call;
				
				strncpy(a1, NOMinicio.c_str(), 25);
				strncpy(a2, NOMfinal.c_str(), 25);
				strncpy(a3, NOMnumeros.c_str(), 25);
				ifstream fileINICIO (a1);
				int pos = 0;
				if (fileINICIO.is_open()){
					while ( getline (fileINICIO,line) ){
						llamadas.push_back(call);
						//cout << line << '\n';
						inicio.push_back(line);
						llamadas.at(pos).inicio = line;
						pos++;
				    }
				    fileINICIO.close();
				}

				pos = 0;
				ifstream fileFINAL (a2);
				if (fileFINAL.is_open()){
					while ( getline (fileFINAL,line) ){
						//cout << line << '\n';
						final.push_back(line);
						llamadas.at(pos).final = line;
						pos++;
				    }
				    fileFINAL.close();
				}
				
				pos = 0;
				ifstream fileNUMEROS (a3);
				if (fileNUMEROS.is_open()){
					while ( getline (fileNUMEROS,line) ){
						//cout << line << '\n';
						char num[9];
						strncpy(num, line.c_str(), 9);
						numeros.push_back(num);
						//llamadas.at(pos).numero = stoi (line,nullptr,16);
						//strncpy(llamadas.at(pos).numero, numeros.at(pos), 9);
						//cout << "LLamadas = " << llamadas.at(pos).numero << endl;
						pos++;
				    }
				    fileNUMEROS.close();
				}
				for (int i = 0; i < numeros.size(); ++i){
					cout << "numero [" << i << "] = " << numeros.at(i) << endl;
				}
				int ran;
				srand (time(0));
				cout << " Size = " << numeros.size() << endl;
				for (int i = 0; i < llamadas.size(); ++i){
					
					ran = rand() % numeros.size();
					strncpy(llamadas.at(i).numero, numeros.at(ran), 9);
					ran = rand() % numeros.size();
					strncpy(llamadas.at(i).destino, numeros.at(ran), 9);
				}
				pos = 0;
				
				/*for (int i = 0; i < numeros.size(); ++i){
					int ran = rand() % numeros.size();
					destino.push_back(numeros.at(ran) );
					strncpy(llamadas.at(pos).destino, destino.at(i), 9);
					//cout << "LLamadas 2 = " << llamadas.at(pos).destino << endl;
				}*/
				
				ofstream file("llamadas.bin", ofstream::binary);
				for (int i = 0; i < llamadas.size(); ++i){
					cout << "Numero = " << llamadas.at(i).numero << "\tInicio = " << llamadas.at(i).inicio << "\tFinal = " << llamadas.at(i).final << "\tDestino = " << llamadas.at(i).destino << endl;
					file.write(reinterpret_cast<const char*> (&llamadas.at(i)), sizeof(llamada));
				}
				cout << "LLamada" << llamadas.at(0).numero << endl;
				cout << "Exito en la operacion" << endl;
				file.close();
			}
			break;
			default: cout << "Opcion invalida" << endl;
					cout << "MENU\n1)Leer Numeros\n2)Guardar Informacion" << endl;
					cin >> opcionMenu;
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
	cin >> menu;
	while(menu != 1 && menu != 2 && menu != 3){
		cout << "MENU\n1)Leer Numeros\n2)Guardar Informacion\n3)Cargar Datos" << endl;
		cin >> menu;
	}
	return menu;
}