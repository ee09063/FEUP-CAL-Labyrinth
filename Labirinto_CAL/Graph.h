/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>

using namespace std;

//class Edge;
class Graph;
class Vertex;

const int NOT_VISITED = 0;
const int DONE_VISITED = 1;
const int INT_INFINITY = 10000000;

/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */
class Edge {
	Vertex *dest;
	double weight;
	string color;
public:
	Edge(Vertex *d, double w): dest(d), weight(w){color="green";}
	friend class Graph;
	friend class Vertex;
	Vertex* getVertex(){return dest;}
	string getColor(){return color;}
	void setColor(string color){this->color=color;}
};

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */
class Vertex {
	vector<Edge> adj;
	string space;
	int dist;
	bool visited;
	int x;
	int y;
	string Color;
public:
	Vertex(string space, int x, int y): space(space), dist(0), visited(false), x(x), y(y)  {path = NULL;Color="blue";}
	friend class Graph;

	void addEdge(Vertex *dest, double w) {
		Edge edgeD(dest,w);
		adj.push_back(edgeD);
	}
	void setEdgeColor(Vertex *d,string Color){
		typename vector<Edge >::iterator it= adj.begin();
		while(it!=adj.end()){
				(*it).setColor(Color);
			it++;
		}
	}
	bool removeEdgeTo(Vertex *d){
		typename vector<Edge >::iterator it= adj.begin();
		typename vector<Edge >::iterator ite= adj.end();
		while (it!=ite) {
			if (it->dest == d) {
				adj.erase(it);
				return true;
			}
			else it++;
		}
		return false;
	}
	int getX(){return x;}
	int getY(){return y;}
	int getDist() const{return this->dist;}
	int getNumEdges() const{return adj.size();}
	vector<Edge> getEdge(){return adj;}
	string getColor(){return Color;}
	void setColor(string Color){this->Color=Color;}
	string getSymbol(){return space;}
	void setSymbol(string s){space = s;}
	Vertex* getDest(int i){return adj[i].dest;}
	void setX(int i){x = i;}
	void setY(int i){y = i;}
	int getAdjSize(){return adj.size();}

	Vertex* path;
};


/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */

class Graph {
	vector<Vertex *> vertexSet;

public:
	int heroX;
	int heroY;
	int exitX;
	int exitY;
	int swordX;
	int swordY;
	int nod;
	Graph(){
		nod=0;
	}
	bool addVertex(string space, int x, int y){
		typename vector<Vertex*>::iterator it= vertexSet.begin();
		typename vector<Vertex*>::iterator ite= vertexSet.end();

		Vertex *v1 = new Vertex(space,x,y);
		vertexSet.push_back(v1);
		return true;
	}
	bool addEdge(const Vertex &sourc, const Vertex &dest, double w){
		typename vector<Vertex*>::iterator it= vertexSet.begin();
		typename vector<Vertex*>::iterator ite= vertexSet.end();

		int found=0;
			Vertex *vS, *vD;
			while (found!=2 && it!=ite )
			{
				if ( (*it)->x == sourc.x && (*it)->y == sourc.y)
					{ vS=*it; found++;}
				if ( (*it)->x == dest.x && (*it)->y == dest.y )
					{ vD=*it; found++;}
				it ++;
			}
			if (found!=2) return false;
			vS->addEdge(vD,w);
			return true;
	}
	bool removeVertex(const Vertex &v);
	bool removeEdge(const Vertex &sourc, const Vertex &dest);
	vector<Vertex * > getVertexSet() const{return vertexSet;}
	int getNumVertex() const{return vertexSet.size();}

