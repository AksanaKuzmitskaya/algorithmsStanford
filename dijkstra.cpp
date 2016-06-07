/*
 * dijkstra.cpp
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * In this programming problem you'll code up Dijkstra's shortest-path algorithm.  
 * The file contains an adjacency list representation of an undirected weighted graph 
 * with 200 vertices labeled 1 to 200. Each row consists of the node tuples that are 
 * adjacent to that particular vertex along with the length of that edge. For example, 
 * the 6th row has 6 as the first entry indicating that this row corresponds to the 
 * vertex labeled 6. The next entry of this row "141,8200" indicates that there is an 
 * edge between vertex 6 and vertex 141 that has length 8200. 
 * The rest of the pairs of this row indicate the other vertices adjacent to vertex 
 * 6 and the lengths of the corresponding edges.
 * Your task is to run Dijkstra's shortest-path algorithm on this graph, using 1 (the first vertex) 
 * as the source vertex, and to compute the shortest-path distances between 1 and every other 
 * vertex of the graph. If there is no path between a vertex v and vertex 1, we'll define the 
 * shortest-path distance between 1 and v to be 1000000. 
 * You should report the shortest-path distances to the following ten vertices, 
 * in order: 7,37,59,82,99,115,133,165,188,197. You should encode the distances 
 * as a comma-separated string of integers.
 * 
 */
 
 #include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <queue>

class Graph {
    typedef std::pair< int , int > pair ;
	std::vector< std::vector< const pair > > g ;
	std::vector< bool > visited ;
	std::vector< int >  shortestPathDs ;
    int numEdges ;
    int numVertices ; 
    struct greaterByDistance ;
	void dijkstraHelper( const pair & start ) ;
public:
    const int getnumVertices() const { return numVertices ; }
	const int getNumEdges() const { return numEdges ; }
	void insertEdge( const int vertex1 , const int vertex2 , const int weight ) ;
    void printShortestPathDs( const int * vertices , const int size ) ; 
	void dijkstra( ) ;
	Graph( const int capacity ) ;
} ;

struct Graph::greaterByDistance {
    bool operator()( const pair & p1 ,  const pair & p2 ) {
        return p1.second > p2.second ; 
    }
} ;

void Graph::dijkstraHelper( const pair & start ) {
    std::priority_queue< const pair , std::vector< const pair > , greaterByDistance > unvisited ;
    unvisited.push( start ) ;
	while( !unvisited.empty() ) {
    // getting vertex with the smallest distance 
        int top = unvisited.top().first ;
        unvisited.pop() ;
        if ( visited[top] ) 
            continue ;
        visited[top] = true ;
        int gTopSize = int( g[top].size() ) ;
        for ( int j = 0 ; j < gTopSize ; ++j ) {
            int vertex = g[top][j].first ;
            if ( visited[vertex] ) 
                continue ;
            int distance = g[top][j].second + shortestPathDs[top] ;
        // == 0  - the path from start vertex to current vertex was not explored yet
            if ( shortestPathDs[vertex] == 0 || shortestPathDs[vertex] > distance ) 
                shortestPathDs[vertex] =  distance ;
			unvisited.push( std::make_pair( vertex , distance ) ) ;
        }	
    }
}

void Graph::insertEdge( const int vertex1 , const int vertex2 , const int weight ) {
	g[vertex1 - 1].push_back( std::make_pair( vertex2 - 1 ,  weight ) ) ; 
	++numEdges ; 
}
void Graph::dijkstra( ) {
    pair start ( 0 , 0 ) ; 
    dijkstraHelper( start ) ;
}
void Graph::printShortestPathDs( const int * vertices , const int size ) {
    std::cout << "--> Shortest Path Distances from start vertex are: " << std::endl ;
    for ( int i = 0 ; i < size ; ++i ) {
        std::cout << shortestPathDs[vertices[i]-1] ; 
        i < ( size - 1 ) ? std::cout << ',' : std::cout << '.' ;
    }
}  
Graph::Graph( const int nVertices ) : numEdges( 0 ) , numVertices( nVertices ) { 
	g.resize( numVertices ) ; 
    visited.resize( numVertices ) ;
    shortestPathDs.resize( numVertices ) ;
}

int main() {
	std::ifstream fid( "C:/Users/ak18902/Documents/dijkstraData.txt" ) ;
	if ( !fid.is_open() ) {
		std::cout <<  "Failed to open the file." << std::endl ;
		return 1 ;
	}
    int sizeG = 200 ;
    Graph graph( sizeG ) ;
	{
        int vertex1 ;
        int vertex2 ;
        int weight ;
        char temp ;
        std::string line ;
        while ( std::getline( fid , line ) ) {
            std::stringstream stream( line ) ;
            stream >> vertex1 ;
            while( stream >> vertex2 >> temp >> weight ) 
		        graph.insertEdge( vertex1 , vertex2 , weight ) ;
        }
        std::cout << "--> The graph was created.\nNumber of edges: " << graph.getNumEdges() 
                  << ".\nNumber of verteces: " << graph.getnumVertices() << '.' << std::endl ;
    }
    fid.close() ;
    graph.dijkstra() ;
    const int size = 10 ;
    const int vertices[size] = { 7 , 37 , 59 , 82 , 99 , 115 , 133 , 165 , 188 , 197 } ;
    graph.printShortestPathDs( vertices , size ) ; 
}
