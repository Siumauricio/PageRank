#include "Archivo.h"
#include <fstream>
#include <iostream>
#include <sstream> 
#include <string>
#include <regex>
#include "Nodo.h"
#include "ListaEnlazada.h"
using namespace std;
vector<string>lis;
bool it = true;
void Archivo::eiminarDuplicados(string pagina,int contador,ListaEnlazada &ls){
	active = true;
	activo = true;
	cerrar = true;
	cout << endl;
	auto end = lis.end ();
	for(auto it = lis.begin (); it != end; ++it) {
		end = std::remove (it + 1,end,*it);
	}
	lis.erase (end,lis.end ());
	string needle = "href=";
	string cadena;
	smatch match;
	ifstream file (pagina);
	if(contador < lis.size()) {
		if(!file.is_open ()) {
			cout << "Failed to open file!\n";
			return;
		} else {
			while(!file.eof ()) {
				getline (file,cadena);
				istringstream in (cadena);
				if(cadena.find (needle) != std::string::npos) {
					string line (cadena);
					regex re ("href=\"(.*)\">");
					if(regex_search (line,match,re)) {
						activo = false;
						if(active) {
							ls.Anadir (pagina);
							ls.Anadir (match[1].str ());
							active = false;
						} else {
							if(cerrar) {
								ls.Anadir (match[1].str ());
							} else {
								ls.Anadir (match[1].str ());
							}
						}
					}
				}
			}
			cerrar = false;
			if(activo) {
				ls.Anadir (pagina);
			}
		}
	} else {
		return;
	}
	//ls.ImprimirLista ();
	file.close ();
	active = true;
	activo = true;
	cerrar = true;
	if(lis.size()-1 == contador) {
		return;
	} else{
			contador+=1;
			eiminarDuplicados (lis[contador],contador ,ls);
	}
}

void Archivo::LeerArchivo (string pagina,vector<string>lista,int contador,int contador2) {
	string needle = "href=";
	string cadena;
	smatch match;
	bool crash = true;
	ifstream file (pagina);
	if(contador < contador2) {
		if(!file.is_open ()) {
			cout << "Failed to open file!\n";
			return;
		} else {
			while(!file.eof ()) {
				getline (file,cadena);
				istringstream in (cadena);
				if(cadena.find (needle) != std::string::npos) {
					string line (cadena);
					regex re ("href=\"(.*)\">");
					if(regex_search (line,match,re)) {
						activo = false;
						if(active) {
							lis.push_back (pagina);
							lista.push_back (match[1].str ());
							active = false;
						} else {
							if(cerrar) {
								lista.push_back (match[1].str ());
							}
						}
					}
				}
			}
			cerrar = false;
			if(activo) {
				lis.push_back (pagina);
			}
		}
	} else {
		return ;
	}
	//ls.ImprimirLista ();
	file.close ();
	active = true;
	activo = true;
		cerrar = true;
	if(contador2 == 1) {
		return ;
	} else {
		LeerArchivo (lista[contador],lista,contador + 1,contador2);
	}

}
bool Archivo::existePagina(string pagina){
	for(int i = 0; i < lis.size(); i++) {
		if(lis[i]==pagina){
			return false;
		}
	}
	return true;
}
int Archivo::cantidadHREF (string pagina) {
	int contador = 0;
	string needle = "href=";
	string cadena;
	ifstream file (pagina);
	if(!file.is_open ()) {
		cout << "Failed to open file!\n";
	} else {
		contador++;
		while(!file.eof ()) {
			getline (file,cadena);
			istringstream in (cadena);
			if(cadena.find (needle) != std::string::npos) {
				string line (cadena);
				regex re ("href=\"(.*)\">");
				smatch match;
				if(std::regex_search (line,match,re)) {
					contador++;
					//std::cout<<match[1].str ()<<'\n';
				}
			}
		}
	}
	file.close ();
	return contador;
}
vector<string> Archivo::extraerPaginas (string texto) {
	string cadena;
	vector<string>paginas = {"instagram.html","whatsapp.html","facebook.html","google.html","youtube.html","amazon.html","twitter.html"};
	vector<string>pages;
	for(int i = 0; i < paginas.size (); i++) {
		ifstream file (paginas[i]);
		if(!file.is_open ()) {
			cout << "Failed to open file!\n";
			break;
		} else {
			while(!file.eof ()) {
				getline (file,cadena);
				istringstream in (cadena);
				if(cadena.find (texto) != string::npos) {
					string line (cadena);
					regex re ("content=\"(.*)\">");
					smatch match;
					if(regex_search (line,match,re)) {
						pages.push_back (paginas[i]);
					}
				}
			}
		}
	}
	return pages;
}
