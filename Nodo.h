#pragma once
#include <iostream>
#include <string>
using namespace std;

struct NodoRedirect {
	string link;
	NodoRedirect *siguiente;
	NodoRedirect(){
		siguiente = nullptr;
	}
	NodoRedirect (string _link,NodoRedirect *_siguiente) {
		this->link = _link;
		this->siguiente = _siguiente;
	}
};

struct NodoPagina {
	string link;
	double Pr;
	double Cantidad;
	NodoPagina *abajo;
	NodoRedirect *siguiente;
	NodoPagina (){
		abajo = nullptr;
		siguiente = nullptr;
		Pr = 0;
		Cantidad = 0;
	}
	bool operator() (NodoPagina* i,NodoPagina *j) {
		return (i->Pr < j->Pr); 
	}
	NodoPagina(double _Pr,string _link,NodoPagina*_abajo,NodoRedirect*_siguiente,double cantidad){
		this->Cantidad = cantidad;
		this->Pr = _Pr;
		this->link = _link;
		this->abajo = _abajo;
		this->siguiente = _siguiente;
	}
}; 


