#include <iostream>

using namespace std;

int menu();
int menu_cliente();
int menu_ciudad();
int menu_lineaxcliente();

int main(int argc, char* argv[]){
	cout<<"Bienvenido"<<endl;
	char resp='s';
	while(resp=='s'||resp=='S'){//while para iniciar el programa
		switch(menu()){//switch principal (menu)

			case 1:{//case 1 Archivo de Clientes
				cout<<"Archivo de Clientes"<<endl;
				switch(menu_cliente()){//switch de archvio de clientes (menu_cliente)
					
					case 1:{//case 1 Agregar (Archivo de Clientes) 
						break;
					}//fin case 1 Agregar (Archivo de Clientes) 

					case 2:{//case 2 Modificar (Archivo de Clientes) 
						break;
					}//fin case 2 Modificar (Archivo de Clientes)

					case 3:{//case 3 Borrar (Archivo de Clientes)
						break;
					}//fin case 3 Borrar (Archivo de Clientes)

					case 4:{//case 4 Listar (Archivo de Clientes)
						break;
					}//fin case 4 Listar (Archivo de Clientes)

					case 5:{//case 5 Buscar (Archivo de Clientes)
						break;
					}//fin case 5 Buscar (Archivo de Clientes)

				}//fin switch de archvio de clientes (menu_cliente)
				break;
			}//fin case 1 Archivo de Clientes

			case 2:{//case 2 Archivo de ciudades
				cout<<"Archivo de Ciudades"<<endl;
				break;
			}//fin case 2 Archivo de ciudades

			case 3:{//case 3 Archivo de Lineas por Cliente
				cout<<"Archivo de Lineas por Cliente"<<endl;
				break;
			}//fin case 3 Archivo de Lineas por Cliente

		}//fin switch principal (menu)
		cout<<"Desea volver a ingresar al programa?(S/N)";
		cin>>resp;
	}//fin while para iniciar el programa
	return 0;
}

int menu(){
	int opcion;
	cout<<"Menu Principal"<<endl;
	cout<<"Elija una opcion:\n1. Archivo de Clientes\n2. Archivo de Ciudades\n3. Archivo de Lineas por Cliente\n4. Salir\nIgrese su opcion: ";
	cin>>opcion;
	return opcion;
}

int menu_cliente(){
	int opcion;
	cout<<"Menu Cliente"<<endl;
	cout<<"Elija una opcion:\n1. Agregar\n2. Modificar\n3. Borrar\n4. Listar\n5. Buscar\n6. Salir\nIgrese su opcion: ";
	cin>>opcion;
	return opcion;	
}

int menu_ciudad(){
	int opcion;
	cout<<"Menu Cliudad"<<endl;
	cout<<"Elija una opcion:\n1. Agregar\n2. Modificar\n3. Borrar\n4. Listar\n5. Buscar\n6. Salir\nIgrese su opcion: ";
	cin>>opcion;
	return opcion;
}

int menu_lineaxcliente(){
	int opcion;
	cout<<"Menu Linea por Cliente"<<endl;
	cout<<"Elija una opcion:\n1. Agregar\n2. Modificar\n3. Borrar\n4. Listar\n5. Buscar\n6. Salir\nIgrese su opcion: ";
	cin>>opcion;
	return opcion;
}