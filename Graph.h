#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <list>
#include <iterator>
#include <algorithm>

using namespace std;

class Graph{

private:
    int vertices;//<! numero de vertices

    list<int> *m_adj;//<! lista de adjacencia

    /**!
     * @param v - vetor em questão.
     * @param visited[] - vetor de vertices visitados.
     **/
    void DFS(int v, bool visited[], int &coast);// Usada recursivamente pela função void DFS(int v);

    /**!
     *
     */
    int expandir(int finalVertex, int *heuristic, int custo, list<int> &mList);

public:
    Graph(int vertices);

    /**!
      * Adiciona uma aresta a um vertice
      **/
    void addEdge(int vertex, int edge);

    /**!
      * imprime a arvore geradora da busca em profundudade apartir do 'initialVertex' (vertice inicial)
      **/
    void BFS(int initialVertex);

    /**!
      * Imprime a arvore geradora de busca em largura em um grafo orientado desconexo
      *
      **/
    void DFS();

    /**!
     * Imprime a arvore geradora de busca em largura em um grafo orientado apartir do vertice inicial, v.
     * @param v - vertice inicial.
     **/
    void DFS(int v);

    /**!
     *
     **/
    void greedyBFS(int initialVertex, int finalVertex, int *heuristic);

    /**!
     *
     **/
    void aStarSearch(int initialVertex, int finalVertex, int *heuristic);

};

#include "Graph.cpp"
#endif // GRAPH_H
