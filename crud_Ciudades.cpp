#include <iostream>
#include <stdlib.h>
#include <fstream>

using namespace std;

struct Ciudad{
	char name[40];
	int idCiudad;
};

ostream& operator<<(ostream& output, const Ciudad& city){
	output << city.name << "\t" << city.idCiudad << endl;
	return output;  
}
istream& operator>>(istream& input, Ciudad& city){
	 input >> city.numero >> city.inicio;
	 return input;
}

int main(int argc, char const *argv[]){

	int opcionMenuPrincipal;
	cout << "******* MENU *******\n1) Agregar\n
	3) Modificar\n
	4) Listar\n
	5) Borrar\n
	6) Buscar\n
	7) Reindexar" << endl;
	cin >> opcionMenuPrincipal;
	switch(opcionMenuPrincipal){
		case 1:{
			Ciudad city;
			ifstream file("data.bin", ifstream::binary);
			int cont = 0 ;
			while(file.read(reinterpret_cast<char*>(&city), sizeof(city))){
				cout << city << endl;
				cout << cont << endl;
				cont++;
			}
		}
		break;
		case 2:{

		}
		break;
		case 3:{

		}
		break;
		case 4:{

		}
		break;
		case 5:{

		}
		break;
		case 6:{
			int opcionBuscar:
			cout << "\t1)Sin indice\n\t2)con indice\n"
			swicth(opcionBuscar){
				case 1:{

				}
				break;
				case 2:{

				}
				break;
			}
		}
		break;
	}
	return 0;
}