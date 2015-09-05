#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <sstream>

using namespace std;

struct Ciudad{
	char name[40];
	int idCiudad;
};

ostream& operator<<(ostream& output, const Ciudad& city){
	output << "nombre = " << city.name << "\t" << "idCiudad = " << city.idCiudad << endl;
	return output;  
}

void reset(char info[40]);
void combine(char name[40],char info[40]);
int chartoidCiudad(char info[40]);

int main(int argc, char* argv[]){
	string texto;
	ifstream ciudad_file("ciudades.txt");
	ofstream file("ciudades.bin", ofstream::binary);

	int sizeRegistro = 0;
	int availList =  -1;

	file.write(reinterpret_cast<char*>(&sizeRegistro), sizeof(sizeRegistro));
	file.write(reinterpret_cast<char*>(&availList), sizeof(availList));
	cout << "Antes = " << sizeRegistro << endl;
	while (!ciudad_file.eof()){
		getline(ciudad_file,texto);
		Ciudad ciudad;
		int coma=0;
		char info[40];
		int contador=0;

		for(int i=0;i<texto.size();i++){
			if(texto[i]==','){
				coma++;
				switch(coma){
					case 1:{
						info[contador+1]='\0';
						combine(ciudad.name,info);
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
		ciudad.idCiudad=chartoidCiudad(info);
		file.write(reinterpret_cast<char*>(&ciudad), sizeof(ciudad));
		sizeRegistro++;
	}
	sizeRegistro = sizeRegistro - 1;
	file.seekp(0);
	cout << "Final = " << sizeRegistro << endl;
	file.write(reinterpret_cast<char*>(&sizeRegistro), sizeof(sizeRegistro));
	file.close();
	ciudad_file.close();
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

int chartoidCiudad(char info[40]){
	int resp;
	stringstream integ;
	integ<<info;
	integ>>resp;
	return resp;
}
