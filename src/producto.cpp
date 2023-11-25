/* 5256715 */
/*
  Módulo de implementacion de 'Producto'.

  Los elementos de tipo 'Producto' son punteros a una estructura (que debe
  definirse en producto.cpp).

  Laboratorio de Programación 2 2do semestre 2022.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/fecha.h"
#include "../include/producto.h"
#include "../include/lista.h"
//#include "../include/vencimiento.h"

// Representación de 'Producto'.
// Se debe definir en producto.cpp.
// struct _rep_producto;
// Declaración del tipo 'Producto'.
struct _rep_producto{
	nat id;
	char* nombre;
	nat cantidadUnidades;
	TLista unidades;
};

/* Operaciones de producto */

/*
  Devuelve un 'producto'.
 */
Producto crearProducto(nat identificadorDeProducto, char* nombre){ 
  Producto producto = new _rep_producto;
  producto->id=identificadorDeProducto;
  producto->nombre = copiarCadenaChar(nombre);
  producto->cantidadUnidades = 0;
  producto->unidades = crearLista();
  return producto;
  }

/*
  Libera la memoria reservada por 'producto'.
 */
void liberarProducto(Producto producto){
  //delete char[strlen(producto->nombre)+1];
  delete [] (producto->nombre) ;
  producto->cantidadUnidades=0;
  liberarLista(producto->unidades);
  delete producto;
  producto=NULL;
}

/*
  Devuelve la cantidad de unidades 'producto'.
 */
nat obtenerCantidad(Producto producto){ 
  return producto->cantidadUnidades; 
}

/*
  Devuelve el identificador de producto de 'producto'.
 */
nat obtenerIdentificadorDeProducto(Producto producto){
  //if (producto!= NULL)
    return producto->id; 
  //else return 0;
}

/*
    Agrega cantidad elementos a la unidad.
    Pre: cantidad y f_venc deben ser mayores a cero. 
 */
void agregarUnidades(Producto producto, nat cantidad, TFecha f_venc){
  producto->cantidadUnidades+=cantidad;
  producto->unidades = agregarAListaOrdenado(producto->unidades,f_venc,cantidad);
} 

/*
    Quita cantidad elementos al producto con fecha de vencimiento más
    próxima.
    Pre: cantidad debe ser mayor a cero.  
 */
void quitarUnidades(Producto producto, nat cantidad){  //si la cantidad es mayor a cantUnid borro todas las fechas y dejo 0 en unidad
  if(producto!=NULL){
    if(obtenerCantidad(producto)<=cantidad){
    producto->cantidadUnidades=0;
    liberarLista(producto->unidades);
    producto->unidades=NULL;
    }else {
    producto->cantidadUnidades-=cantidad;
    producto->unidades=quitarDeLista(producto->unidades,cantidad);
  }

  /*if ( producto->cantidadUnidades-cantidad < 0 ) {  //Si la fecha no tiene cant libero la memoria
    producto->cantidadUnidades=0;
  }else {
    producto->cantidadUnidades-=cantidad;
  }
  quitarDeLista(producto->unidades,cantidad); */

  }
} 

/*
    Quita todas las unidades de productos cuya fecha de vencimiento es menor igual a
    la fecha actual.  
 */
void quitarVencidos(Producto producto, TFecha fecha){
  if(producto!=NULL && !esVaciaLista(producto->unidades) ){
    //TLista unidad = (producto->unidades) ;
    Vencimiento borrar = obtenerMasViejo(producto->unidades);
    TFecha fVenc = obtenerFVencimiento(borrar);
    while( !esVaciaLista(producto->unidades) && (  compararFechas(fecha,fVenc) != -1 )
     ) {    //Si venc es menor igual a fecha 
      producto->cantidadUnidades -= obtenerCantidad(borrar); //quito unidades al producto
      producto->unidades=quitarMasViejo(producto->unidades); //Saco el venc de la lista (muevo al sig) y libero vencimiento
      liberarVencimiento(borrar);
      if(!esVaciaLista(producto->unidades) ){
        borrar = obtenerMasViejo(producto->unidades); //Obtengo el venc a borrar
        fVenc = obtenerFVencimiento(borrar);
      }
    }
  }  
} 

/*
  Imprime los datos del producto en el formato específicado en la letra.
 */
void imprimirProducto(Producto producto){
  printf("Información del producto %d - %s\n", obtenerIdentificadorDeProducto(producto), producto->nombre);
  printf("Total de unidades: %d\n", obtenerCantidad(producto));
  if(obtenerCantidad(producto) > 0) imprimirInfoLista(producto->unidades);
} 
