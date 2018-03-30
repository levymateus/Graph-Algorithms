#include "Graph.h"

Graph::Graph(int vertices)
{
    this->vertices = vertices;
    this->m_adj = new list<int>[vertices];
}

void Graph::addEdge(int vertex, int edge)
{
    this->m_adj[vertex].push_back(edge);
}

void Graph::DFS(int v, bool visited[], int &coast)
{
  visited[v] = true;
  char c = ((char) v + 'A');
  cout << c << " ";
  list<int>::iterator i;

  for(i = m_adj[v].begin(); i != m_adj[v].end(); i++)
    if(!visited[*i]) DFS(*i, visited, ++coast);
}

void Graph::DFS(int v)
{
  int coast = 0;
  bool *visited = new bool[vertices];

  for(int i = 0; i < vertices; i++) visited[i] = false;// marca todos os vertices como nao visitados

  DFS(v, visited, coast);
  cout << "coast=" << coast << endl;

}

void Graph::DFS()
{
  bool *visited = new bool[vertices];

  // marcar todos os vertices como nao visitados
  for(int i = 0; i < vertices; i++) visited[i] = false;
  list<int>::iterator j;

  // Checa cada vertice do grafo, se o vertice nao for visitado, marca como visitado
  for(int i = 0; i < vertices; i++)
  {
    if(!visited[i])
    {
      visited[i] = true;
      char c = (char) i + 'A';
      cout << c << " ";
      for(j = m_adj[i].begin(); j != m_adj[i].end(); j++)
      {
        if(!visited[*j])
        {
          visited[*j] = true;
          c = (char) *j + 'A';
          cout << c << " ";
        }
      }
    }
  }

  cout << endl;

}

void Graph::BFS(int currVertexVertex)
{
  int coast = 0;
  list<int> queue;
  bool *visited = new bool[vertices];// cada indice representa um vértice e se ele ja foi visitado

  // primeiro, garantir se existe o vértice de partida...
  if(currVertexVertex < 0 || currVertexVertex > vertices)
  {
    cout << currVertexVertex << " vertex don't exist ..." << endl;
    return;
  }

  for(int i = 0; i < vertices; i++) visited[i] = false;// todos os vértices, primeiramente, são marcados como nao visitados

  visited[currVertexVertex] = true;// inicia-se o vertice inicial como marcado
  queue.push_back(currVertexVertex);// coloca o vertice inicial no final da fila

  list<int>::iterator it;

  while(!queue.empty())
  {

    // desenfileirar o primeiro elemento da fila
    int currVertex = queue.front();
    char c = ((char) currVertex + 'A');
    cout << c << " ";
    queue.pop_front();

    // checa todos os nós vizinhos do no desenfileirado
    for(it = m_adj[currVertex].begin(); it !=  m_adj[currVertex].end(); it++)
    {
      if(!visited[*it]){
        visited[*it] = true;
        queue.push_back(*it);
        coast += 1;
      }
    }

  }

  cout << "total=" << coast << endl;

}

// nunca olhar para traz nem adiante
// de B até J funciona
// heuristica de desenpate: quantidade de filhos e se algum deles tem o no alvo
void Graph::greedyBFS(int initialVertex, int finalVertex, int* heuristic){

  list<int>::iterator it;
  int custo = 0;
  int vAtual = initialVertex;
  int vProx;
  list<int> list;

  cout << "chegar ate " << (char)(finalVertex+'A') << endl;

  while(vAtual != finalVertex && !m_adj[vAtual].empty())
  {
    int custoAtual = heuristic[m_adj[vAtual].front()]; // começa com o custo da primeira adjacencia
    vProx = m_adj[vAtual].front(); // assume por hora que o proximo nó sera a primeira adjacencia da lista

    cout << "vAtual = " << (char) (vAtual+'A') << "[" << heuristic[ vAtual ] << "]" << endl;

    /**
     * Visita-se todas as ajacencias e escolhe a com o menor custo para ser o proximo vertice do caminho
     */

    for (it = m_adj[vAtual].begin(); it != m_adj[vAtual].end(); it++)
    {
      cout << (char) (*it+'A') << "[" << heuristic[ *it ] << "] ";

      if(*it == finalVertex)
      {
        vProx = *it;
        custoAtual = heuristic[*it];
        break;
      }

      if (custoAtual > heuristic[ *it ])
      {
        // atualiza-se o proximo vertice e o custo atual
        vProx = *it;
        custoAtual = heuristic[ *it ];
      }
      else if (custoAtual == heuristic[*it])
      {
        cout << "empate ";
        // aplicar heuristica.
        // 1 - colocar em uma fila de prioridades (eliminando os que tem menos filhos)
        list.push_back(*it);
      }
    }

    if(!list.empty()){
      list.sort();
      vProx = list.front();
      cout << "escolhe" << (char) (vProx+'A') << endl;
      list.clear();
    }

    custo += custoAtual;
    vAtual = vProx; // O vertice atual passa a ser o que seria o proximo vertice
    cout << "custo=" << custo << endl;
  }

}

