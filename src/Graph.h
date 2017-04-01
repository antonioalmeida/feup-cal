/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <cmath>
#include <stddef.h>
#include <iostream>
#include "InfoVertex.h"

using namespace std;

#define INT_INFINITY 999999

template <class T> class Edge;
template <class T> class Graph;

template <class T>
class Vertex {
private:
	T info;
	vector<Edge<T>  > adj;
	bool visited;
	bool processing;
	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
	int indegree;
	int dist;
	Vertex<T>* path;
	InfoVertex infoV;
public:
	int getIndegree() const;
	vector<Edge<T> > getAdj(){return adj;};
	T getInfo() const;
	InfoVertex getInfoV();
	void setInfoV(InfoVertex infoV);
	void incIndegree();
	void decIndegree();
	Vertex(T in, InfoVertex extraIn);
	void setDelivered(bool val);
	friend class Graph<T>;
};

template <class T>
InfoVertex Vertex<T>::getInfoV(){
	return infoV;
}
template <class T>
void Vertex<T>::setInfoV(InfoVertex infoV){
	this->infoV=infoV;
}

template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	typename vector<Edge<T> >::iterator it= adj.begin();
	typename vector<Edge<T> >::iterator ite= adj.end();
	while (it!=ite) {
		if (it->dest == d) {
			adj.erase(it);
			return true;
		}
		else it++;
	}
	return false;
}

template <class T>
Vertex<T>::Vertex(T in, InfoVertex extraIn): info(in), infoV(extraIn), visited(false), indegree(0), processing(false), dist(0), path(0) {}


template <class T>
void Vertex<T>::addEdge(Vertex<T> *dest, double w) {
	Edge<T> edgeD(dest,w);
	adj.push_back(edgeD);
}

template <class T>
int Vertex<T>::getIndegree() const{
	return indegree;
}

template <class T>
void Vertex<T>::incIndegree(){
	indegree++;
}

template <class T>
void Vertex<T>::decIndegree(){
	indegree--;
}

template <class T>
T Vertex<T>::getInfo() const{
	return info;
}

template <class T>
void Vertex<T>::setDelivered(bool val) {
	infoV.setDelivered(val);
}

template <class T>
class Edge {
	Vertex<T> * dest;
	double weight;
public:
	Edge(Vertex<T> *d, double w);
	Vertex<T> * getDest() {return dest;};
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w){}

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
	void dfs(Vertex<T> *v, vector<T> &res) const;
	void dfs_aux(Vertex<T> *v, vector<T> &res) const;

	//exercicio 6
	int ** W;   //weight
	int ** P;   //path
public:
	bool addVertex(const T &in, const InfoVertex &extraIn);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeVertex(const T &in);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> dfs_aux() const; //Used for isDAG
	vector<T> bfs(Vertex<T> *v) const;
	int maxNewChildren(Vertex<T> *v, T &inf) const;
	vector<Vertex<T> * > getVertexSet() const;
	int getNumVertex() const;
	vector<Vertex<T>*> getSources() const;
	void resetIndegrees();
	bool isDAG();
	vector<T> topologicalOrder();
	void unweightedShortestPath(const T &v);
	void shortestPathUnweighted(const T &s);
	Vertex<T>* getVertex(const T &v);
	int getIndex(Vertex<T> *v);

	//exercicio 6
	void bellmanFordShortestPath(const T &s);
	void dijkstraShortestPath(const T &s);
	void floydWarshallShortestPath();
	int edgeCost(int vOrigIndex, int vDestIndex);
	vector<T> getfloydWarshallPath(const T &origin, const T &dest);
	void getfloydWarshallPathAux(int index1, int index2, vector<T> & res);
	int nodeDistance(int vOrigIndex, int vDestIndex);
};

class CycleException{};

template <class T>
int Graph<T>::getIndex(Vertex<T> *v){
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i] == v) return i;
	return -1;
}

template <class T>
Vertex<T>* Graph<T>::getVertex(const T &v){
	for(unsigned int i = 0; i < vertexSet.size(); i++)
		if (vertexSet[i]->info == v) return vertexSet[i];
	return NULL;
}

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}
template <class T>
vector<Vertex<T> * > Graph<T>::getVertexSet() const {
	return vertexSet;
}

template <class T>
bool Graph<T>::addVertex(const T &in, const InfoVertex &extraIn) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++)
		if ((*it)->info == in) return false;
	Vertex<T> *v1 = new Vertex<T>(in, extraIn);
	vertexSet.push_back(v1);
	return true;
}

template <class T>
bool Graph<T>::removeVertex(const T &in) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	for (; it!=ite; it++) {
		if ((*it)->info == in) {
			Vertex<T> * v= *it;
			vertexSet.erase(it);
			for(Edge<T> adjacent : v->adj)
				adjacent.dest->decIndegree();
			typename vector<Vertex<T>*>::iterator it1= vertexSet.begin();
			typename vector<Vertex<T>*>::iterator it1e= vertexSet.end();
			for (; it1!=it1e; it1++) {
				(*it1)->removeEdgeTo(v);
			}
			delete v;
			return true;
		}
	}
	return false;
}

