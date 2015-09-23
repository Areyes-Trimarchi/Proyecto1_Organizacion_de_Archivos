#include "b-treenode.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

ostream& operator<<(ostream& output, const Key& key){
    output << key.llave;
    return output;
}

ostream& operator<<(ostream& output, const KeyChar& key){
    output << key.llave;
    return output;
}

BTreeNode::BTreeNode(bool hoja, int ordenArbol){
	this->hoja = hoja;

	this->tamano = 0;
	this->minimo = (ordenArbol/2)-1;
	this->maximo = ordenArbol - 1;
	this->llaves =  new Key[ordenArbol-1];
    this->llavesChar =  new KeyChar[ordenArbol-1];
	this->hijos = new BTreeNode *[ordenArbol];
}

BTreeNode::~BTreeNode(){

}

bool BTreeNode::insert(Key llave){
    int i = this->tamano - 1;
 
    if (hoja == true){                                      //Si es hoja solo se busca la posicion a insertar
        while (i >= 0 && llaves[i].llave > llave.llave) {
            llaves[i+1] = llaves[i];                        //Por mientras se busca la posicion exacta se mueven las llaves
            i--;
        }
        if (llaves[i+1].llave == llave.llave)
            return false;
        llaves[i+1] = llave;                                //Se inserta en la posicion exacta ya que i termina en el ciclo en la posicion antes
        tamano = tamano+1;
    } else {                                                //Si no es hoja
        while (i >= 0 && llaves[i].llave > llave.llave)     //Busca la posicion del hijo que tendra la llave
            i--;
 
        if (hijos[i+1]->tamano == hijos[i+1]->maximo) {     //Comprueba si el hijo no tiene el tamano maximo
            split(i+1, hijos[i+1]); 
 
            if (llaves[i+1].llave < llave.llave)            //Busca cual de las dos hojas que se acaban de splitear tendran al hijo
                i++;
        }
        hijos[i+1]->insert(llave);
    }
    return true;
}

bool BTreeNode::insert(KeyChar llave){
    int i = this->tamano - 1;
    if (hoja == true){                                      //Si es hoja solo se busca la posicion a insertar
        while (i >= 0 && (strncmp(llavesChar[i].llave, llave.llave, 14) > 0) ) {
            llavesChar[i+1] = llavesChar[i];                        //Por mientras se busca la posicion exacta se mueven las llaves
            i--;
        }
        if (llavesChar[i+1].llave == llave.llave)
            return false;
        llavesChar[i+1] = llave;                                //Se inserta en la posicion exacta ya que i termina en el ciclo en la posicion antes
        tamano = tamano+1;
    } else {                                                //Si no es hoja
        while (i >= 0 && (strncmp(llavesChar[i].llave, llave.llave, 14) > 0) )      //Busca la posicion del hijo que tendra la llave
            i--;
 
        if (hijos[i+1]->tamano == hijos[i+1]->maximo) {     //Comprueba si el hijo no tiene el tamano maximo
            split(i+1, hijos[i+1]); 
 
            if (strncmp(llavesChar[i+1].llave, llave.llave, 14) < 0)            //Busca cual de las dos hojas que se acaban de splitear tendran al hijo
                i++;
        }
        hijos[i+1]->insert(llave);
    }
    return true;
}

void BTreeNode::split(int pos, BTreeNode* node){
    BTreeNode* neo = new BTreeNode(node->hoja, node->maximo+1); //creacion del nuevo nodo
    neo->tamano = minimo;                                       //
 
    for (int i = 0; i < minimo; i++)
        neo->llaves[i] = node->llaves[i+minimo+1];              //Copiando las ultimas llaves del nodo mayores de la mitad
 
    if (node->hoja == false){
        for (int i = 0; i < minimo+1; i++)
            neo->hijos[i] = node->hijos[i+minimo+1];            //Copiando los ultimos hijos del nodo mayores de la mitad
    }
    node->tamano = minimo;                                      //se le asigna el tamano minimo al nodo a splitear
 
    for (int i = tamano; i >= pos+1; i--)
        hijos[i+1] = hijos[i];                                  //Copiando los primeros hijos del nodo menores de la mitad
 
    hijos[pos+1] = neo;                                         //Poniendo el nuevo nodo que contiene los mayores de ultimo lugar de hijos del nodo padre
 
    for (int j = tamano-1; j >= pos; j--)
        llaves[j+1] = llaves[j];                                //Moviendo las posiciones de las llaves para hacer espacio para la llave que sera promovida
 
    llaves[pos] = node->llaves[minimo];                         //Poniendo la llave promovida en la posicion necesaria
 
    tamano = tamano + 1;        
}

