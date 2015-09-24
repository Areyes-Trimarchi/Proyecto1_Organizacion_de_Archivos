exe:		main.o crud_LineasXClienteArbol.o crud_clientesarbol.o crud_CiudadesArbol.o b-tree.o b-treenode.o crud_LineasXCliente.o crud_Ciudades.o crud_clientes.o index.o 
		g++ main.o crud_LineasXClienteArbol.o crud_clientesarbol.o crud_CiudadesArbol.o b-tree.o b-treenode.o crud_LineasXCliente.o crud_Ciudades.o crud_clientes.o  index.o  -o exe
main.o:	main.cpp index.h crud_LineasXCliente.h crud_Ciudades.h crud_clientes.h crud_clientesarbol.h b-tree.h crud_CiudadesArbol.h crud_LineasXClienteArbol.h
		g++ -c main.cpp
crud_LineasXClienteArbol.o:	crud_LineasXClienteArbol.cpp crud_LineasXClienteArbol.h b-tree.h
		g++ -c crud_LineasXClienteArbol.cpp
crud_CiudadesArbol.o:	crud_CiudadesArbol.cpp crud_CiudadesArbol.h b-tree.h 
		g++ -c crud_CiudadesArbol.cpp
crud_clientesarbol.o:	crud_clientesarbol.cpp crud_clientesarbol.h b-tree.h 
		g++ -c crud_clientesarbol.cpp
b-tree.o:	b-tree.cpp b-tree.h b-treenode.h
		g++ -c b-tree.cpp
b-treenode.o: 	b-treenode.cpp b-treenode.h
		g++ -c b-treenode.cpp
crud_LineasXCliente.o:	crud_LineasXCliente.cpp crud_LineasXCliente.h index.h 
		g++ -c crud_LineasXCliente.cpp
crud_Ciudades.o:	crud_Ciudades.cpp crud_Ciudades.h index.h 
		g++ -c crud_Ciudades.cpp
crud_clientes.o:	crud_clientes.cpp crud_clientes.h index.h 
		g++ -c crud_clientes.cpp
index.o: 	index.cpp index.h
		g++ -c index.cpp