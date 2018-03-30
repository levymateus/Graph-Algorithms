#include "Graph.h"
#include <fstream>
#include <string.h>

int main(int argc, char const *argv[]) {

  char str[256];

  if(!argv[1]){

    std::cout << "Enter the name of an existing text file: ";
    std::cin.get (str,256);    // get c-string

  }else{

    strcpy(str, argv[1]);
    std::cout << str << std::endl;

  }

  std::ifstream is(str);     // open file

  char c;
  bool let[256] = { false };
  int vertices = 0;

  /**
   * conta o numero de vertices que o grafo ira ter
   */
  while (is.get(c)){
    int i = (int) c;
    if(let[i] == false && c != '/' && c != '\n'){
      vertices++;
      let[i] = true;
    }

  }

  std::ifstream ifs(str);
  Graph g(vertices);
  char line[4];

  while (ifs.getline(line, 4)){
    g.addEdge(line[0] - 'A', (int) line[2] - 'A');
  }

  std::cout << "DFS=";
  g.DFS(1);
  std::cout << "\nBFS=";
  g.BFS(1);
  std::cout << "\ngreedBFS=" << endl;
  int h[] = { 2, 1, 3, 2, 3, 2, 3, 3, 3, 4, 4, 4 };
  g.greedyBFS(1, 9, h);
  std::cout << "\nA*=" << endl;
  g.aStarSearch(1, 9, h);

  is.close();                // close file

  return 0;
}
