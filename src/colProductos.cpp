/* 5256715 */

/*
  Módulo de implementación de 'ColProductos'.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/producto.h"
#include "../include/pila.h"
#include "../include/utils.h"
#include "../include/colProductos.h"

// Representación de 'ColProductos'.
// Declaración del tipo 'TColProductos'
struct rep_colproductos{
  Producto prod;
  rep_colproductos *izq, *der;
};

/*
  Devuelve un 'ColProductos' vacío (sin elementos).
  El tiempo de ejecución debe ser O(1).
 */
TColProductos crearColProductos(){ return NULL; }

/*
  Libera la memoria asociada a 'colProd' pero no la de sus productos.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de
  'colProd'.
 */
void liberarColProductos(TColProductos colProd){
  if(colProd!=NULL){
    liberarColProductos(colProd->izq);
    liberarColProductos(colProd->der);
    delete colProd;
    colProd = NULL;
  }
}

/*
Devuelve true si existe un Producto con identificador 'idProd'.
En caso contrario devuelve false.
El tiempo de ejecución debe ser O(log(n)).
*/
bool existeProductoEnColProductos(nat idProd, TColProductos colProd){ 
  if(colProd!=NULL){
    nat id = obtenerIdentificadorDeProducto(colProd->prod);
    if(idProd>id) return existeProductoEnColProductos(idProd,colProd->der);
    else if (idProd<id) return existeProductoEnColProductos(idProd,colProd->izq);
    else if (idProd==id) return true;
    else return false;
  }
  else return false;
  //return false;
}

/*
  Devuelve el Producto cuyo componente natural es 'idProd'.
  Si 'idProd' no pertenece a 'colProd', devuelve NULL.
  El tiempo de ejecución debe ser O(log(n)).
 */
Producto buscarProductoEnColProductos(nat idProd, TColProductos colProd){
  if(colProd!=NULL && existeProductoEnColProductos(idProd,colProd) ){
    nat id = obtenerIdentificadorDeProducto(colProd->prod);
    if(idProd>id) return buscarProductoEnColProductos(idProd,colProd->der);
    else if (idProd<id) return buscarProductoEnColProductos(idProd,colProd->izq);
    else if (idProd==id) return (colProd->prod);
  }else return NULL;
  return NULL;
}

/*
  Inserta 'dato' en 'colProd'. 
  Precondición: !existeProductoEnColProductos()
  El tiempo de ejecución debe ser O(log(n))
 */
TColProductos insertarEnColProductos(Producto dato, TColProductos colProd){ //Ni idea de lo que hace esto 
  if(colProd!=NULL){
    nat id = obtenerIdentificadorDeProducto(colProd->prod);
    nat idProd = obtenerIdentificadorDeProducto(dato);
    if ( idProd > id ) colProd->der = insertarEnColProductos(dato,colProd->der);
    else if ( idProd < id) colProd->izq = insertarEnColProductos(dato,colProd->izq);
  }
  else { 
    TColProductos nuevo = new rep_colproductos;
    nuevo->prod = dato;
    nuevo->der = NULL;
    nuevo->izq = NULL;
    return nuevo;
  }
  return colProd;
}

Producto maxABB(TColProductos colProd){
  TColProductos aux = colProd;
  while(aux->der!=NULL) aux=aux->der;
  return aux->prod;
}
void removerMaxABB(TColProductos &colProd){
  if(colProd!=NULL){
   if(colProd->der==NULL){
    TColProductos aux = colProd;
    colProd->prod=NULL;
    colProd=colProd->izq;
    delete aux;
  }else removerMaxABB(colProd->der);
  }
}
/*
  Remueve de 'colProd' el elemento con identificador idProd.
  Devuelve 'colProd'.
  Precondición: existeProductoEnColProductos()
  El tiempo de ejecución debe ser O(log(n))
*/
TColProductos removerDeColProductos(nat idProd, TColProductos colProd){ 
  if(colProd!=NULL){
    nat id = obtenerIdentificadorDeProducto(colProd->prod);
    if(id==idProd){
      if(colProd->izq!=NULL){
        Producto prod= colProd->prod; //buscarProductoEnColProductos(idProd,colProd);
        colProd->prod=maxABB(colProd->izq);
        removerMaxABB(colProd->izq);
        liberarProducto(prod);
        return colProd;
      }else {
        TColProductos aux = colProd;
        Producto prod= buscarProductoEnColProductos(idProd,colProd);
        colProd=colProd->der;
        liberarProducto(prod);
        delete aux;
        return colProd;
      }
    } else if ( idProd > id ) colProd->der = removerDeColProductos(idProd,colProd->der);
    else if ( idProd < id ) colProd->izq = removerDeColProductos(idProd,colProd->izq);
    else return colProd;
  }else return colProd;
  return colProd;
}

/*
  Devuelve una pila con los elementos de la colección ordenados por identificador
  de menor a mayor.
*/

TPila apilarRec(TPila p,TColProductos col){
  if(col!=NULL){
    p=apilarRec(p,col->izq);
    p=apilar(col->prod,p);
    p=apilarRec(p,col->der);
  }
  return p;
}
TPila colProdAPila(TColProductos colProd){ //Recorro en postOrden 1ero der y dsps izq 
  TPila pila=crearPila();
  pila=apilarRec(pila,colProd);
  return pila;
}