int Graph::expandir(int finalVertex, int *heuristic, int custo, list<int> &mList)
{
  // 3 - aplicar heuristica nos filhos
  list<int>::iterator i, j;
  int vProx = mList.front();
  int custoAtual = heuristic[vProx];
  list<int> list;

  for(i = mList.begin(); i != mList.end(); i++)
  {
    cout << "expandir no " << (char) (*i+'A') << endl;

    if(*i == finalVertex)
    {
      vProx = *i;
      custoAtual = heuristic[*i];
      return vProx;
    }

    for (j = m_adj[*i].begin(); j != m_adj[*i].end() && !m_adj[*i].empty(); j++)
    {
      cout << (char) (*j+'A') << "[" << heuristic[ *j ] << "] ";

      if (custoAtual > (custo + heuristic[ *i ]) )
      {
        // atualiza-se o proximo vertice e o custo atual
        vProx = *j;
        custoAtual = heuristic[ *j ];
      }
      else if (custoAtual == heuristic[*j])
      {
        cout << "empate ";
        // aplicar heuristica.
        // 1 - colocar em uma fila
        list.push_back(*j);
      }
    }
  }

  if(!list.empty()){
    // 2 - expandir os filhos
    expandir(finalVertex, heuristic, custo, list);
  }

  custo += custoAtual;
  return vProx;
}

void Graph::aStarSearch(int initialVertex, int finalVertex, int *heuristic)
{
  list<int>::iterator it;
  int custo = 0;
  int vAtual = initialVertex;
  int vProx;
  list<int> list;

  cout << "chegar ate " << (char)(finalVertex+'A') << endl;

  while(vAtual != finalVertex && !m_adj[vAtual].empty())
  {
    int custoAtual = heuristic[m_adj[vAtual].front()]; // começa com o custo da primeira adjacencia
    vProx = m_adj[vAtual].front(); // assume por hora que o proximo nó sera a primeira adjacencia da lista

    cout << "vAtual = " << (char) (vAtual+'A') << "[" << heuristic[ vAtual ] << "]" << endl;

    /**
     * Visita-se todas as ajacencias e escolhe a com o menor custo para ser o proximo vertice do caminho
     */

    for (it = m_adj[vAtual].begin(); it != m_adj[vAtual].end(); it++)
    {
      cout << (char) (*it+'A') << "[" << heuristic[ *it ] << "] ";

      if(*it == finalVertex)
      {
        vProx = *it;
        custoAtual = heuristic[*it];
        break;
      }

      if (custoAtual > (custo + heuristic[ *it ]) )
      {
        // atualiza-se o proximo vertice e o custo atual
        vProx = *it;
        custoAtual = heuristic[ *it ];
      }
      else if (custoAtual == heuristic[*it])
      {
        cout << "empate ";
        // aplicar heuristica.
        // 1 - colocar em uma fila
        list.push_back(*it);
      }

      cout << endl;
    }

    if(!list.empty()){
      // 2 - expandir os filhos
      expandir(finalVertex, heuristic, custo, list);
    }

    custo += custoAtual;
    vAtual = vProx; // O vertice atual passa a ser o que seria o proximo vertice
    cout << "custo=" << custo << endl;
  }
}
