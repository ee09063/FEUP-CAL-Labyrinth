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
#include "Labirinto.h"
#include <cstdio>
#include "graphviewer.h"
#include "Labirinto.h"
#include <fstream>
#include <stdlib.h>

using namespace std;

int main()
{
	srand(time(0)%1000);
	string myfile = "labirinto.txt";
	Labirinto *lab1 = new Labirinto(myfile.c_str(),';');
	vector< vector <string> > strs = lab1->getLabirinto();

	Grafo *graf1 = new Grafo(strs);
	int heroX = graf1->getGraph().heroX; int heroY = graf1->getGraph().heroY;
	int swordX = graf1->getGraph().swordX; int swordY = graf1->getGraph().swordY;
	int exitX = graf1->getGraph().exitX; int exitY = graf1->getGraph().exitY;
	int nod = graf1->getGraph().nod;
	vector<Vertex*> dragons;
	Vertex* sword = graf1->getGraph().getVertex(swordX,swordY);
	Vertex* exit = graf1->getGraph().getVertex(exitX,exitY);
	bool heroArmed = false;
	bool heroAlive = true;

	graf1->printGraph();

	while(nod != 0 && heroAlive)
	{
		Vertex* hero = graf1->getGraph().getVertex(heroX,heroY);
		dragons.clear();
		//Movimento do heroi enquanto desarmado
		if(!heroArmed && heroAlive)
		{
			vector<Vertex*> path = graf1->getGraph().ShortestPath(hero, sword);
			if(path.size() != 0)
			{
				for(int i = 0; i < hero->getNumEdges(); i++)
				{
					if(hero->getDest(i) == path[0])
					{
						if(hero == exit){
							hero->setSymbol("S");
							graf1->gv->setVertexColor(graf1->getGraph().getVertexindex(exit->getX(),exit->getY()),"orange");
							graf1->gv->rearrange();
							//Sleep(3000);
						}
						else{
							hero->setSymbol("N");
							graf1->gv->setVertexColor(graf1->getGraph().getVertexindex(hero->getX(),hero->getY()),"white");
							graf1->gv->rearrange();
							//Sleep(3000);

						}
						path[0]->setSymbol("H");
						graf1->gv->setVertexColor(graf1->getGraph().getVertexindex(path[0]->getX(),path[0]->getY()),"blue");
						graf1->gv->rearrange();
						Sleep(1000);
						heroX = path[0]->getX();
						heroY = path[0]->getY();
						if(heroX == swordX && heroY == swordY)
						{
							heroArmed = true;
						}
					}
				}
			}
		}
		///////////////
		//Movimento do heroi enquanto armado
		else if(heroArmed)
		{
			vector<Vertex*> path = graf1->getGraph().ShortestPathDragon(hero);

			for(int i = 0; i < hero->getNumEdges(); i++)
			{
				if(hero->getDest(i) == path[0])
				{
					if(path[0]->getSymbol() == "D")
					{
						cout << "KILLED DRAGON" << endl;
						nod--;
					}
					if(hero == exit){
						hero->setSymbol("S");
						graf1->gv->setVertexColor(graf1->getGraph().getVertexindex(hero->getX(),hero->getY()),"orange");
						graf1->gv->rearrange();
					}
					else{
						hero->setSymbol("N");
						graf1->gv->setVertexColor(graf1->getGraph().getVertexindex(hero->getX(),hero->getY()),"white");
						graf1->gv->rearrange();
					}
					path[0]->setSymbol("H");
					graf1->gv->setVertexColor(graf1->getGraph().getVertexindex(path[0]->getX(),path[0]->getY()),"blue");
					graf1->gv->rearrange();
					Sleep(1000);
					heroX = path[0]->getX();
					heroY = path[0]->getY();
				}
			}
		}
		/////////////////////
		//Movimento dos dragoes
		for(int i = 0; i < graf1->getGraph().getNumVertex(); i++)
		{
			Vertex* present = graf1->getGraph().getVertex(i);
			if(present->getSymbol() == "D" )
			{
				dragons.push_back(present);
			}
		}
		for(unsigned int i = 0; i < dragons.size(); i++)
		{
			int v = rand()%dragons[i]->getNumEdges();
			Vertex* next = dragons[i]->getDest(v);
			if(next->getSymbol() == "H" && heroArmed == false)
			{
				dragons[i]->setSymbol("N");
				next->setSymbol("D");
				heroAlive = false;
				graf1->gv->setVertexColor(graf1->getGraph().getVertexindex(dragons[i]->getX(),dragons[i]->getY()),"white");
				graf1->gv->setVertexColor(graf1->getGraph().getVertexindex(next->getX(),next->getY()),"red");
				graf1->gv->rearrange();
				Sleep(1000);
				cout << "HERO IS DEAD"<<endl;
			}
			else if(next->getSymbol() == "N")
			{
				dragons[i]->setSymbol("N");
				next->setSymbol("D");
				graf1->gv->setVertexColor(graf1->getGraph().getVertexindex(dragons[i]->getX(),dragons[i]->getY()),"white");
				graf1->gv->setVertexColor(graf1->getGraph().getVertexindex(next->getX(),next->getY()),"red");
				graf1->gv->rearrange();
				Sleep(1000);
			}
		}
		///////////
		graf1->printGraph();
		cout << "NUM DRAGON: " << nod << endl;
	}
	//Movimento do herói para a saída
	if(heroAlive)
	{
		cout << "NOW TO EXIT" << endl;
		Vertex* hero = graf1->getGraph().getVertex(heroX,heroY);
		vector<Vertex*>pathToExit = graf1->getGraph().ShortestPath(hero,exit);
		for(unsigned int i = 0; i < pathToExit.size(); i++)
		{
			Vertex* hero = graf1->getGraph().getVertex(heroX,heroY);
			Vertex* next = pathToExit[i];

			for(int j = 0; j < hero->getAdjSize(); j++)
			{
				if(hero->getDest(j) == next)
				{
					hero->setSymbol("N");
					next->setSymbol("H");
					heroX = next->getX();
					heroY = next->getY();
					graf1->gv->setVertexColor(graf1->getGraph().getVertexindex(hero->getX(),hero->getY()),"white");
					graf1->gv->setVertexColor(graf1->getGraph().getVertexindex(next->getX(),next->getY()),"blue");
					graf1->gv->rearrange();
					Sleep(1000);
				}
			}
			graf1->printGraph();
		}
	}
	///////////////////////////
	cout << "END OF APP" << endl;

	getchar();
	return 0;
}