template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	vS->addEdge(vD,w);
	vD->incIndegree();
	return true;
}

template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	typename vector<Vertex<T>*>::iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite= vertexSet.end();
	int found=0;
	Vertex<T> *vS, *vD;
	while (found!=2 && it!=ite ) {
		if ( (*it)->info == sourc )
		{ vS=*it; found++;}
		if ( (*it)->info == dest )
		{ vD=*it; found++;}
		it ++;
	}
	if (found!=2) return false;
	if(vS->removeEdgeTo(vD)){
		vD->decIndegree();
		return true;
	}
	else
		return false;
}




template <class T>
vector<T> Graph<T>::dfs() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfs(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs(Vertex<T> *v,vector<T> &res) const {
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++)
		if ( it->dest->visited == false )
			dfs(it->dest, res);
}

template <class T>
vector<T> Graph<T>::dfs_aux() const {
	typename vector<Vertex<T>*>::const_iterator it= vertexSet.begin();
	typename vector<Vertex<T>*>::const_iterator ite= vertexSet.end();
	for (; it !=ite; it++)
		(*it)->visited=false;
	vector<T> res;
	it=vertexSet.begin();
	for (; it !=ite; it++)
		if ( (*it)->visited==false )
			dfs_aux(*it,res);
	return res;
}

template <class T>
void Graph<T>::dfs_aux(Vertex<T> *v,vector<T> &res) const {
	v->processing = true;
	v->visited = true;
	res.push_back(v->info);
	typename vector<Edge<T> >::iterator it= (v->adj).begin();
	typename vector<Edge<T> >::iterator ite= (v->adj).end();
	for (; it !=ite; it++){
		if ( it->dest->visited == false )
			dfs_aux(it->dest, res);

		if( it->dest->processing == true)
			throw CycleException();
	}
	v->processing = false;
}

template <class T>
vector<T> Graph<T>::bfs(Vertex<T> *v) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	q.push(v);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
			}
		}
	}
	return res;
}

template <class T>
int Graph<T>::maxNewChildren(Vertex<T> *v, T &inf) const {
	vector<T> res;
	queue<Vertex<T> *> q;
	queue<int> level;
	int maxChildren=0;
	inf =v->info;
	q.push(v);
	level.push(0);
	v->visited = true;
	while (!q.empty()) {
		Vertex<T> *v1 = q.front();
		q.pop();
		res.push_back(v1->info);
		int l=level.front();
		level.pop(); l++;
		int nChildren=0;
		typename vector<Edge<T> >::iterator it=v1->adj.begin();
		typename vector<Edge<T> >::iterator ite=v1->adj.end();
		for (; it!=ite; it++) {
			Vertex<T> *d = it->dest;
			if (d->visited==false) {
				d->visited=true;
				q.push(d);
				level.push(l);
				nChildren++;
			}
		}
		if (nChildren>maxChildren) {
			maxChildren=nChildren;
			inf = v1->info;
		}
	}
	return maxChildren;
}

template <class T>
vector<Vertex<T>*> Graph<T>::getSources() const{
	vector<Vertex<T>*> result;
	for(Vertex<T>* ver : vertexSet){
		if(ver->getIndegree() == 0)
			result.push_back(ver);
	}

	return result;
}

/*
template <class T>
void Graph<T>::resetIndegrees(){
	typename vector<Vertex<T>*>::iterator it = vertexSet.begin();
	typename vector<Vertex<T>*>::iterator ite = vertexSet.end();
	for(;it != ite; it++)
		(*it)->indegree = 0;
	for(it = vertexSet.begin(); it != ite; it++){
		typename vector<Edge<T>>::iterator ita = (*it)->adj.begin();
		typename vector<Edge<T>>::iterator itae = (*it)->adj.end();
		for(; ita != itae; ita++)
			ita->dest->incIndegree();
	}
}
 */

template <class T>
bool Graph<T>::isDAG(){
	try{
		dfs_aux();
		return true;
	}
	catch(CycleException &e){
		return false;
	}
}

template <class T>
vector<T> Graph<T>::topologicalOrder(){
	vector<T> result;
	if(isDAG()){
		vector<Vertex<T>*> sources = getSources();
		queue<Vertex<T>*> order;
		for(Vertex<T>* sour : sources)
			order.push(sour);
		while(!order.empty()){
			Vertex<T>* current = order.front();
			for(Edge<T> adjacent : current->adj){
				if(--(adjacent.dest->indegree) == 0)
					order.push(adjacent.dest);
			}
			result.push_back(current->info);
			order.pop();
		}
	}
	resetIndegrees();
	return result;
}

