#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>

using namespace std;

struct Cliente{
	char name[40];
	char genero;
	int idCiudad;
	char idCliente[14];
};

void reset(char info[40]);
void combine(char array[40],char info[40]);
void combineidCliente(char id[14],char info[40]);
int chartoidCiudad(char info[40]);

int main(int argc, char* argv[]){
	string texto;
	ifstream clientes("clientes.txt");
	ofstream file("clientes.bin", ofstream::binary);

	int sizeRegistro = 0;
	int availList =  -1;

	file.write(reinterpret_cast<char*>(&sizeRegistro), sizeof(sizeRegistro));
	file.write(reinterpret_cast<char*>(&availList), sizeof(availList));
	cout << "Antes = " << sizeRegistro << endl;
	while (!clientes.eof()){
		getline(clientes,texto);
		Cliente cliente;
		int coma=0;
		char info[40];
		int contador=0;
		for(int i=0;i<texto.size();i++){
			if(texto[i]==','){
				coma++;
				switch(coma){
					case 1:{
						info[contador+1]='\0';
						combine(cliente.name,info);
						contador=-1;
						reset(info);
						break;
					}
					case 2:{
						contador=0;
						info[0]='0';
						break;
					}case 3:{
						info[contador+1]='\0';
						combineidCliente(cliente.idCliente,info);
						contador=-1;
						reset(info);
						break;
					}
					case 4:{
						info[contador+1]='\0';
						cliente.genero=info[0];
						contador=-1;
						reset(info); 
						break;
					}
				}
			}else{
				info[contador]=texto[i];
			}	
			contador++;
		}
		info[contador+1]='\0';
		cliente.idCiudad=chartoidCiudad(info);
		file.write(reinterpret_cast<char*>(&cliente), sizeof(cliente));
		sizeRegistro++;
	}
	sizeRegistro = sizeRegistro - 1;
	file.seekp(0);
	cout << "Final = " << sizeRegistro << endl;
	file.write(reinterpret_cast<char*>(&sizeRegistro), sizeof(sizeRegistro));
	file.close();
	clientes.close();
	return 0;
}
void reset(char info[40]){
	for (int i = 0; i < 40; ++i)
	{
		info[i]='\0';
	}
}
void combine(char name[40],char info[40]){
	for (int i = 0; i < 40; ++i)
	{
		name[i]=info[i];
	}
}
void combineidCliente(char id[14],char info[40]){
	for (int i = 0; i < 14; ++i)
	{
		id[i]=info[i];
	}
}
int chartoidCiudad(char info[40]){
	int resp;
	stringstream integ;
	integ<<info;
	integ>>resp;
	return resp;
}
