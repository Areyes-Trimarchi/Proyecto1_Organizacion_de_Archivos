#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

using namespace std;

struct Cliente{
	char name[40];
	char genero;
	int idCiudad;
	int idCliente;
};

void reset(char info[40]);
void combine(char array[40],char info[40]);
int chartoidCliente(char info[40]);
int chartoidCiudad(char info[40]);

int main(int argc, char* argv[]){
	string texto;
	ifstream clientes("clientes.txt");
	while (!clientes.eof()){
		getline(clientes,texto);
		Cliente cliente;
		int coma=0;
		char info[40];
		int contador=0;
		cout<<"TEXTO "<<texto<<endl;
		for(int i=0;i<texto.size();i++){
			if(texto[i]==','){
				coma++;
				switch(coma){
					case 1:{
						cout<<"NAME : "<<info<<endl;
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
						cout<<"Id cliente : chartoidCliente(info) "<<chartoidCliente(info)<<endl;
						info[contador+1]='\0';
						cliente.idCliente=chartoidCliente(info);
						contador=-1;
						reset(info);
						break;
					}
					case 4:{
						cout<<"genero : "<<info<<endl;
						cout<<"GENERO "<<info;
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
		cout<<"info final "<<info<<endl;
		info[contador+1]='\0';
		cliente.idCiudad=chartoidCiudad(info);
		cout<<"Cliente "<<cliente.name<<","<<cliente.idCliente<<","<<cliente.genero<<","<<cliente.idCiudad<<endl;
	}
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
int chartoidCliente(char info[40]){
	int resp;
	resp=atoi(info);
	cout<<"RESP CLIENTE "<<resp<<endl;
	return resp;
}
int chartoidCiudad(char info[40]){
	int resp;
	resp=atoi(info);
	cout<<"RESP ciudad "<<resp<<endl;
	return resp;
}