	Vertex* getVertex(const Vertex &v) const{
		for(unsigned int i = 0; i < vertexSet.size(); i++)
		{
			if (vertexSet[i]->x == v.x && vertexSet[i]->y == v.y)
			{
				return vertexSet[i];
			}
		}
		return NULL;
	}
	Vertex* getVertex(int x, int y) const{
		for(unsigned int i = 0; i < vertexSet.size(); i++)
		{
			if (vertexSet[i]->x == x && vertexSet[i]->y == y)
			{
				return vertexSet[i];
			}
		}
		return NULL;
	}
	int getVertexindex(int x, int y) const{
			for(unsigned int i = 0; i < vertexSet.size(); i++)
			{
				if (vertexSet[i]->x == x && vertexSet[i]->y == y)
				{
					return i;
				}
			}
			return -1;
		}
	void setVertexColor(int x, int y, string Color) const{
			for(unsigned int i = 0; i < vertexSet.size(); i++)
			{
				if (vertexSet[i]->x == x && vertexSet[i]->y == y)
				{
					vertexSet[i]->setColor(Color);
				}
			}
		}
	Vertex* getVertex(int i) const{return vertexSet[i];}
	vector<Vertex*> getSources() const;
	int getVertexId(int x, int y) const{
		for(unsigned int i = 0; i < vertexSet.size(); i++){
			if (vertexSet[i]->x == x && vertexSet[i]->y == y){
				return i;
			}
		}
		return 0;
	}

	vector<Vertex*> ShortestPath(Vertex* source, Vertex* dest)
		{
		vector<Vertex*>path;
			for(unsigned int i = 0; i < vertexSet.size(); i++){
				vertexSet[i]->path = NULL;
				vertexSet[i]->dist = INT_INFINITY;
			}
			source->dist=0;
			queue<Vertex*> q;
			q.push(source);
			while(!q.empty()){
				Vertex* v = q.front();
				q.pop();
				for(unsigned int i = 0; i < v->adj.size(); i++)
				{
					Vertex* w = v->adj[i].dest;
					if(w->getSymbol() != "D")
					{
						if(w->dist == INT_INFINITY)
						{
							w->dist = v->dist+1;
							w->path=v;
							q.push(w);
						}
						if(w == dest)
						{
							list<Vertex*>buffer;
							Vertex* v = dest;
							buffer.push_front(v);
							while(v->path != NULL && v->path != source)
							{
								v = v->path;
								buffer.push_front(v);
							}
							while(!buffer.empty())
							{
								path.push_back(buffer.front());
								buffer.pop_front();
							}
							return path;
						}
					}
				}
			}
			return path;
		}

	vector<Vertex*> ShortestPathDragon(Vertex* source)
		{
			vector<Vertex*>path;
			for(unsigned int i = 0; i < vertexSet.size(); i++)
			{
				vertexSet[i]->path = NULL;
				vertexSet[i]->dist = INT_INFINITY;
			}
			source->dist=0;
			queue<Vertex*> q;
			q.push(source);
			while(!q.empty())
			{
				Vertex* v = q.front();
				q.pop();
				for(unsigned int i = 0; i < v->adj.size(); i++)
				{
					Vertex* w = v->adj[i].dest;
					if(w->dist == INT_INFINITY)
					{
						w->dist = v->dist+1;
						w->path=v;
						q.push(w);
						if(w->getSymbol() == "D")
						{
							list<Vertex*>buffer;
							buffer.push_front(w);
							while(w->path != NULL && w->path != source)
							{
								w = w->path;
								buffer.push_front(w);
							}
							vector<Vertex*>path;
							while(!buffer.empty())
							{
								path.push_back(buffer.front());
								buffer.pop_front();
							}
							return path;
						}
					}
				}
			}
			return path;
		}
		vector<Vertex*> getPath(Vertex* source, Vertex* dest)
		{
			list<Vertex*>buffer;
			Vertex* v = dest;
			buffer.push_front(v);
			while(v->path != NULL && v->path != source)
			{
				v = v->path;
				buffer.push_front(v);
			}
			vector<Vertex*>path;
			while(!buffer.empty())
			{
				path.push_back(buffer.front());
				buffer.pop_front();
			}
			return path;
		}

};

#endif /* GRAPH_H_ */
