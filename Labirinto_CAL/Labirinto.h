/*
 * Labirinto.h
 */

#ifndef LABIRINTO_H_
#define LABIRINTO_H_

#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <cstddef>
#include <cctype>
#include <vector>
#include <iomanip>
#include <ctime>
#include <fstream>
#include <algorithm>
#include <cstdio>
#include "Graph.h"
#include "graphviewer.h"
#include <fstream>
#include <stdlib.h>

using namespace std;

/** Class Labirinto */
class Labirinto{
	const char* filename;
	char delimiter;
	vector< vector <string> > strs;
public:
	/** Construtor da Class
	 * @param filename char Nome do ficheiro a carregar
	 * @param delimiter char Caracter separador dos campos usado no ficheiro
	 */
	Labirinto (const char* filename, char delimiter);
	/**
	 * loadLabirinto
	 * Funcao para carregar labirinto a partir de um ficheiro externo
	 * separado por caracter delimitador ex.';'
	*/
	void loadLabirinto ();
	/**
	 * getLabirinto
	 * Devolve o Vector com Vector de strings
	 */
	vector< vector<string> > getLabirinto();
	/**
	 * printLabirinto
	 * Imprime Labirinto para a consola
	 */
	void printLabirinto();

	/**
	 * Class fileNotExists
	 */
	class fileNotExists{
	public:
		/**
		 * Construtor da Class fileNotExists
		 */
		fileNotExists(const char* myfile){
			stringstream ss;
			string s;
			ss << myfile;
			ss >> s;
			cout << "O ficheiro " << myfile << " nao existe." << endl;
			exit(0);
		}
	};
};
/**
 * Class Grafo
 */
class Grafo{
	Graph myGraph;
	vector< vector <string> > strs;
public:
	GraphViewer *gv;
	Grafo(vector< vector <string> > strs);
	void addVertices();
	void addArestas();
	Graph getGraph();
	int getNumLinhas () const;
	int getNumColunas () const;
	void buildGraph();
	void printGraph();

};

#endif /* LABIRINTO_H_ */
