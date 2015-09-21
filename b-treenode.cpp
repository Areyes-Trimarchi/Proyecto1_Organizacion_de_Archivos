#include "b-treenode.h"
#include <iostream>

using namespace std;

BTreeNode::BTreeNode(bool hoja, int ordenArbol){
	this->hoja = hoja;

	this->tamano = 0;
	this->minimo = (ordenArbol/2)-1;
	this->maximo = ordenArbol - 1;
	this->llaves =  new Key[ordenArbol-1];
	this->hijos = new BTreeNode *[ordenArbol];
}

BTreeNode::~BTreeNode(){

}

void BTreeNode::split(){

}

*BTreeNode BTreeNode::busqueda(int llaveBusqueda){
	int posicion = 0;
	for (int i = 0; i < tamano; i++){
		if(llaveBusqueda < llaves[i]->llave)
			posicion++;
	}

    if (keys[posicion] == k)
        return keys[posicion];
    if (leaf == true)
        return NULL;
    return C[posicion]->busqueda(llaveBusqueda);
}

int BTreeNode::LlaveExiste(Key llave){
    int pos_key=0;
    while (pos_key<tamano && llaves[pos_key] < llave){
        ++pos_key;
    }
    return pos_key;
}

void BTreeNode::Remove(Key* llave){
    int pos_key = LlaveExiste(llave);
    if (pos_key < tamano && llaves[pos_key]== llave){
        if (!hoja){//Remove cuando no es hoja
        	Key* tmp_llave = llaves[pos_key];
		    if (hijos[pos_key]->tamano >= minimo){
		        Key *prev = getPrev(pos_key);
		        llaves[pos_key]= prev;
		        hijos[pos_key]->Remove(prev);
		    }else if  (hijos[pos_key+1]->tamano >= minimo){
		        Key *next = getNext(pos_key);
		        llaves[pos_key] = next;
		        hijos[pos_key+1]->Remove(next);
		    }else
		    {
		        merge(pos_key);
		        hijos[pos_key]->Remove(tmp_llave);
		    }	
        }else{//remove cuando es hoja
        	for (int i=pos_key+1; i<tamano; ++i){
		        llaves[i-1] = llaves[i];
		 	}
		    tamano--;
        }    
    }else{
        if (hoja){
            cout << "La llave "<< llave <<" que usted ingreso no existe :(\n";
            return;
        }
        bool esta_noesta = ( (pos_key==tamano)? true : false );
        if (hijos[pos_key]->tamano < minimo){
            Llenar(pos_key);
        }
        if (esta_noesta && pos_key > tamano){
            hijos[pos_key-1]->Remove(llave);
        }
        else{
            hijos[pos_key]->Remove(llave);
        }
    }
    return;
}

*Key BTreeNode::getPrev(int pos_key){
    BTreeNode *move=hijos[pos_key];
    while (!move->hoja){
        move = move->hijos[move->tamano];
 	}
    return move->llaves[move->tamano-1];
}

*Key BTreeNode::getNext(int pos_key){
    BTreeNode *move = hijos[pos_key+1];
    while (!move->hoja){
       move = move->hijos[0];
 	}
    return move->llaves[0];
}

void BTreeNode::Llenar(int pos_key){
    if (pos_key!=0 && hijos[pos_key-1]->tamano>=minimo){
        PrestadoPrev(pos_key);
    }else if (pos_key!=tamano && hijos[pos_key+1]->tamano>=minimo){
        PrestadoNext(pos_key);
 	}else{
        if (pos_key != tamano){
            merge(pos_key);
        }
        else{
            merge(pos_key-1);
        }
    }
    return;
}

void BTreeNode::PrestadoPrev(int pos_key)
{
    BTreeNode *hijo=hijos[pos_key],*hermano=hijos[pos_key-1];
    for (int i=hijo->tamano-1; i>=0; --i){
        hijo->llaves[i+1] = hijo->llaves[i];
 	}
 	if (!hijo->hoja){
        for(int i=hijo->tamano; i>=0; --i){
            hijo->hijos[i+1] = hijo->hijos[i];
        }
    }
    hijo->llaves[0]=llaves[pos_key-1];
    if (!hoja){
        hijo->hijos[0]=hermano->hijos[hermano->tamano];
 	}
    llaves[pos_key-1]=hermano->llaves[hermano->tamano-1];
 	hijo->tamano+=1;
    hermano->tamano-=1;
    return;
}

void BTreeNode::PrestadoNext(int pos_key){
 
    BTreeNode *hijo=hijos[pos_key],*hermano=hijos[pos_key+1];
    hijo->llaves[(hijo->tamano)] = llaves[pos_key];
    if (!(hijo->hoja)){
        hijo->hijos[(hijo->tamano)+1] = hermano->hijos[0];
 	}
    llaves[key] = hermano->llaves[0];
    for (int i=1; i<hermano->tamano; ++i){
        hermano->llaves[i-1] = heramno->llaves[i];
 	}
    if (!heramno->hoja){
        for(int i=1; i<=hermano->tamano; ++i){
            heramno->hijos[i-1]=hermano->hijos[i];
        }
    }
    hijo->tamano+=1;
    hermano->tamano-=1;
    return;
}

void BTreeNode::Merge(int pos_key){
    BTreeNode *hijo = hijos[pos_key],*hermano = hijos[pos_key+1];
    hijo->llaves[minimo-1] = llaves[pos_key];
    for (int i=0; i<hermano->tamano; ++i){
        hijo->llaves[i+minimo] = hermano->llaves[i];
 	}
    if (!hijo->hoja){
        for(int i=0; i<=hermano->tamano; ++i){
            hijo->hijos[i+minimo] = hermano->hijos[i];
        }
    }
    for (int i=pos_key+1; i<tamano; ++i){
        llaves[i-1] = llaves[i];
 	}
    for (int i=pos_key+2; i<=tamano; ++i){
        hijos[i-1] = hijos[i];
 	}
    hijo->tamano+=hermano->tamano+1;
    n--;
    delete(hermano);
    return;
}