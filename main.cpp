#include <iostream>
#include "index.h"
#include "crud_clientes.h"
#include "crud_Ciudades.h"
#include "crud_LineasXCliente.h"
#include "b-tree.h"
#include "crud_CiudadesArbol.h"
#include "crud_LineasXClienteArbol.h"
#include "crud_clientesarbol.h"
#include "factura.h"
#include <cstring>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

//Declaracion de metodos
int menu();
int menu_cliente();
int menu_ciudad();
int menu_lineaxcliente();
//Fin Declaracion de metodos

int main(int argc, char* argv[]){//inicio main
	cout<<"Bienvenido"<<endl;
	char resp='s';
	while(resp=='s'||resp=='S'){//while para iniciar el programa
		switch(menu()){//switch principal (menu)

			case 1:{//case 1 Archivo de Clientes
				cout<<"Archivo de Clientes"<<endl;
				Crud_Clientes crud_clientes;
				switch(menu_cliente()){//switch de archvio de clientes (menu_cliente)
					
					case 1:{//case 1 Agregar (Archivo de Clientes)
						if(!crud_clientes.Agregar()){
							cerr<<"Ocurrio un error"<<endl;
						} 
						break;
					}//fin case 1 Agregar (Archivo de Clientes) 

					case 2:{//case 2 Modificar (Archivo de Clientes)
						if(!crud_clientes.Modificar()){
							cerr<<"Ocurrio un error"<<endl;
						}  
						break;
					}//fin case 2 Modificar (Archivo de Clientes)

					case 3:{//case 3 Borrar (Archivo de Clientes)
						if(!crud_clientes.Borrar()){
							cerr<<"Ocurrio un error"<<endl;
						}
						break;
					}//fin case 3 Borrar (Archivo de Clientes)

					case 4:{//case 4 Listar (Archivo de Clientes)
						if(!crud_clientes.Listar()){
							cerr<<"Ocurrio un error"<<endl;
						}
						/*char siNo;
						cout<<"Desea Listar por arbol (S/N): ";
						cin>>siNo;
						if(siNo=='S'||siNo=='s'){
							if(!crud_clientes.ListarArbol()){
							cerr<<"Ocurrio un error"<<endl;
							}
						}else{
							
						}*/
						break;
					}//fin case 4 Listar (Archivo de Clientes)

					case 5:{//case 5 Buscar (Archivo de Clientes)
						int option;
						cout<<"Como desea Buscar\n1. Con Indice\n2. Sin Indice\nElija una opcion: ";
						cin>>option;
						switch(option){//switch de opcion para buscar clientes

							case 1:{//case 1 para buscar clientes con indice
								if(!crud_clientes.BuscarIndex()){
									cerr<<"Ocurrio un error"<<endl;
								}
								break;
							}//FIN case 1 para buscar clientes con indice

							case 2:{//case 2 para buscar clientes SIN indice
								if(!crud_clientes.Buscar()){
									cerr<<"Ocurrio un error"<<endl;
								}
								break;
							}//FIN case 2 para buscar clientes SIN indice

						}//FIN switch de opcion para buscar clientes
						break;
					}//fin case 5 Buscar (Archivo de Clientes)

				}//fin switch de archvio de clientes (menu_cliente)
				break;
			}//fin case 1 Archivo de Clientes

			case 2:{//case 2 Archivo de ciudades
				cout<<"Archivo de Ciudades"<<endl;
				crud_ciudades crud_ciudades;
				crud_ciudades.correr();
				break;
			}//fin case 2 Archivo de ciudades

			case 3:{//case 3 Archivo de Lineas por Cliente
				cout<<"Archivo de Lineas por Cliente"<<endl;
				crud_lineasxcliente crud_lineasxcliente;
				crud_lineasxcliente.correr();
				break;
			}//fin case 3 Archivo de Lineas por Cliente
			case 4:{//case 4 Archivo de Ciudades con el Arbol-B
				cout<<"Archivo de Ciudades"<<endl;
				crud_ciudadesArbol crud_ciudadesArbol;
				crud_ciudadesArbol.correr();
			}//fin case 4 Archivo de Ciudades con el Arbol-B
			break;
			case 5:{//case 5 Archivo de Lineas por Cliente con el Arbol-B
				cout<<"Archivo de Lineas por Cliente"<<endl;
				crud_lineasxclienteArbol crud_lineasxclienteArbol;
				crud_lineasxclienteArbol.correr();
			}//fin case 5 Archivo de Lineas por Cliente con el Arbol-B
			break;
			case 6:{
				cout<<"Archivo de Clientes"<<endl;
				crud_ClientesArbol crud_clientesarbol;
				crud_clientesarbol.correr();
			}
			case 7:{//case 5 Para hacer facturas
				cout<<"Facturas"<<endl;
				FacturaA factura;
				factura.corre();
			}//fin case 5 Para hacer facturas
			break;

		}//fin switch principal (menu)
		cout<<"Desea volver a ingresar al programa?(S/N)";
		cin>>resp;
	}//fin while para iniciar el programa
	return 0;
}//fin main

//METODOS
int menu(){
	int opcion;
	cout<<"Menu Principal"<<endl;
	cout<<"Elija una opcion:\n1. Archivo de Clientes\n2. Archivo de Ciudades\n3. Archivo de Lineas por Cliente\n";
	cout << "4. Archivo de Ciudades con Arbol-B\n5. Archivo de Lineas por Cliente con Arbol-B\n6. Archivo Cliente con Arbol-B\n7. Facturar";
	cout << "\n8. Salir\nIngrese su opcion: ";
	cin>>opcion;
	return opcion;
}

int menu_cliente(){
	int opcion;
	cout<<"Menu Cliente"<<endl;
	cout<<"Elija una opcion:\n1. Agregar\n2. Modificar\n3. Borrar\n4. Listar\n5. Buscar\n6. Salir\nIngrese su opcion: ";
	cin>>opcion;
	return opcion;	
}

int menu_ciudad(){
	int opcion;
	cout<<"Menu Cliudad"<<endl;
	cout<<"Elija una opcion:\n1. Agregar\n2. Modificar\n3. Borrar\n4. Listar\n5. Buscar\n6. Salir\nIngrese su opcion: ";
	cin>>opcion;
	return opcion;
}

int menu_lineaxcliente(){
	int opcion;
	cout<<"Menu Linea por Cliente"<<endl;
	cout<<"Elija una opcion:\n1. Agregar\n2. Modificar\n3. Borrar\n4. Listar\n5. Buscar\n6. Salir\nIngrese su opcion: ";
	cin>>opcion;
	return opcion;
}
//FIN METODOS