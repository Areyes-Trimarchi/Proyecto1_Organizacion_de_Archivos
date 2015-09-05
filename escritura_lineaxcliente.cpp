#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>

using namespace std;

struct LineaxCliente{
	char numero[9];
	char idCliente[14];
};

void reset(char info[15]);
void combineidCliente(char id[9],char info[15]);
void combinenumero(char id[14],char info[15]);

int main(int argc, char* argv[]){
	string texto;
	ifstream lineaxcliente("lineasxcliente.txt");
	ofstream file("clientes.bin", ofstream::binary);
	
	int sizeRegistro = 0;
	int availList =  -1;

	file.write(reinterpret_cast<char*>(&sizeRegistro), sizeof(sizeRegistro));
	file.write(reinterpret_cast<char*>(&availList), sizeof(availList));
	cout << "Antes = " << sizeRegistro << endl;
	while (!lineaxcliente.eof()){
		getline(lineaxcliente,texto);
		LineaxCliente linea;
		int coma=0;
		char info[15];
		int contador=0;
		for(int i=0;i<texto.size();i++){
			if(texto[i]==','){
				coma++;
				switch(coma){
					case 1:{
						info[contador+1]='\0';
						combinenumero(linea.numero,info);
						contador=0;
						reset(info);
						info[0]='0';
						break;
					}
				}
			}else{
				info[contador]=texto[i];
			}	
			contador++;
		}
		info[contador+1]='\0';

		combineidCliente(linea.idCliente,info);
		file.write(reinterpret_cast<char*>(&linea), sizeof(linea));
		reset(info);
		sizeRegistro++;
	}
	sizeRegistro = sizeRegistro - 1;
	file.seekp(0);
	cout << "Final = " << sizeRegistro << endl;
	file.write(reinterpret_cast<char*>(&sizeRegistro), sizeof(sizeRegistro));
	file.close();
	lineaxcliente.close();
	return 0;
}
void reset(char info[15]){
	for (int i = 0; i < 15; ++i)
	{
		info[i]='\0';
	}
}

void combineidCliente(char id[14],char info[15]){
	for (int i = 0; i < 14; ++i)
	{
		id[i]=info[i];
	}
}
void combinenumero(char num[9],char info[15]){
	for (int i = 0; i < 9; ++i)
	{
		num[i]=info[i];
	}
}
