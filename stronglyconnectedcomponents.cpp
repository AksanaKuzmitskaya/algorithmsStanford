 /*
 * stronglyconnectedcomponents
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 *
 * "SCC.txt" file contains the edges of a directed graph. Vertices are labeled as positive integers from 1 to 875714. 
 * Every row indicates an edge, the vertex label in first column is the tail and the vertex label in second 
 * column is the head (recall the graph is directed, and the edges are directed from the first column vertex 
 * to the second column vertex). So for example, the 11th row looks liks : "2 47646". This just means that 
 * the vertex with label 2 has an outgoing edge to the vertex with label 47646
 * Your task is to code up the algorithm from the video lectures for computing strongly connected components (SCCs), 
 * and to run this algorithm on the given graph. 
 * Output Format: You should output the sizes of the 5 largest SCCs in the given graph, in decreasing order of sizes, 
 * separated by commas (avoid any spaces). 
 * So if your algorithm computes the sizes of the five largest SCCs to be 500, 400, 300, 200 and 100, 
 * then your answer should be "500,400,300,200,100". If your algorithm finds less than 5 SCCs, 
 * then write 0 for the remaining terms. Thus, if your algorithm computes only 3 SCCs whose sizes are 400, 300, and 100, 
 * then your answer should be "400,300,100,0,0".
 *
 */

#include <vector> 
#include <iostream>
#include <fstream>
#include <stack>

#define NUM_OF_SIZES 5
#define NUM_VERTICES 875714

class Graph {
	std::vector< std::vector< int > > g , gHelper ;
	std::vector< bool > visited ;
	std::vector< int >  f , sizesOfScc ;
    int sccSize , t , numEdges ;
	void DFSRev( const int i ) ;
	void DFS( const int i ) ;
    void setFVisitedFT() ;
    void cleareVisitedFT() ;
    void insertSizeInSortedOrder( const int sccSize ) ;
public:
	const int getNumEdges() const { return numEdges ; }
    void printSCCSizes() const ;
	void insertEdge( const int vertex1 , const int vertex2 ) ;
	void DFSHelper( bool onRev = false ) ;
	void transformG() ;
	Graph() ;
} ;

void Graph::DFSRev( const int i ) {
    std::stack< int > stack ;
    stack.push( i ) ;
    int top ;
	while( !stack.empty() ) {
        top = stack.top() ;
        visited[top] = true ;
        bool hasUnvisited = false ;
        for ( int j = int( gHelper[top].size() - 1 ) ; j >= 0 ; --j ) {
            if ( !visited[gHelper[top][j]] ) {
                visited[gHelper[top][j]] = true ;
			    stack.push( gHelper[top][j] ) ;
                hasUnvisited = true ;
            } 
		} 
        if ( !hasUnvisited ) {
            f[top] = t ;
            ++t ;
            stack.pop() ;
        }
    }
}
void Graph::DFS( const int i ) {
    sccSize = 0 ;
    std::stack< int > stack ;
    stack.push( i ) ;
	while( !stack.empty() ) {
        int top = stack.top() ;
        stack.pop() ;
        if ( !visited[top] ) {
            ++sccSize ;
            visited[top] = true ;
            for ( int j = int( gHelper[top].size() - 1 ) ; j >= 0 ; --j ) {
                if ( !visited[gHelper[top][j]] ) {
			        stack.push( gHelper[top][j] ) ;
                }
            }
		}
    }
    insertSizeInSortedOrder( sccSize ) ; 
}
void Graph::setFVisitedFT() {
    visited.resize( NUM_VERTICES , false ) ;
    f.resize( NUM_VERTICES ) ;
    t = 0 ; 
    sccSize = 0 ;
}
void Graph::cleareVisitedFT() {
    visited.clear() ;
    f.clear() ;
    gHelper.clear() ;
}
void Graph::insertSizeInSortedOrder( const int sccSize ) {
    int i = NUM_OF_SIZES - 1  ; 
    while( i >= 0 && sizesOfScc[i] <= sccSize ) {
        --i ;
    }
    ++i ;
    if ( i < NUM_OF_SIZES ) {
        int j = NUM_OF_SIZES - 2 ;
        while( j >= i ) {
            sizesOfScc[j+1] = sizesOfScc[j] ;
            --j ;
        }
        sizesOfScc[i] = sccSize ;
    }
}
void Graph::printSCCSizes() const { 
    int i ;
    for ( i = 0 ; i != NUM_OF_SIZES - 1 ; ++i )
        std::cout << sizesOfScc[i] << "," ;
    std::cout << sizesOfScc[i] << "." << std::endl ;
}
void Graph::insertEdge( const int vertex1 , const int vertex2 ) {
	g[vertex1 - 1].push_back( vertex2 - 1 ) ; 
	gHelper[vertex2 - 1].push_back( vertex1 - 1 ) ; 
	++numEdges ; 
}
void Graph::DFSHelper( bool onRev ) {
    setFVisitedFT() ;
	for ( int i = NUM_VERTICES - 1 ; i >= 0 ; --i ) {
	    if ( !visited[i] ) {
            if ( onRev )
				DFSRev( i ) ;
            else 
                DFS( i ) ;
		}
	}
    cleareVisitedFT() ;
}
void Graph::transformG() {
    gHelper.resize( NUM_VERTICES ) ;
	for ( int i = 0 ; i < NUM_VERTICES ; ++i ) {
        gHelper[f[i]].assign( g[i].begin() , g[i].end() ) ;
		for ( int j = 0 ; j < g[i].size() ; ++j ) {
			gHelper[f[i]][j] = f[g[i][j]] ;
		}
	}
}
Graph::Graph() : numEdges( 0 ) { 
	g.resize( NUM_VERTICES ) ; 
	gHelper.resize( NUM_VERTICES ) ; 
    sizesOfScc.resize( NUM_OF_SIZES ) ;
}

int main() {
	std::ifstream fid( "SCC.txt" ) ;
	if ( !fid.is_open() ) {
		std::cout <<  "Failed to open the file." << std::endl ;
		return 1 ;
	}
	Graph graph ;
	int vertex1 ;
	int vertex2 ;
	while ( fid >> vertex1 >> vertex2 ) {
		graph.insertEdge( vertex1 , vertex2 ) ;
	}
	fid.close() ;
	std::cout << "Number of edges: " << graph.getNumEdges() << std::endl ;
    bool onRev = true ;
// DFS on reversed graph
	graph.DFSHelper( onRev ) ;
// changed the nodes on regular graph for finishing times from reversed graph
	graph.transformG() ; 
// DFS in decreasing order of finishing times 
    graph.DFSHelper( ) ;
    std::cout << "The sizes of the 5 largest SCCs in the given graph: " ;
    graph.printSCCSizes() ;
}
