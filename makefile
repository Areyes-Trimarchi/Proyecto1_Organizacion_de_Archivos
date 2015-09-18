exe:		main.o crud_LineasXCliente.o crud_Ciudades.o crud_clientes.o index.o 
		g++ main.o crud_LineasXCliente.o crud_Ciudades.o crud_clientes.o  index.o  -o exe
main.o:	main.cpp index.h  
		g++ -c main.cpp
crud_LineasXCliente.o:	crud_LineasXCliente.cpp crud_LineasXCliente.h index.h 
		g++ -c crud_LineasXCliente.cpp
crud_Ciudades.o:	crud_Ciudades.cpp crud_Ciudades.h index.h 
		g++ -c crud_Ciudades.cpp
crud_clientes.o:	crud_clientes.cpp crud_clientes.h index.h 
		g++ -c crud_clientes.cpp
index.o: 	index.cpp index.h
		g++ -c index.cpp