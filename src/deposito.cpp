/* 5256715 */

/*
  Módulo de definición de 'Deposito'.

  Los elementos de tipo 'Deposito' son punteros a una estructura (que debe
  definirse en deposito.cpp).

  Laboratorio de Programación 2 2do semestre 2022.
  InCo-FIng-UDELAR
 */

#include "../include/deposito.h"
#include "../include/fecha.h"
#include "../include/colProductos.h"
#include "../include/pila.h"
#include "../include/producto.h"

// Representación de 'Deposito'.
// Se debe definir en deposito.cpp.
// struct _rep_deposito;
// Declaración del tipo 'Deposito'.
struct _rep_deposito{
	TColProductos productos;
};

/* Operaciones de deposito */

/*
  Devuelve un 'deposito'.
 */
TDeposito crearDeposito() {
  TDeposito deposito = new _rep_deposito;
  deposito->productos = crearColProductos();
  return deposito;
}

/*
  Libera la memoria reservada por 'deposito' y de todos sus elementos.
 */
void liberarDeposito(TDeposito deposito) {
  if(deposito!=NULL){
    TPila prods = colProdAPila(deposito->productos);
    liberarColProductos(deposito->productos);
    while(cantidadEnPila(prods)>0 ){
      Producto prod = cima(prods);
      liberarProducto(prod);
      prods = desapilar(prods);
    }
    liberarPila(prods);
    delete deposito;
    deposito = NULL;
  }
}

/*
  Devuelve las unidades del producto con identificador 'identificador'
  en el deposito 'deposito'. O(log(n))
 */
nat obtenerCantidadUnidades(TDeposito deposito, int identificador){ 
  Producto producto=buscarProductoEnColProductos(identificador,deposito->productos);
  if( producto != NULL)
    return obtenerCantidad(producto);
  else return 0; 
}

/*
  Agrega un producto al depósito con el identificador y el nombre que se pasan como parametros. O(log(n))
  Pre: !existeProducto(). 
 */
void agregarProducto(TDeposito deposito, nat identificador, char* nombre){
    Producto producto = crearProducto(identificador,nombre);
    deposito->productos=insertarEnColProductos(producto,deposito->productos);
}

/*
  Devuelve true si existe un producto con identificador 'identificador'. O(log(n))
*/
bool existeProducto(TDeposito deposito, nat identificador){ 
  return existeProductoEnColProductos(identificador,deposito->productos); 
  }

/*
  Quita del depósito todas las unidades que tengan fecha de vencimiento anterior 
  o igual a la fecha pasada como parámetro.
*/
void quitarVencidosDeposito(TDeposito deposito, TFecha fecha){ //recorrer todo el arbol y comparar las fechas de los productos
  TPila pila = colProdAPila(deposito->productos);
  while( cantidadEnPila(pila)>0 ){
    Producto prod = cima(pila);
    quitarVencidos(prod,fecha);
    pila=desapilar(pila);
  }
  liberarPila(pila);
}

/*
  Agrega cantidad unidades con fecha de vencimiento fVenc al producto de identificador
  'identificador'.
  Pre: existeProducto().
*/
void agregarUnidades(TDeposito deposito, nat identificador, nat cantidad, TFecha fVenc){
  Producto producto = buscarProductoEnColProductos(identificador,deposito->productos);
  agregarUnidades(producto,cantidad,fVenc);
}

/*
    Quita cantidad elementos al producto con identificador 'identificador'.
    Se quitan los elementos con fecha de vencimiento más próxima.
    Pueden existir productos con cantidad 0 pero no con cantidad menor a cero.
    Pre: existeProducto() && obtenerCantidadUnidades() >= cantidad.
*/
void quitarUnidades(TDeposito deposito, nat identificador, nat cantidad){
  Producto producto = buscarProductoEnColProductos(identificador,deposito->productos);
  if(cantidad>=0) quitarUnidades(producto,cantidad);
}

/*
    Si el producto existe, entonces lo elimina. También se deben eliminar todas 
    las unidades del producto. 
*/
void eliminarProducto(TDeposito deposito, nat identificador){
  if(existeProductoEnColProductos(identificador,deposito->productos)){
    //Producto producto = buscarProductoEnColProductos(identificador,deposito->productos);
    deposito->productos = removerDeColProductos(identificador,deposito->productos);
    //liberarProducto(producto);
  }
}

/*
  Se debe imprimir el resumen del depósito de la forma que está aclarada en
  el archivo de especificación gestionDeposito.h
*/
void imprimirResumenDeposito(TDeposito deposito) {
  if(deposito!=NULL){
    TPila pila = colProdAPila(deposito->productos);
    while( cantidadEnPila(pila) > 0 ){
      Producto prod = cima(pila);
      imprimirProducto(prod);
      desapilar(pila);
    }
    liberarPila(pila);
    pila=NULL;
    /*
    Producto producto = deposito->productos->prod;
    imprimirProducto(producto);
    imprimirResumenDeposito(deposito->productos->der);
    imprimirResumenDeposito(deposito->productos->izq);  */
  }  
}

/*
  Imprime los datos del producto en el formato específicado en la letra. O(log(n))
  Pre: existeProducto() 
 */
void imprimirProducto(TDeposito deposito, int identificador){
  Producto producto = buscarProductoEnColProductos(identificador,deposito->productos);
  imprimirProducto(producto);
}
