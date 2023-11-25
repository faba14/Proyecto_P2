/* 5256715 */

/*
  Módulo de definición de 'TLista'.

  Los elementos de tipo TLista son Listas de elementos de tipo TFecha.

  Laboratorio de Programación 2.
  InCo-FIng-UDELAR
 */

#include "../include/utils.h"
#include "../include/lista.h"
#include "../include/vencimiento.h"
#include "../include/fecha.h"

// Representación de 'TLista'.
// Se debe definir en Lista.cpp.
// Declaración del tipo 'TLista'
struct _rep_lista{
  _rep_lista* sig;
  Vencimiento ven;
};

// Que sentido tiene esta funcion?
/*
  Devuelve una TLista vacía (sin elementos).
  El tiempo de ejecución debe ser O(1).
 */
TLista crearLista(){
  return NULL;
}

/*
  Libera la memoria asignada a la TLista 'p' y la de todos sus elementos.
  El tiempo de ejecución debe ser O(n), siendo 'n' la cantidad de elementos de la TLista
  'p'.
 */
void liberarLista(TLista p){
  while(p!=NULL){
    TLista borrar=p;
    p=p->sig;
    liberarVencimiento(borrar->ven);
    delete borrar;
  }
}

/*
  Devuelve true si la TLista 'p' es vacia.
  El tiempo de ejecución debe ser O(1).
 */
bool esVaciaLista(TLista p){
  return p==NULL; 
}

/*
  Devuelve 'p' con un nuevo vencimiento insertado en caso de que no exista la fecha
  en la lista. Si ya existe un vencimiento con f_venc se le aumenta cantidad a dicho elemento.
  En caso de crear un nuevo vencimiento, la fecha utilizada al crearlo no debe 
  compartir memoria con 'f_venc' que se pasa por parámetro. 
  El tiempo de ejecución debe ser O(n).
 */
TLista agregarAListaOrdenado(TLista p,TFecha f_venc,nat cantidad){
    TLista aux;
    if(p==NULL){
        aux = new _rep_lista;
        aux->ven=crearVencimiento(f_venc,cantidad);
        aux->sig=p;
        p=aux;
        return p;
    }else{        
        TFecha fecha=obtenerFVencimiento(p->ven);
        if(compararFechas(fecha,f_venc)==0){ //Si son iguales agrego unidades
            agregarUnidades(p->ven,cantidad);
            return p;
        }else if(compararFechas(fecha,f_venc)==1){  //Si f_venc<fecha inserto al ppio
            aux = new _rep_lista;
            aux->ven=crearVencimiento(f_venc,cantidad);
            aux->sig=p;
            p=aux;            
            return p;
        }else if(compararFechas(fecha,f_venc)==-1 && p->sig==NULL){//Si el sig es null y f_venc>fecha inserto al final
            aux = new _rep_lista;
            aux->ven=crearVencimiento(f_venc,cantidad);
            aux->sig=NULL;
            p->sig=aux;    
            return p;
        }else if(compararFechas(fecha,f_venc)==-1 && p->sig!=NULL){
            p->sig=agregarAListaOrdenado(p->sig,f_venc,cantidad);
        }
    } return p;
}

/*
  Devuelve el elemento en 'p' con menor fecha de vencimiento de la lista.
  Precondición: cantidadEnLista(p) > 0.
  El tiempo de ejecución debe ser O(1).
 */
Vencimiento obtenerMasViejo(TLista p){
  return p->ven;
}

/*	
	Quita de la lista 'p' al elemento con la menor fecha de vencimiento.
	Pre: la lista tiene al menos un elemento.
*/
TLista quitarMasViejo(TLista p){
  TLista viejo=p;
  p=p->sig;  
  //liberarVencimiento(viejo->ven);
  delete viejo;
  return p; 
}

/*
Elimina 'cantidad' de unidades de la lista de vencimientos. 
Las unidades se eliminan según la fecha de vencimiento de menor a mayor fecha.
Si 'cantidad' es mayor que la cantidad de unidades sumadas que hay en la lista, 
entonces se deben eliminar todos los elementos de la lista. 
*/
TLista quitarDeLista(TLista p, nat cantidad){
  nat cantElim=0;
  //TLista aux;
  while( (cantElim < cantidad) && p!=NULL){
    if( (cantidad-cantElim) >= obtenerCantidad(p->ven) ){
      cantElim+= obtenerCantidad(p->ven);
      Vencimiento venc=obtenerMasViejo(p);
      p=quitarMasViejo(p);
      liberarVencimiento(venc);
    }else {
      quitarUnidades( p->ven , (cantidad-cantElim) );
      cantElim+= obtenerCantidad(p->ven);
    }
  }
  return p; 
}

/*  
    Imprime información de la lista en el formato siguiente: 
	%Fecha vencimiento% -> %cantidad unidades%
	%Fecha vencimiento% -> %cantidad unidades%
	%Fecha vencimiento% -> %cantidad unidades%
*/
void imprimirInfoLista(TLista p){
  TLista aux = p;
  while(aux!=NULL){
    imprimirVencimiento(obtenerMasViejo(aux));
    aux=aux->sig;
  }
}

