#include "ListaEnlazada.h"
#include "Archivo.h"
#include <iostream>
#include "Archivo.h"
#include <fstream>
#include <algorithm>
using namespace std;

ListaEnlazada::ListaEnlazada (void):abajo (nullptr),primero (nullptr) {}

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

void ListaEnlazada::ImprimirLista () {
	LimpiarPr ();
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
bool exis = true;
vector<string> ListaEnlazada::calcularRef (NodoPagina *page,vector<string> &vec) {
	Archivo a;
	vector<string>vec2;
	NodoRedirect *actual = primero->siguiente;
	NodoPagina *abajo = primero;
	bool cerrar = true;
	if(exis) {
		LimpiarPr ();
		page = primero;
		guardar = false;
		exis = false;
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
	//cout << "Pagina: " << page->link;
	if(vec2.size () == 0) {
		int x = a.cantidadHREF (page->link) - 1;
		PR += (double)1 / x;
		page->Pr = 0.15;
		page->Cantidad = 0;
	}
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
	vector<string>exit;
	NodoPagina *actual = primero;
	NodoPagina *tmp = primero;
	NodoPagina *act = primero;
	bool existe = true;
	while(actual != nullptr) {
		if(existe) {
			exit.push_back (actual->link);
			actual->Pr = 0;
		}
		act = actual;
		actual = actual->abajo;

	}
}
void ListaEnlazada::ImprimirPR (string palabra) {
	ofstream archivo;
	NodoPagina *actual = primero;
	vector<NodoPagina*>ordenar;
	
	int variable = 0;
	while(actual != nullptr) {
		//cout<<"<li><a href = "<<actual->link<<"><"< / a>< / li>
		ordenar.push_back (actual);
		//cout << "<h2>Pagina: "<< actual->link << " PR: " << actual->Pr << " Enlaces Salientes: " << actual->Cantidad << "</h2>"<<endl;
		///cout << "<a href=\"" << actual->link << "\"> " << actual->link << " </a>" << endl;
		actual = actual->abajo;
	}
	archivo.open ("Enlaces.html",ios::app);

	std::sort (ordenar.begin (),ordenar.end (),[](const NodoPagina *left,const NodoPagina *right) { return (left->Pr > right->Pr); });
	
	archivo << "Palabra Buscada: "<<palabra<<endl;
	for(int i = 0; i < ordenar.size(); i++) {
		archivo << "Pagina: "<<ordenar[i]->link << " PR: " << ordenar[i]->Pr << endl;
		cout << "<h2>Pagina: " << ordenar[i]->link << " PR: " << ordenar[i]->Pr <<  "</h2>" << endl;
		cout << "<a href=\"" << ordenar[i]->link << "\"> " << ordenar[i]->link << " </a>" << endl;
	}
	archivo << endl;
	archivo.close ();

}
array<double,100>valores;
void ListaEnlazada::AjustarPR (NodoPagina *page,vector<string> &vec,int contador,int posArreglo) {
	//Caso Base
	if(contador == 10 || vec.size () == 0) {
		return;
	} else {
		page = primero;
		posArreglo = 0;
		contador += 1;
		Archivo a;

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
				//Resultado = 0;
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
