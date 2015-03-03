/**
 * mincut.cpp
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 *
 * Given file which contains the adjacency list representation of a simple undirected graph. 
 * There are 200 vertices labeled 1 to 200. The first column in the file represents the vertex label, 
 * and the particular row (other entries except the first column) tells all the vertices that the vertex
 * is adjacent to. So for example, the 6th row looks like : "6	155	56	52	120	......". 
 * Code up and run the randomized contraction algorithm for the min cut problem and use it on the above graph 
 * to compute the min cut (i.e., the minimum-possible number of crossing edges)
 *
 */
 
#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include <sstream>
#include <unordered_map>
#include <time.h>
#include <stdlib.h>
#include <iterator>
using namespace std;

class Graph {
  int V; 
  unordered_map<int, list<int>> adj;
 public:
  Graph(int v) : V(v) {}
  void addEdge(int v, int w) {
    adj[v].push_back(w);
  }
  void Contract(int v, int w) {
   --V;
   cout << V << "v" << endl;
   adj[v].merge(adj[w]);
   adj.erase(w);
   for (auto i = adj.begin(); i != adj.end(); ++i) {
     if (!(*i).second.empty()) {
       auto it = (*i).second.begin();
       while (it != (*i).second.end()){
         if (*it == w) {
           *it = v;
         }
         ++it;
       }
     }
   }
   auto it = adj[v].begin();
   while (it != adj[v].end()) {
     if (v == *it) {
       it = adj[v].erase(it);
     } else {
       ++it;
     }
   }
  } 
  int GetMinCut() {
   int rand_v, rand_w;
    while (V > 2) {
      rand_v = rand() % V;
      auto i = adj.begin();
      while (rand_v) {
        ++i;
        rand_v--;
      }
      rand_v = i->first;
      rand_w = rand() % adj[rand_v].size();
      auto j = adj[rand_v].begin();
      while (rand_w) {
        ++j;
        rand_w--;
      }
      rand_w = *j; 
      Contract(rand_v, rand_w);
    }
    return adj.begin()->second.size();
  } 
};

int main() {
  srand (time(NULL));
  Graph g(200);
  ifstream fin("kargerMinCut.txt");
  string line;
  if (fin.is_open()) {
    cout << "File Opened successfully!!!. Reading data from file into array" << endl;
    while (getline(fin, line)) {
      int v;
      int w;
      istringstream line_stream(line);
      line_stream >> v;
      while (line_stream >> w) {
        g.addEdge(v, w);
      }
    }
  }
  fin.close();
  cout << g.GetMinCut() << " - answer" << endl;
}
