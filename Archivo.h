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
	void LeerArchivo (string, vector<string>, int,int,ListaEnlazada&);
	int cantidadHREF (string);
	vector<string> extraerPaginas (string);
private:
	//ListaEnlazada ls;
	bool activo = true;
	bool active = true;
	bool cerrar = true;
};
#endif // !ARCHIVO_H
