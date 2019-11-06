#include <iostream>
#include "Archivo.h"
#include "ListaEnlazada.h"
#include <string>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
using namespace std;

int main (int argc, char **argv) {
	Archivo a;
	vector<string>lista;
	vector<string>lista3;
	vector<string>ls2;
	ListaEnlazada ls;
	cout << "Palabra: " << argv[1] << endl;
	NodoPagina *page2 = new NodoPagina ();
	lista = a.extraerPaginas (argv[1]);
	for(int i = 0; i < lista.size (); i++) {
		a.LeerArchivo (lista[i],lista3,0,a.cantidadHREF (lista[i]));
		//cout << lista[i] << endl;
	}
	a.eiminarDuplicados (lista[0],0,ls);
	ls.calcularRef (nullptr,ls2);
	ls.AjustarPR (page2,ls2,0,0);
	cout << "<h1>\t\tPAGERANK </h1>" << endl;
	ls.ImprimirPR (argv[1]);
	return 0;
}
