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
    LinkedList( void ) = default;
    LinkedList( const LinkedList& );
    ~LinkedList( void );
    bool insertAtFront( const T& );
    bool insertAtBack( const T& );
    bool deleteAtFront( void );
    inline int length( void ) { return size; }
    bool deleteAtBack( void );
    bool insertBeforePosition( int, const T& );
    bool deleteBeforePosition( int );


    //helper functions
    void clear( void );
    inline bool empty() const { return size == 0; }
    void printVals( void ) const ;

    class LLIterator {
    public:
        // TODO DO THE MOV OP
        LLIterator( ) = default;
        explicit LLIterator( Node* n ) { ptr = n; };
        LLIterator( const LLIterator& l ) { ptr = l.ptr; };
        LLIterator& operator=( const LLIterator& l ) {
            if ( &l == this ) {
                return *this;
            }
            ptr = l.ptr;
            return *this;
        };
        const PCB& operator*( ) const { if (  ptr != nullptr ) return ptr->data; };
        PCB& operator*( ) { if (  ptr != nullptr ) return ptr->data; };
        void operator++( ) { if (  ptr != nullptr ) ptr = ptr->next; };
        bool operator!=( const LLIterator &l ) { return ptr != l.ptr;  };
    private:
        Node* ptr = nullptr;
    };

    LLIterator begin( void ) const { return LLIterator(headPtr); };
    LLIterator end( void ) const { return LLIterator(nullptr); };

private:
    Node* headPtr = nullptr;
    unsigned int size = 0;
};


#endif //LINKEDLIST_H
