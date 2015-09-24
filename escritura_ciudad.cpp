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

struct Header{
	int availList;
	int sizeRegistro;
};

ostream& operator<<(ostream& output, const Ciudad& city){
	output << "nombre = " << city.name << "\t" << "idCiudad = " << city.idCiudad << endl;
	return output;  
}

ostream& operator<<(ostream& output, const Header& city){
	output << "Avail = " << city.availList << "\t" << "Size = " << city.sizeRegistro << endl;
	return output;  
}

void reset(char info[40]);
void combine(char name[40],char info[40]);
int chartoidCiudad(char info[40]);

int main(int argc, char* argv[]){
	Header headA;
	ifstream fileA("ciudades.bin", ifstream::binary);
	fileA.read(reinterpret_cast<char*>(&headA), sizeof(Header));
	cout << headA;
	fileA.close();

	string texto;
	ifstream ciudad_file("ciudades.txt");
	ofstream file("ciudades.bin", ofstream::binary);

	int sizeRegistro = 0;

	Header head;
	head.availList = -1;
	head.sizeRegistro = 0;

	ciudad_file.seekg(0, ciudad_file.end);
	int length = ciudad_file.tellg();
	ciudad_file.seekg(0, ciudad_file.beg);


	file.write(reinterpret_cast<char*>(&head), sizeof(Header));
	cout << "Antes = " << head.sizeRegistro << endl;
	int cont = 0;
	while (cont != length){
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
		cout << ciudad;
		file.write(reinterpret_cast<char*>(&ciudad), sizeof(Ciudad));
		sizeRegistro++;
		cont = ciudad_file.tellg();
	}
	sizeRegistro = sizeRegistro;
	file.seekp(0);
	cout << "Final = " << sizeRegistro << endl;
	head.sizeRegistro = sizeRegistro;
	file.write(reinterpret_cast<char*>(&head), sizeof(Header));
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