BTreeNode* BTreeNode::busqueda(int llaveBusqueda){
    int posicion = 0;
    while (posicion < tamano && llaveBusqueda > llaves[posicion].llave)
        posicion++;

    if (llaves[posicion].llave == llaveBusqueda)
        return this;
    if (hoja == true)
        return NULL;
    return hijos[posicion]->busqueda(llaveBusqueda);
}

BTreeNode* BTreeNode::busqueda(char * llaveBusqueda){
    int posicion = 0;
    cout << "llaveBusqueda = " << llaveBusqueda << "\tkey = " << llavesChar[posicion].llave << endl;
    while (posicion < tamano && (strncmp(llaveBusqueda,llavesChar[posicion].llave, 14) > 0 ) )
        posicion++;

    if (strncmp(llavesChar[posicion].llave, llaveBusqueda, 14) == 0 )
        return this;
    if (hoja == true)
        return NULL;
    return hijos[posicion]->busqueda(llaveBusqueda);
}

void BTreeNode::inorder(bool tipo) {
    int i;
    for (i = 0; i < tamano; i++){
        if (hoja == false){
            cout << "Hijo " << i << " ";
            hijos[i]->inorder(tipo);
        }
        if(tipo)
            cout << " " << llaves[i];
        else
            cout << " " << llavesChar[i];
    }
 
    if (hoja == false)
        hijos[i]->inorder(tipo);
}

int BTreeNode::LlaveExiste(Key llave){
    int pos_key=0;
    while (pos_key<tamano && llaves[pos_key].llave < llave.llave){
        ++pos_key;
    }
    return pos_key;
}

int BTreeNode::LlaveExiste(KeyChar llave){
    int pos_key=0;
    while (pos_key<tamano && strncmp(llavesChar[pos_key].llave,llave.llave,14)<0){
        ++pos_key;
    }
    return pos_key;
}

