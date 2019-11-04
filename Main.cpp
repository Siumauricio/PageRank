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
	NodoPagina *page2 = new NodoPagina ();
	lista = a.extraerPaginas ("Photos");
	for(int i = 0; i < lista.size (); i++) {
		a.LeerArchivo (lista[i],lista3,0,a.cantidadHREF (lista[i]));
		cout << lista[i] << endl;
	}
	a.eiminarDuplicados (lista[0],0,ls);
     //ls.ImprimirLista ();
	cout << endl << "-------------------------------------------" << endl;
	ls.calcularRef (nullptr,ls2);
	ls.AjustarPR (page2,ls2,0,0);
	cout << endl << "-------------------------------------------" << endl;
	ls.ImprimirPR ();
	cout << "-------------------------------------------" << endl;

}
