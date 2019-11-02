#include "ListaEnlazada.h"
#include "Archivo.h"
#include <iostream>
#include "Archivo.h"
using namespace std;

ListaEnlazada::ListaEnlazada (void):abajo (nullptr),primero (nullptr) {}

ListaEnlazada::~ListaEnlazada () {
	delete primero;
	delete abajo;
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
			while((NodoRedirect *)actual->siguiente != nullptr) {
				actual = actual->siguiente;
			}
			actual->siguiente = (NodoRedirect *)nuevo;
			if((cantHREF - 1 == contador)) {
				NodoPagina *actual2 = primero;
				while((NodoPagina *)actual2->abajo != nullptr) {
					actual2 = (NodoPagina *)actual2->abajo;
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

void ListaEnlazada::ImprimirLista () {
	cout << endl;
	bool cerrar = true;
	NodoPagina *actual = (NodoPagina *)primero;
	NodoRedirect *tmp = (NodoRedirect *)primero->siguiente;
	while(tmp != nullptr) {
		if(cerrar) {
			cerrar = false;
			cout << "[" << actual->link << "]";
			actual = actual->abajo;
			actual = primero;
		}
		if(actual->siguiente != nullptr) {
			cout << "->";
		}
		cout << "[" << tmp->link << "]";
		tmp = tmp->siguiente;
		if(tmp == nullptr) {
			if(actual->abajo == nullptr) {
				return;
			}
			actual = actual->abajo;
			cout << endl;
			cout << "[" << actual->link << "]";
			tmp = actual->siguiente;
			if(tmp == nullptr) {
				actual = actual->abajo;
				cout << endl;
				cout << "[" << actual->link << "]";
				tmp = actual->siguiente;
			}
		}
	}
	cout << endl;
}

double ListaEnlazada::calcularPR (int iteracciones,double Resultado,float sobre) {
	return 	Resultado = (1 - 0.85) + 0.85 * (sobre);
}

vector<string> ListaEnlazada::calcularRef (NodoPagina *page,vector<string> &vec) {
	Archivo a;
	vector<string>vec2;
	NodoRedirect *actual = primero->siguiente;
	NodoPagina *abajo = primero;
	bool cerrar = true;
	if(vec.size()==0) {
		LimpiarPr ();
		page = primero;
		guardar = false;
	} else if(page == nullptr) {
		return vec;
	}
	while(abajo != nullptr) {
		if(actual == nullptr) {
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
					actual = abajo->siguiente;
				}
			}
		}
		if(actual->link == page->link && cerrar) {
			vec.push_back (abajo->link);
			vec2.push_back (abajo->link);
		}
		actual = actual->siguiente;
	}

	float PR = 0;
	double Resultado = 0;
	cout << "Pagina: " << page->link;
	for(int i = 0; i < vec2.size (); i++) {
		int x = a.cantidadHREF (vec2[i]) - 1;
		PR += (double)1 / x;
		if(vec2.size () - 1 == i) {
			page->Pr = calcularPR (0,Resultado,PR);
			page->Cantidad = vec2.size ();
		}
	}
	cout << endl;
	return calcularRef (page->abajo,vec);;
}
void ListaEnlazada::LimpiarPr () {
	NodoPagina *actual = primero;
	while(actual != nullptr) {
		actual->Pr = 0;
		actual = actual->abajo;
	}
}
void ListaEnlazada::ImprimirPR () {
	NodoPagina *actual = primero;
	while(actual != nullptr) {
		cout << "Pagina: " << actual->link << " PR: " << actual->Pr << " Enlaces Salientes: " << actual->Cantidad << endl;
		actual = actual->abajo;
	}
}

void ListaEnlazada::AjustarPR (NodoPagina *page,vector<string> &vec,int contador,int posArreglo) {
	//Caso Base
	if(contador == 500) {
		cout << contador;
		return;
	}else{
		page = primero;
		posArreglo = 0;
		contador += 1;
		Archivo a;
		array<double,100>valores;
		NodoPagina *tmp = primero;
		float PR = 0;
		double Resultado = 0;
		int cantidadElementos = 0;
		for(int i = 0; i < vec.size (); i++) {
			int x = a.cantidadHREF (vec[i]) - 1;
			if(page->Cantidad == cantidadElementos) {
				valores[posArreglo] = (double)calcularPR (0,Resultado,PR);
				posArreglo += 1;
				cantidadElementos = 0;
				page = page->abajo;
				PR = 0;
				i--;
				Resultado = 0;
			} else {
				while(tmp != nullptr) {
					if(tmp->link == vec[i]) {
						PR += tmp->Pr / x;
						break;
					}
					tmp = tmp->abajo;
				}
				tmp = primero;
				cantidadElementos++;
			}
			if(i == vec.size () - 1) {
				valores[posArreglo] = (double)calcularPR (0,Resultado,PR);
				posArreglo += 1;
			}
		}
		NodoPagina *SetPr = primero;
		int x = 0;
		while(SetPr != nullptr) {
			SetPr->Pr = valores[x];
			SetPr = SetPr->abajo;
			x++;
		}
	}
	AjustarPR (page,vec,contador,posArreglo);
}






















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