template <class T>
void Graph<T>::shortestPathUnweighted(const T &s) {
	Vertex<T>* source = 0;
	for(Vertex<T>* v : vertexSet){
		if(v->info == s){
			source = v;
			break;
		}
	}
	if(source == NULL) return;
	for (Vertex<T>* v : vertexSet) {
		v->path = 0;
		v->dist = INFINITY;
	}

	source->dist = 0;
	queue<Vertex<T>*> q;
	q.push(source); // na cauda
	while(!q.isEmpty()){
		Vertex<T>* current = q.front(); // da cabeça
		for (Edge<T> e : current->adj) {
			Vertex<T>* w = e.dest;
			if (w->dist == INFINITY) {
				w->dist = current->dist + 1;
				w->path = current;
				q.add(w);
			}
		}
		q.pop();
	}
}

template<class T>
void Graph<T>::bellmanFordShortestPath(const T &s) {

	for(unsigned int i = 0; i < vertexSet.size(); i++) {
		vertexSet[i]->path = NULL;
		vertexSet[i]->dist = INT_INFINITY;
	}

	Vertex<T>* v = getVertex(s);
	v->dist = 0;
	queue< Vertex<T>* > q;
	q.push(v);

	while( !q.empty() ) {
		v = q.front(); q.pop();
		for(unsigned int i = 0; i < v->adj.size(); i++) {
			Vertex<T>* w = v->adj[i].dest;
			if(v->dist + v->adj[i].weight < w->dist) {
				w->dist = v->dist + v->adj[i].weight;
				w->path = v;
				q.push(w);
			}
		}
	}
}

template<class T>
void Graph<T>::floydWarshallShortestPath() {

	W = new int * [vertexSet.size()];
	P = new int * [vertexSet.size()];
	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		W[i] = new int[vertexSet.size()];
		P[i] = new int[vertexSet.size()];
		for(unsigned int j = 0; j < vertexSet.size(); j++)
		{
			W[i][j] = edgeCost(i,j);
			P[i][j] = -1;
		}
	}


	for(unsigned int k = 0; k < vertexSet.size(); k++)
		for(unsigned int i = 0; i < vertexSet.size(); i++)
			for(unsigned int j = 0; j < vertexSet.size(); j++)
			{
				//se somarmos qualquer coisa ao valor INT_INFINITY, ocorre overflow, o que resulta num valor negativo, logo nem conv�m considerar essa soma
				if(W[i][k] == INT_INFINITY || W[k][j] == INT_INFINITY)
					continue;

				int val = min ( W[i][j], W[i][k]+W[k][j] );
				if(val != W[i][j])
				{
					W[i][j] = val;
					P[i][j] = k;
				}
			}
}

template<class T>
vector<T> Graph<T>::getfloydWarshallPath(const T &origin, const T &dest){

	int originIndex = -1, destinationIndex = -1;

	for(unsigned int i = 0; i < vertexSet.size(); i++)
	{
		if(vertexSet[i]->info == origin)
			originIndex = i;
		if(vertexSet[i]->info == dest)
			destinationIndex = i;

		if(originIndex != -1 && destinationIndex != -1)
			break;
	}


	vector<T> res;

	//se nao foi encontrada solucao possivel, retorna lista vazia
	if(W[originIndex][destinationIndex] == INT_INFINITY)
		return res;

	res.push_back(vertexSet[originIndex]->info);

	//se houver pontos intermedios...
	if(P[originIndex][destinationIndex] != -1)
	{
		int intermedIndex = P[originIndex][destinationIndex];

		getfloydWarshallPathAux(originIndex, intermedIndex, res);

		res.push_back(vertexSet[intermedIndex]->info);

		getfloydWarshallPathAux(intermedIndex,destinationIndex, res);
	}

	res.push_back(vertexSet[destinationIndex]->info);


	return res;
}



template<class T>
void Graph<T>::getfloydWarshallPathAux(int index1, int index2, vector<T> & res)
{
	if(P[index1][index2] != -1)
	{
		getfloydWarshallPathAux(index1, P[index1][index2], res);

		res.push_back(vertexSet[P[index1][index2]]->info);

		getfloydWarshallPathAux(P[index1][index2],index2, res);
	}
}

template<class T>
int Graph<T>::edgeCost(int vOrigIndex, int vDestIndex)
{
	if(vertexSet[vOrigIndex] == vertexSet[vDestIndex])
		return 0;

	for(unsigned int i = 0; i < vertexSet[vOrigIndex]->adj.size(); i++)
	{
		if(vertexSet[vOrigIndex]->adj[i].dest == vertexSet[vDestIndex])
			return vertexSet[vOrigIndex]->adj[i].weight;
	}

	return INT_INFINITY;
}

template<class T>
int Graph<T>::nodeDistance(int vOrigIndex, int vDestIndex) {
	return W[vOrigIndex][vDestIndex];
}

#endif /* GRAPH_H_ */
