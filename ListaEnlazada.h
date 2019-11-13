#pragma once
#include "Nodo.h"
#include <vector>
#include <array>
using namespace std;
#ifndef LISTAENLAZADA_H
#define LISTAENLAZADA_H
class ListaEnlazada {
private:
	array<double,20>valores;
	NodoPagina*primero;
	NodoRedirect* abajo;
	string name;
	bool exis = true;
	bool guardar = true;
	bool activo = true;
	int cantHREF = 0;
	int contador = 0;
public:
	ListaEnlazada (string);
	ListaEnlazada(void);
	bool estaVacia(void);
	void Anadir(string);
	double calcularPR (double,float);
	vector<string> calcularRef (NodoPagina *,vector<string>&);
	void ImprimirPR (string);
	void AjustarPR (NodoPagina *page,vector<string>&,int,int);
	void LimpiarPr ();
};
#endif // !NODO_H
