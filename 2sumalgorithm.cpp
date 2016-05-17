/*
 * 2sumalgorithm.cpp
 *
 * Aksana Kuzmitskaya
 * aksana.kuzmitskaya@gmail.com
 *
 * The goal of this problem is to implement a variant of the 2-SUM algorithm 
 * (covered in the Week 6 lecture on hash table applications).
 * The file contains 1 million integers, both positive and negative 
 * (there might be some repetitions!).This is your array of integers, 
 * with the ith row of the file specifying the ith entry of the array.
 * Your task is to compute the number of target values t in the interval 
 * [-10000,10000] (inclusive) such that there are distinct numbers x,y 
 * in the input file that satisfy x+y=t. (NOTE: ensuring distinctness 
 * requires a one-line addition to the algorithm from lecture.)
 * Write your numeric answer (an integer between 0 and 20001) in the space provided.
 * 
 */

#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

// since the numbers are in the rande [-10000, 10000] prime number around 10000 * 4
#define NUMBER_OF_BACKETS 583777   


class HashTable{
    int hashFunction( long long val ) {
        int g = val >> 16 ;
        return g % NUMBER_OF_BACKETS ;
	}
    std::vector< std::list<long long> > backets ;
    int size ;
public:
	std::list< long long > & value( int key ) { return backets[key] ; }
	bool find( const long long & val ) {
		int hashCode = hashFunction( val ) ;
        if ( backets[hashCode].empty() ) 
            return false ;
		return backets[hashCode].end() != std::find( backets[hashCode].begin() , backets[hashCode].end() , val ) ; 
	}
	void add( const long long & val ) {
		int hashCode = hashFunction( val ) ;
		if ( find( val ) ) 
			return ;
        ++size ;
		backets[hashCode].push_front( val ) ; 
	}
    int getSize() const { return size ; } ;
	HashTable( ) : size(0) { backets.resize( NUMBER_OF_BACKETS + 1 ) ; }
} ;

int main() {
      
	std::ifstream fid(  "algo1-programming_prob-2sum.txt"  ) ;
	if ( !fid.is_open() ) {
		std::cout <<  "Failed to open the file." << std::endl ;
		return 1 ;
	}
	long long val ;
	HashTable hTable ;
	int i = 0 ;
	while ( fid >> val ) {
		hTable.add( val ) ;
	}
    int size = hTable.getSize() ;
    std::cout <<  "Values are in hasht with size " << size << std::endl ;
    size /= 2 ;
	int count = 0 ;
	for ( int i = -10000 ; i < 10001 ; ++i ) {
        bool found = false ;
        int sizeCount = 0 ;
		for ( int j = 0 ; !found && sizeCount < size && j < NUMBER_OF_BACKETS ; ++j ) {
			std::list< long long > & listV = hTable.value( j ) ;
            if ( !listV.empty() ) {
                for ( std::list< long long >::iterator it = listV.begin() ; !found && it != listV.end() ; ++it ) {
                    ++sizeCount ;
                    long long dif = i - *it ;
                    if ( dif != *it && hTable.find( dif ) ) {
                        ++count ;
                        found = true ;
                    }
                }  
            }
		}
	}
    std::cout <<  "Answer: " << count << std::endl ;
	fid.close() ;
}
