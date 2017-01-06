/*
 * labirinto.cpp
 */
#include "labirinto.h"

/** Construtor da Class Labirinto*/
Labirinto::Labirinto (const char* filename, char delimiter):filename(filename),delimiter(delimiter){
	loadLabirinto ();
}
/**
 * loadLabirinto
 * Funcao para carregar labirinto a partir de um ficheiro externo
 * separado por caracter delimitador ex.';'
*/
void Labirinto::loadLabirinto (){
//stream
ifstream infile(filename);
strs.push_back(vector<string>());
string invalue;
int i=0;
int j=0;
	if(!infile) throw fileNotExists(filename);
	else if (infile){
		// IF FILE EXISTS POPULATE VECTOR
		while(getline (infile, invalue, delimiter)){
			if (!infile.eof()) {
				if(*invalue.c_str()=='\n'){
					i++;
					j=0;
					strs.push_back(vector<string>());
					invalue.erase(remove(invalue.begin(), invalue.end(), '\n'), invalue.end());
					strs[i].push_back(invalue);
				} else {
					strs[i].push_back(invalue);
					j++;
				}

			}
		}
	}
}
/**
* getLabirinto
* Devolve o Vector com Vector de strings
*/
vector< vector<string> > Labirinto::getLabirinto(){
	return strs;
}

/**
 * printLabirinto
 * Imprime Labirinto para a consola
 */
void Labirinto::printLabirinto(){
	for(unsigned int i=0;i<strs.size();i++){
		for(unsigned int j=0; j<strs[i].size();j++)
			cout << strs[i][j];
		cout << endl;
	}
	cout << "Dimensao  Linhas: " << strs.size() << endl;
	cout << "Dimensao Colunas: " << strs[0].size() << endl;
}

/** Construtor da Class Grafo */
Grafo::Grafo (vector< vector <string> > strs):strs(strs){
	addVertices();
	addArestas();
	gv = new GraphViewer(600, 600, false);
	buildGraph();
}
/**
 * Adicionar Vertices ao Grafo
*/
void Grafo::addVertices(){
	for(size_t i = 0; i < strs.size(); i++){
		for(size_t j = 0; j < strs[i].size(); j++){
			if(strs[i][j] != "X"){
				//cout << "I: " << i << " J: " << j << " VALOR: " << strs[i][j] << endl;
					myGraph.addVertex(strs[i][j], i, j);
					//if((i+j)%2==0)myGraph.setVertexColor(i,j,"red");
					if(strs[i][j] == "H")
						{
							myGraph.heroX = i; myGraph.heroY = j;
							myGraph.setVertexColor(i,j,"blue");
						}
						else if(strs[i][j] == "E")
						{
							myGraph.swordX = i; myGraph.swordY = j;
							myGraph.setVertexColor(i,j,"green");
						}
						else if(strs[i][j] == "S")
						{
							myGraph.exitX = i; myGraph.exitY = j;
							myGraph.setVertexColor(i,j,"orange");
						}
						else if(strs[i][j] == "D")
						{
							myGraph.nod+=1;
							myGraph.setVertexColor(i,j,"red");
						} else {myGraph.setVertexColor(i,j,"white");}
			}
		}
	}
}
/**
 * Adicionar Arestas Ao Grafo
 */
void Grafo::addArestas(){
int numLinhas = getNumLinhas();
int numColunas = getNumColunas();
for(int i = 0; i < myGraph.getNumVertex(); i++)
	{
		Vertex* v = myGraph.getVertex(i);
		int xCoord = v->getX(), yCoord = v->getY();
		//UP
		if(xCoord-1 >= 0)
		{
			if(strs[xCoord-1][yCoord] != "X")
			{
				Vertex* w = myGraph.getVertex(xCoord-1, yCoord);
				v->addEdge(w,1.0);
			}
		}
		//DOWN
		if( xCoord+1 < numLinhas)
		{
			if(strs[xCoord+1][yCoord] != "X")
			{
				Vertex* w = myGraph.getVertex(xCoord+1, yCoord);
				v->addEdge(w,1.0);
			}
		}
		//LEFT
		if(yCoord-1 >= 0)
		{
			if(strs[xCoord][yCoord-1] != "X")
			{
				Vertex* w = myGraph.getVertex(xCoord, yCoord-1);
				v->addEdge(w,1.0);
			}
		}
		//RIGHT
		if( yCoord+1 < numColunas)
		{
			if(strs[xCoord][yCoord+1] != "X")
			{
				Vertex* w = myGraph.getVertex(xCoord, yCoord+1);
				v->addEdge(w,1.0);
			}
		}
	}
}
/**
 * Devolve a Graph
 */
Graph Grafo::getGraph(){
	return myGraph;
}
/**
 * Devolve numero de linhas o vetor labirinto
 */
int Grafo::getNumLinhas () const{
	return strs.size();
}
/**
 * Devolve numero de colunas o vetor labirinto
 */
int Grafo::getNumColunas () const{
	return strs[0].size();
}
void Grafo::buildGraph(){
	gv->setBackground("background.jpg");
	gv->createWindow(600, 600);
	gv->defineVertexColor("blue");
	gv->defineEdgeColor("green");


	//Adicionar Nos
	for(int i=0;i<myGraph.getNumVertex();i++){
		gv->addNode(i,80+myGraph.getVertex(i)->getY()*50,120+myGraph.getVertex(i)->getX()*50);
		gv->setVertexColor(i,myGraph.getVertex(i)->getColor());
		gv->rearrange();
	}

	//Adicionar Arestas
	int id=0;
	vector<Edge> edge;
	for(int i=0;i<myGraph.getNumVertex();i++){
		edge=myGraph.getVertex(i)->getEdge();
		typename vector<Edge >::iterator it=edge.begin();
		while(it!=edge.end()){
			//A TRATAR
			cout << "Vx:" <<myGraph.getVertex(i)->getX() << " ";
			cout << "Vy:" <<myGraph.getVertex(i)->getY() << endl;

			//Saber id Vertex Final Pelas Coordenada x, y do vertice da aresta
			int j=myGraph.getVertexId((*it).getVertex()->getX(),(*it).getVertex()->getY());
			cout << id << ";" << i << ";" << j << ";" << endl;
			gv->addEdge(id,i,j,EdgeType::UNDIRECTED);
			gv->setEdgeColor(id,(*it).getColor());
			id++;
			it++;
		}
	}
}

void Grafo:: printGraph()
{
	int k = 0;
	for(int x = 0; x < getNumLinhas(); x++)
		for(int y = 0; y < getNumColunas(); y++)
		{
			if(getGraph().getVertex(x,y) != NULL)
				cout << getGraph().getVertex(x,y)->getSymbol() << " ";
			else cout << "  ";

			if(k == getNumColunas()-1)
			{
				k = 0;
				cout << endl;
			}
			else k++;
		}
	cout << endl << endl;
}

