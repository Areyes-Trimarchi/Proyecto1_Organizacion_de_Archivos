#pragma once

#include <iostream>
#include <vector>
#include "b-tree.h"

using namespace std;

struct Factura {
    char idCliente[14];
    char name[40];
    char ciudadNombre[40];
    vector<string> numeros_cliente;
    vector<Llamada> llamadas_cliente;
    vector<double> costo;
};

class FacturaA{
public:
	FacturaA();
	~FacturaA();
	void corre();
	long years_to_seconds(string);
	long month_to_seconds(string);
	long days_to_seconds(string);
	long hours_to_seconds(string);
	long minutes_to_seconds(string);
};