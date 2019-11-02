#pragma once
#include "Nodo.h"
#include <vector>
#include <array>
using namespace std;
#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
class ListaEnlazada {
private:
	NodoPagina*primero;
	NodoRedirect* abajo;
	string name;
	bool guardar = true;
	bool activo = true;
	bool avanzar = true;
	bool cerrar = true;
	int cantHREF = 0;
	int contador = 0;
	int pos = 0;

public:
	~ListaEnlazada ();
	ListaEnlazada(void);
	bool estaVacia(void);
	void Anadir(string);
	double calcularPR (int,double,float);
	void ImprimirLista();
	vector<string> calcularRef (NodoPagina *,vector<string>&);
	void ImprimirPR ();
	void AjustarPR (NodoPagina *page,vector<string>&,int,int);
	void LimpiarPr ();
};
#endif // !NODO_H


/*void ListaEnlazada::Anadir (string Nombre) {
	NodoPagina *nuevo = new NodoPagina (Nombre,nullptr,nullptr);
	NodoRedirect *_nuevo = new NodoRedirect (Nombre,nullptr);
	Archivo a;
	if(activo) {
		if(estaVacia ()) {
			cantHREF = a.cantidadHREF (Nombre);
		} else {
			cantHREF = a.cantidadHREF (name);
		}
		activo = false;
	}

	if(estaVacia ()) {
		contador++;
		abajo = nuevo;
		siguiente = _nuevo;
	} else {
		if(contador < cantHREF) {
			NodoRedirect *actual = siguiente;
			while(actual->siguiente != nullptr) {
				actual = actual->siguiente;
			}
			actual->siguiente = _nuevo;
			contador++;
		} else {
			NodoPagina *actual = abajo;
			while(actual->abajo != nullptr) {
				actual = actual->abajo;
			}
			actual->abajo = nuevo;
			abajo = actual->abajo;
			name = nuevo->link;
			contador = 0;
			contador++;
			activo = true;
		}
	}
}*/