#include <iostream>
#include "Archivo.h"
#include "ListaEnlazada.h"
#include <string>
using namespace std;

int main () {
	Archivo a;
	vector<string>lista;
	vector<string>lista3;
	vector<string>ls2;
	ListaEnlazada ls;
	NodoPagina *page = new NodoPagina ();
	NodoPagina *page2 = new NodoPagina ();
	a.LeerArchivo ("google.html",lista3,0,a.cantidadHREF ("google.html"),ls);
	//lista = a.extraerPaginas ("Photos");

	for( int i = 0; i<lista.size (); i++ ) {
		
		//cout<<lista[i]<<endl;
	}
	ls.ImprimirLista ();
	cout << endl<<"-------------------------------------------" << endl;
	ls.calcularRef (nullptr,ls2);
	cout << "-------------------------------------------" << endl;
	ls.AjustarPR (page2,ls2,0,0);
	ls.ImprimirPR ();
}
