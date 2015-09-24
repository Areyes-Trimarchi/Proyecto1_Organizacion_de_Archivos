#include <iostream>
#include "b-tree.h"
#include "factura.h"
#include <cstring>
#include <string>
#include <sstream>
#include <cstdlib>
#include <fstream>
#include <vector>

using namespace std;

istream& operator>>(istream& input, Llamada& llamada){
     input >> llamada.numero >> llamada.inicio >> llamada.final >> llamada.destino;
     return input;
}

FacturaA::FacturaA(){

}

FacturaA::~FacturaA(){

}

void FacturaA::corre(){
    cout << "\tFacturas\n";
    fstream file_Ciudades("ciudades.bin", fstream::binary);
    fstream file_Clientes("clientes.bin", fstream::binary);
    fstream file_Lineas("lineaxclientes.bin", fstream::binary); //llamadas
    fstream file_Llamadas("llamadas.bin", fstream::binary);
    vector<Factura> facturas;

    file_Ciudades.open("ciudades.bin");
    file_Clientes.open("clientes.bin");
    file_Lineas.open("lineaxclientes.bin");
    file_Llamadas.open("llamadas.bin");
    HeaderArbol header;

    ClienteArbol client;
    char name[40];
    int idCiudad;
    char idCliente[14];
    char ciudadNombre[40];

    file_Clientes.seekg(0);
    file_Clientes.read(reinterpret_cast<char*>(&header), sizeof(HeaderArbol));
    while( file_Clientes.read(reinterpret_cast<char*>(&client), sizeof(ClienteArbol)) ){
        cout << "Entro cliente " << endl;
        strncpy(name, client.nombre, 40);                             //Cargando datos iniciales
        idCiudad = client.idCiudad;
        strncpy(idCliente, client.idCliente, 14);
        
        CiudadArbol ciudad;
        file_Ciudades.seekg(0);
        file_Ciudades.read(reinterpret_cast<char*>(&header), sizeof(HeaderArbol));
        while( file_Ciudades.read(reinterpret_cast<char*>(&ciudad), sizeof(CiudadArbol)) ){
            if(idCiudad == ciudad.idCiudad){                         //Encontrando la ciudad del cliente actual
                strncpy(ciudadNombre, ciudad.name, 40);
                break;
            }
            cout << "Entro ciudades " << endl;
        }

        LineaxClienteArbol linea;
        vector<string> numeros_cliente;
        file_Lineas.seekg(0);
        file_Lineas.read(reinterpret_cast<char*>(&header), sizeof(HeaderArbol));
        while( file_Lineas.read(reinterpret_cast<char*>(&linea), sizeof(LineaxClienteArbol)) ){
            if( strncmp(idCliente, linea.idCliente, 14) == 0)
                numeros_cliente.push_back(linea.numero);               //Cargando los numeros totales del cliente
            cout << "Entro lineas\t idCliente = " << idCliente << "\t linea idCliente = " << linea.idCliente << endl;
        }

        
        vector<Llamada> llamadas_cliente;
        for (int i = 0; i < numeros_cliente.size(); ++i){
            Llamada call;
            file_Llamadas.seekg(0);
            file_Llamadas.read(reinterpret_cast<char*>(&header), sizeof(HeaderArbol));
            while( file_Llamadas.read(reinterpret_cast<char*>(&call), sizeof(Llamada)) ){
                cout << "numeros_cliente = " << numeros_cliente.at(i) << "\tcall numero = " << call.numero << endl;
                if( strcmp(numeros_cliente.at(i).c_str(), call.numero) == 0)
                    llamadas_cliente.push_back(call);                   //Cargando las llamadas que el cliente realizo
            }
            cout << "Entro llamdaas " << endl;
        }
        cout << "Size = " << llamadas_cliente.size() << endl;
        for (int i = 0; i < llamadas_cliente.size(); ++i){
            string anio_inicio;
            string mes_inicio;
            string dia_inicio;
            string hora_inicio;
            string minutos_inicio;
            string segundos_inicio;

            string anio_final;
            string mes_final;
            string dia_final;
            string hora_final;
            string minutos_final;
            string segundos_final;

            string inicio;
            inicio = llamadas_cliente.at(i).inicio;
            anio_inicio = inicio.substr(0, 4);
            mes_inicio = inicio.substr(5, 2);
            dia_inicio = inicio.substr(8, 2);
            hora_inicio = inicio.substr(11, 2);
            minutos_inicio = inicio.substr(14,2);
            segundos_inicio = inicio.substr(17,2);

            string final;
            final = llamadas_cliente.at(i).inicio;
            anio_final = final.substr(0, 4);;
            mes_final = final.substr(5, 2);
            dia_final = final.substr(8, 2);
            hora_final = final.substr(11, 2);
            minutos_final = final.substr(14,2);
            segundos_final = final.substr(17,2);

            long year_inicio = years_to_seconds(anio_inicio);
            long month_inicio = month_to_seconds(mes_inicio);
            long day_inicio = days_to_seconds(dia_inicio);
            long hour_inicio = hours_to_seconds(hora_inicio);
            long minutes_inicio = minutes_to_seconds(minutos_inicio);
            long seconds_inicio = atoi(segundos_inicio.c_str());

            long year_final = years_to_seconds(anio_final);
            long month_final = month_to_seconds(mes_final);
            long day_final = days_to_seconds(dia_final);
            long hour_final = hours_to_seconds(hora_final);
            long minutes_final = minutes_to_seconds(minutos_final);
            long seconds_final = atoi(segundos_final.c_str());

            long total_inicio = year_inicio + month_inicio + day_inicio + hour_inicio + minutes_inicio + seconds_inicio;
            long total_final = year_final + month_final + day_final + hour_final + minutes_final + seconds_final;
            long total = total_final - total_inicio;
            long tarifa_AM1 = hours_to_seconds("8");
            long tarifa_AM2 = hours_to_seconds("15") + minutes_to_seconds("59") + 59 ;
            long tarifa_1 = hours_to_seconds("16");
            long tarifa_2 = hours_to_seconds("23") + minutes_to_seconds("59") + 59 ;
            long tarifa_PM1 = hours_to_seconds("0");
            long tarifa_PM2 = hours_to_seconds("7") + minutes_to_seconds("59") + 59 ;

            long horas = hour_inicio + minutes_inicio + seconds_inicio;
            double precio;
            if( horas >  tarifa_AM1 && horas < tarifa_AM2){
                precio = (horas/60) * 0.05;
            } else if ( horas > tarifa_1 && horas < tarifa_2){
                precio = (horas/60) * 0.04;
            } else{
                precio = (horas/60) * 0.01;
            }
            Factura fac;
            strncpy(fac.idCliente, idCliente, 14);
            strncpy(fac.name, name, 40);
            strncpy(fac.ciudadNombre, ciudadNombre, 40);
            fac.numeros_cliente = numeros_cliente;
            fac.llamadas_cliente = llamadas_cliente;
            fac.costo = precio;
            facturas.push_back(fac);
        }
        file_Ciudades.close();
        file_Clientes.close();
        file_Lineas.close();
        file_Llamadas.close();
    }// Fin while

    cout << "\tImpresion de Facturas" << endl;
    for (int i = 0; i < facturas.size(); ++i){
        cout << "ID Cliente = "  << facturas.at(i).idCliente << "\tNombre = " << facturas.at(i).name << "\tCiudad = " << facturas.at(i).ciudadNombre << endl;
        for (int j = 0; j < facturas.at(i).numeros_cliente.size(); ++j){
            cout << "Numero = " << facturas.at(i).numeros_cliente.at(j) << ":\tNumero\tDestino\tInicio\tFinal\tPrecio" << endl;
            for (int k = 0; k < facturas.at(k).llamadas_cliente.size(); ++k){
                if( strncmp(facturas.at(i).numeros_cliente.at(j).c_str(), facturas.at(i).llamadas_cliente.at(k).numero, 9) == 0){
                    cout << "\t\t\t" << facturas.at(i).llamadas_cliente.at(k).numero << "\t" << facturas.at(i).llamadas_cliente.at(k).destino;
                    cout << "\t" << facturas.at(i).llamadas_cliente.at(k).inicio << "\t" << facturas.at(i).llamadas_cliente.at(k).final << endl;
                }
            }
        }
    }

}

long FacturaA::years_to_seconds(string year){
    long seconds;
    int anio = atoi(year.c_str());
    seconds = anio * 12 * 30 * 24 * 60 * 60;
    return seconds;
}

long FacturaA::month_to_seconds(string month){
    long seconds;
    int mes = atoi(month.c_str());
    seconds = mes * 30 * 24 * 60 * 60;
    return seconds;
}

long FacturaA::days_to_seconds(string day){
    long seconds;
    int dia = atoi(day.c_str());
    seconds = dia * 24 * 60 * 60;
    return seconds;
}

long FacturaA::hours_to_seconds(string hour){
    long seconds;
    int hora = atoi(hour.c_str());
    seconds = hora * 60 * 60;
    return seconds;
}

long FacturaA::minutes_to_seconds(string minutes){
    long seconds;
    int  minutos = atoi(minutes.c_str());
    seconds = minutos * 60;
    return seconds;
}