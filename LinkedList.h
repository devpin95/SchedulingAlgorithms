// Modified By: Devin Piner
// Filename: LinkedList.h
// Description: Interface of the LinkedList class
// Last Updated: February 20, 2017

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Node.h"
#include "PCB.h"

class LLIterator;
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

    LLIterator begin( void ) const;
    LLIterator end( void ) const;

//    friend LinkedList& operator+( const LinkedList&, const LinkedList& );
//    friend LinkedList& operator-( const LinkedList&, const LinkedList& );

    //helper functions
//    void removeDuplicates( void );
    void clear( void );
//    bool isPresent( const T& ) const;
//    unsigned int frequency( const T& ) const;
//    LinkedList& operator=( const LinkedList& );
    void printVals( void ) const ;

    class LLIterator {
    public:
        // TODO DO THE MOV OP
        LLIterator( ) { /* EMPTY BODY */ };
        LLIterator( Node* n ) { ptr = n; };
        LLIterator( const LLIterator& l ) { ptr = l.ptr; };
        LLIterator& operator=( const LLIterator& l ) { ptr = l.ptr; };
        const PCB& operator*( ) { if (  ptr != nullptr ) return ptr->data; };
        void operator++( ) { if (  ptr != nullptr ) ptr = ptr->next; };
    private:
        Node* ptr = nullptr;
    };

private:
    Node* headPtr = nullptr;
    unsigned int size = 0;
};


#endif //LINKEDLIST_H
