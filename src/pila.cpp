/* 5256715 */

#include "../include/pila.h"
#include "../include/cadena.h"
#include "../include/producto.h"

struct _rep_pila {
  TCadena pila;
  nat cantidad;
};

/*
  Devuelve una TPila vacía (sin elementos).
  El tiempo de ejecución debe ser O(1).
 */
TPila crearPila() {
  TPila nuevaPila = new _rep_pila;
  nuevaPila->pila= crearCadena();
  nuevaPila->cantidad=0;
  return nuevaPila; 
}

/*
  Libera la memoria asignada a 'p' si la pila no contiene elementos.
  El tiempo de ejecución debe ser O(1), siendo 'n' la cantidad de elementos de
  'p'.
 */
void liberarPila(TPila p) {
  if(p!=NULL){
    if(cantidadEnPila(p)==0 ) {
      delete p;
      p=NULL;
    }
  }
}


/*
  Devuelve la cantidad de elementos de 'p'.
  El tiempo de ejecución debe ser O(1).
 */
nat cantidadEnPila(TPila p) {
  if(p!=NULL) return p->cantidad;
  else return 0;
}

/*
  Apila 'info' en 'p'-
  Devuelve 'p'.
  La TPila resultado no comparte memoria con 'info'.
  El tiempo de ejecución debe ser O(1).
 */
TPila apilar(Producto dato, TPila p) {
  p->pila=insertarAlInicio(p->pila,dato);
  p->cantidad+=1;
  return p;
}

/*
  Devuelve el elemento más nuevo en 'p'.
  Precondición: cantidadEnPila(p) > 0.
  El tiempo de ejecución debe ser O(1).
 */
Producto cima(TPila p) {
  return datoCadena(p->pila); 
}

/*
  Remueve de 'p' su elemento más nuevo.
  Se libera la memoria asignada utilizada por la pila para almacenarlo.
  Devuelve 'p'.
  Precondición: cantidadEnPila(p) > 0.
  El tiempo de ejecución debe ser O(1).
 */
TPila desapilar(TPila p) {
  removerPrimero(p->pila);
  p->cantidad-=1;
  return p; 
}
