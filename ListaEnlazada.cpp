#include "ListaEnlazada.h"
#include "Archivo.h"
#include <iostream>
#include "Archivo.h"
#include <fstream>
#include <algorithm>
using namespace std;

ListaEnlazada::ListaEnlazada (void):abajo (nullptr),primero (nullptr) {}

ListaEnlazada::ListaEnlazada (string pagina) {
	bool abrir = false;
	Archivo a;
	vector<string>lista;
	vector<string>lista3;
	vector<string>TotalCoincidencia;
	ListaEnlazada ls;
	//cout << "Palabra: " << argv[1] << endl;
	lista = a.extraerPaginas (pagina);
	for(int i = 0; i < lista.size (); i++) {
		a.LeerArchivo (lista[i],lista3,0,a.cantidadHREF (lista[i]));
		abrir = true;
	}
	if(abrir) {
		a.eiminarDuplicados (lista[0],0,ls);
		ls.calcularRef (nullptr,TotalCoincidencia);
		ls.AjustarPR (nullptr,TotalCoincidencia,0,0);
		cout << "<h1>\t\tPAGERANK </h1>" << endl;
		ls.ImprimirPR (pagina);
	}
}
bool ListaEnlazada::estaVacia () {
	return abajo == nullptr;
}

void ListaEnlazada::Anadir (string Nombre) {
	NodoPagina *nuevo = new NodoPagina (0,Nombre,nullptr,nullptr,0);
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
		primero = nuevo;
		abajo = (NodoRedirect *)nuevo;
	} else {
		if(contador < cantHREF) {
			NodoRedirect *actual = abajo;
			while(actual->siguiente != nullptr) {
				actual = actual->siguiente;
			}
			actual->siguiente = (NodoRedirect *)nuevo;
			if((cantHREF - 1 == contador)) {
				NodoPagina *actual2 = primero;
				while(actual2->abajo != nullptr) {
					actual2 = actual2->abajo;
				}
				actual2->siguiente = abajo->siguiente;
			}
			contador++;
		} else {
			NodoPagina *actual = primero;
			while(actual->abajo != nullptr) {
				actual = actual->abajo;
			}
			actual->abajo = nuevo;
			abajo = (NodoRedirect *)actual->abajo;
			name = nuevo->link;
			contador = 0;
			contador++;
			activo = true;
		}
	}
}
double ListaEnlazada::calcularPR (double Resultado,float sobre) {
	return 	Resultado = (1 - 0.85) + 0.85 * (sobre);
}
vector<string> ListaEnlazada::calcularRef (NodoPagina *page,vector<string> &TotalCoincidencia) {
	Archivo a;
	vector<string>Coincidencia;
	NodoRedirect *Siguiente = primero->siguiente;
	NodoPagina *abajo = primero;
	bool cerrar = true;
	if(exis) {
		LimpiarPr ();
		page = primero;
		guardar = false;
		exis = false;
	} else if(page == nullptr) {
		return TotalCoincidencia;
	}
	while(abajo != nullptr) {
		if(Siguiente == nullptr) {
			abajo = abajo->abajo;
			if(abajo == nullptr) {
				cerrar = false;
				break;
			} else {
				if(abajo->link == page->link) {
					abajo = abajo->abajo;
				}
				if(abajo != nullptr) {
					if(abajo->siguiente == nullptr) {
						abajo = abajo->abajo;
					}
				}
				if(abajo == nullptr) {
					break;
				} else {
					Siguiente = abajo->siguiente;
				}
			}
		}
		if(Siguiente->link == page->link && cerrar) {
			TotalCoincidencia.push_back (abajo->link);
			Coincidencia.push_back (abajo->link);
		}
		Siguiente = Siguiente->siguiente;
	}
	float PR = 0;
	double Resultado = 0;
	int x = 0;
	if(Coincidencia.size () == 0) {
		page->Pr = 0.15;
		page->Cantidad = 0;
	}else{
		for(int i = 0; i < Coincidencia.size (); i++) {
			x = a.cantidadHREF (Coincidencia[i]) - 1;
			PR += (double)1 / x;
		}
		page->Pr = calcularPR (Resultado,PR);
		page->Cantidad = Coincidencia.size ();
	}
	cout << endl;
	return calcularRef (page->abajo,TotalCoincidencia);;
}
void ListaEnlazada::LimpiarPr () {
	NodoPagina *actual = primero;
	while(actual != nullptr) {
		actual->Pr = 0;
		actual = actual->abajo;
	}
}
void ListaEnlazada::ImprimirPR (string palabra) {
	ofstream archivo;
	NodoPagina *actual = primero;
	vector<NodoPagina *>ordenar;
	while(actual != nullptr) {
		ordenar.push_back (actual);
		actual = actual->abajo;
	}
	archivo.open ("Enlaces.html",ios::app);
	sort (ordenar.begin (),ordenar.end (),[](const NodoPagina *left,const NodoPagina *right) { return (left->Pr > right->Pr); });
	archivo << "Palabra Buscada: " << palabra << endl;
	for(int i = 0; i < ordenar.size (); i++) {
		archivo << "Pagina: " << ordenar[i]->link << " PR: " << ordenar[i]->Pr << endl;
		cout << "<h2>Pagina: " << ordenar[i]->link << " " << ordenar[i]->Pr << "</h2>" << endl;
		cout << "<a href=\"" << ordenar[i]->link << "\"> " << ordenar[i]->link << " </a>" << endl;
	}
	archivo << endl;
	archivo.close ();
}
void ListaEnlazada::AjustarPR (NodoPagina *page,vector<string> &TotalCoincidencia,int contador,int posArreglo) {
	//Caso Base
	if(contador == 100 || TotalCoincidencia.size () == 0) {
		return;
	} else {
		page = primero;
		posArreglo = 0;
		Archivo a;
		NodoPagina *tmp = primero;
		float PR = 0;
		double Resultado = 0;
		int cantidadElementos = 0;
		int x = 0;
		for(int i = 0; i < TotalCoincidencia.size (); i++) {
			x = a.cantidadHREF (TotalCoincidencia[i]) - 1;
			if(page->Cantidad == cantidadElementos) {
				valores[posArreglo] = (double)calcularPR (Resultado,PR);
				posArreglo += 1;
				cantidadElementos = 0;
				page = page->abajo;
				PR = 0;
				i--;
				Resultado = 0;
			} else {
				while(tmp != nullptr) {
					if(tmp->link == TotalCoincidencia[i]) {
						PR += tmp->Pr / x;
						break;
					}
					tmp = tmp->abajo;
				}
				tmp = primero;
				cantidadElementos++;
			}
			if(i == TotalCoincidencia.size () - 1) {
				valores[posArreglo] = (double)calcularPR (Resultado,PR);
				posArreglo += 1;
			}
		}
		NodoPagina *SetPr = primero;
		int posicion = 0;
		while(SetPr != nullptr) {
			SetPr->Pr = valores[posicion];
			SetPr = SetPr->abajo;
			posicion++;
		}
	}
	AjustarPR (page,TotalCoincidencia,contador+1,posArreglo);
}
