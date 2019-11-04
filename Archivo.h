#pragma once
using namespace std;
#include <string>
#include "ListaEnlazada.h"
#include <list>
#include <vector>
#include <array>
#ifndef ARCHIVO_H
#define ARCHIVO_H

class Archivo {
public:
	//Archivo ();
	void LeerArchivo (string, vector<string>, int,int);
	int cantidadHREF (string);
	bool existePagina (string);
	vector<string> extraerPaginas (string);
	void eiminarDuplicados (string pagina,int contador,ListaEnlazada &);
private:
	//ListaEnlazada ls;
	bool activo = true;
	bool active = true;
	bool cerrar = true;
};
#endif // !ARCHIVO_H
