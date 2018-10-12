// Modified By: Devin Piner
// Filename: LinkedList.h
// Description: Interface of the LinkedList class
// Last Updated: February 20, 2017

#ifndef HW5_LINKEDLIST_H
#define HW5_LINKEDLIST_H

#include "Node.h"
#include "PCB.h"


typedef struct PCB T;

class LinkedList {
public:
    //required functions
    LinkedList( void );
    LinkedList( const LinkedList& );
    ~LinkedList( void );
    bool insertAtFront( const T& );
    bool insertAtBack( const T& );
    bool deleteAtFront( void );
    inline int length( void ) { return size; }
    bool deleteAtBack( void );
    bool insertBeforePosition( int, const T& );
    bool deleteBeforePosition( int );
//    friend LinkedList& operator+( const LinkedList&, const LinkedList& );
//    friend LinkedList& operator-( const LinkedList&, const LinkedList& );

    //helper functions
//    void removeDuplicates( void );
    void clear( void );
//    bool isPresent( const T& ) const;
//    unsigned int frequency( const T& ) const;
//    LinkedList& operator=( const LinkedList& );
    void printVals( void ) const ;

private:
    Node* headPtr = nullptr;
    unsigned int size = 0;
};


#endif //HW5_LINKEDLIST_H
