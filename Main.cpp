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
	for(int i = 0; i < argc; i++) {
		ListaEnlazada e = ListaEnlazada (argv[i]);
	}
	return 0;
}
