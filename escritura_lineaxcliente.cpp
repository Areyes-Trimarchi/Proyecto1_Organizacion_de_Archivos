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

struct Header{
	int availList;
	int sizeRegistro;
};

void reset(char info[15]);
void combineidCliente(char id[9],char info[15]);
void combinenumero(char id[14],char info[15]);

int main(int argc, char* argv[]){
	string texto;
	ifstream lineaxcliente("lineasxcliente.txt");
	ofstream file("lineaxclientes.bin", ofstream::binary);
	int sizeRegistro = 0;
	int availList =  -1;
	Header head;
	head.availList=availList;
	head.sizeRegistro=sizeRegistro;

	lineaxcliente.seekg(0, lineaxcliente.end);
	int length = lineaxcliente.tellg();
	lineaxcliente.seekg(0, lineaxcliente.beg);

	file.write(reinterpret_cast<char*>(&head), sizeof(Header));
	int cont=0;
	while (cont!=length){
		char numero[9];
		char idCliente[14];
		getline(lineaxcliente,texto);
		LineaxCliente linea;
		int contadorcoma=0;
		int contador_numero=0;
		int contador_id=1;
		idCliente[0]='0';
		for(int i=0;i<22;i++){
			if(texto[i]==','||contadorcoma!=0){
				contadorcoma++;
				if(texto[i]!=','){
					idCliente[contador_id]=texto[i];
					contador_id++;
				}
			}else{
				numero[contador_numero]=texto[i];
				contador_numero++;
			}

		}
		numero[8]='\0';
		idCliente[13]='\0';
		strncpy(linea.numero,numero,9);
		strncpy(linea.idCliente,idCliente,14);
        cout << "NUMERO = " << linea.numero << "\tIDCLIENTE = " << linea.idCliente << endl;
		file.write(reinterpret_cast<char*>(&linea), sizeof(LineaxCliente));
		sizeRegistro++;
		cont = lineaxcliente.tellg();
	}
    cout << "Size = " << sizeRegistro << endl;
	head.sizeRegistro = sizeRegistro;
	file.seekp(0);
	file.write(reinterpret_cast<char*>(&head), sizeof(Header));
	file.close();
	lineaxcliente.close();
	return 0;
}