bool BTreeNode::Remove(Key llave){
    int pos_key = LlaveExiste(llave);
    if (pos_key < tamano && llaves[pos_key].llave== llave.llave){
        if (!hoja){//Remove cuando no es hoja
            Key tmp_llave = llaves[pos_key];
            if (hijos[pos_key]->tamano >= minimo){
                Key prev = getPrev(pos_key);
                llaves[pos_key]= prev;
                hijos[pos_key]->Remove(prev);
            }else if  (hijos[pos_key+1]->tamano >= minimo){
                Key next = getNext(pos_key);
                llaves[pos_key] = next;
                hijos[pos_key+1]->Remove(next);
            }else
            {
                Merge(pos_key);
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
            return false;
        }
        bool esta_noesta = ((pos_key==tamano)? true : false );
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
    return true;
}

bool BTreeNode::Remove(KeyChar llave){
    int pos_key = LlaveExiste(llave);
    if (pos_key < tamano && strncmp(llavesChar[pos_key].llave,llave.llave,14)==0){
        if (!hoja){//Remove cuando no es hoja
            KeyChar tmp_llave = llavesChar[pos_key];
            if (hijos[pos_key]->tamano >= minimo){
                KeyChar prev = GetPrev(pos_key);
                llavesChar[pos_key]= prev;
                hijos[pos_key]->Remove(prev);
            }else if  (hijos[pos_key+1]->tamano >= minimo){
                KeyChar next = GetNext(pos_key);
                llavesChar[pos_key] = next;
                hijos[pos_key+1]->Remove(next);
            }else
            {
                Merge(pos_key);
                hijos[pos_key]->Remove(tmp_llave);
            }   
        }else{//remove cuando es hoja
            for (int i=pos_key+1; i<tamano; ++i){
                llavesChar[i-1] = llavesChar[i];
            }
            tamano--;
        }    
    }else{
        if (hoja){
            cout << "La llave "<< llave <<" que usted ingreso no existe :(\n";
            return false;
        }
        bool esta_noesta = ((pos_key==tamano)? true : false );
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
    return true;
}

Key BTreeNode::getPrev(int pos_key){
    BTreeNode *move=hijos[pos_key];
    while (!move->hoja){
        move = move->hijos[move->tamano];
    }
    return move->llaves[move->tamano-1];
}

KeyChar BTreeNode::GetPrev(int pos_key){
    BTreeNode *move=hijos[pos_key];
    while (!move->hoja){
        move = move->hijos[move->tamano];
    }
    return move->llavesChar[move->tamano-1];
}

Key BTreeNode::getNext(int pos_key){
    BTreeNode *move = hijos[pos_key+1];
    while (!move->hoja){
       move = move->hijos[0];
    }
    return move->llaves[0];
}

KeyChar BTreeNode::GetNext(int pos_key){
    BTreeNode *move = hijos[pos_key+1];
    while (!move->hoja){
       move = move->hijos[0];
    }
    return move->llavesChar[0];
}

void BTreeNode::Llenar(int pos_key){
    if (pos_key!=0 && hijos[pos_key-1]->tamano>=minimo){
        PrestadoPrev(pos_key);
    }else if (pos_key!=tamano && hijos[pos_key+1]->tamano>=minimo){
        PrestadoNext(pos_key);
    }else{
        if (pos_key != tamano){
            Merge(pos_key);
        }
        else{
            Merge(pos_key-1);
        }
    }
    return;
}

void BTreeNode::LlenarChar(int pos_key){
    if (pos_key!=0 && hijos[pos_key-1]->tamano>=minimo){
        PrestadoPrevChar(pos_key);
    }else if (pos_key!=tamano && hijos[pos_key+1]->tamano>=minimo){
        PrestadoNextChar(pos_key);
    }else{
        if (pos_key != tamano){
            MergeChar(pos_key);
        }
        else{
            MergeChar(pos_key-1);
        }
    }
    return;
}

void BTreeNode::PrestadoPrev(int pos_key){
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

void BTreeNode::PrestadoPrevChar(int pos_key){
    BTreeNode *hijo=hijos[pos_key],*hermano=hijos[pos_key-1];
    for (int i=hijo->tamano-1; i>=0; --i){
        hijo->llavesChar[i+1] = hijo->llavesChar[i];
    }
    if (!hijo->hoja){
        for(int i=hijo->tamano; i>=0; --i){
            hijo->hijos[i+1] = hijo->hijos[i];
        }
    }
    hijo->llavesChar[0]=llavesChar[pos_key-1];
    if (!hoja){
        hijo->hijos[0]=hermano->hijos[hermano->tamano];
    }
    llavesChar[pos_key-1]=hermano->llavesChar[hermano->tamano-1];
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
    llaves[pos_key] = hermano->llaves[0];
    for (int i=1; i<hermano->tamano; ++i){
        hermano->llaves[i-1] = hermano->llaves[i];
    }
    if (!hermano->hoja){
        for(int i=1; i<=hermano->tamano; ++i){
            hermano->hijos[i-1]=hermano->hijos[i];
        }
    }
    hijo->tamano+=1;
    hermano->tamano-=1;
    return;
}

void BTreeNode::PrestadoNextChar(int pos_key){
 
    BTreeNode *hijo=hijos[pos_key],*hermano=hijos[pos_key+1];
    hijo->llavesChar[(hijo->tamano)] = llavesChar[pos_key];
    if (!(hijo->hoja)){
        hijo->hijos[(hijo->tamano)+1] = hermano->hijos[0];
    }
    llavesChar[pos_key] = hermano->llavesChar[0];
    for (int i=1; i<hermano->tamano; ++i){
        hermano->llavesChar[i-1] = hermano->llavesChar[i];
    }
    if (!hermano->hoja){
        for(int i=1; i<=hermano->tamano; ++i){
            hermano->hijos[i-1]=hermano->hijos[i];
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
    tamano--;
    delete(hermano);
    return;
}

void BTreeNode::MergeChar(int pos_key){
    BTreeNode *hijo = hijos[pos_key],*hermano = hijos[pos_key+1];
    hijo->llavesChar[minimo-1] = llavesChar[pos_key];
    for (int i=0; i<hermano->tamano; ++i){
        hijo->llavesChar[i+minimo] = hermano->llavesChar[i];
    }
    if (!hijo->hoja){
        for(int i=0; i<=hermano->tamano; ++i){
            hijo->hijos[i+minimo] = hermano->hijos[i];
        }
    }
    for (int i=pos_key+1; i<tamano; ++i){
        llavesChar[i-1] = llavesChar[i];
    }
    for (int i=pos_key+2; i<=tamano; ++i){
        hijos[i-1] = hijos[i];
    }
    hijo->tamano+=hermano->tamano+1;
    tamano--;
    delete(hermano);
    return;
}