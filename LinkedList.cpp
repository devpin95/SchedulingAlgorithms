// Author: Devin Piner
// Filename: LinkedList.cpp
// Description: Implementation of the LinkedList class
// Last Updated: February 16, 2017

#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() { /* EMPTY BODY */ }

LinkedList::LinkedList( const LinkedList& in ) { //COPY CONSTRUCTOR
    //Step through the in linked list and copy the values into the new linked list
    for ( Node* itrPtr = in.headPtr; itrPtr != nullptr; itrPtr = itrPtr->next ) {
        this->insertAtBack( itrPtr->data );
    }
}

LinkedList::~LinkedList() {
    //send headPtr ahead of the iterator so that we can move
    //forward after the delete
    //itrPtr will stay behind to delete the node, and then
    //move to headPtr after the delete
    Node* itrPtr = headPtr; //create a temp pointer
    while ( itrPtr != nullptr ) {
        headPtr = headPtr->next;
        delete itrPtr;
        itrPtr = headPtr;
    }
    size = 0;
    headPtr = nullptr;
}

bool LinkedList::insertAtFront( const T& data ) {
    //Precondition: The data passed in of type T (char)
    //Postcondition: The data is contained in a node object
    // and is at the beginning of the list

    bool success = false;
    Node* currentPtr = new Node;
    currentPtr->data = data;

    //if the list is empty, make the headPtr point
    //to the new node
    if ( size == 0 ) {
        headPtr = currentPtr;
        success = true;
    } else {
        //make currentPtr->next point to headPtr
        currentPtr->next = headPtr;

        //headPtr = currentPtr
        headPtr = currentPtr;

        success = true;
    }

    ++size;

    return success;
}

bool LinkedList::insertAtBack( const T& data ) {
    bool success = false;

    if ( size == 0 ) {
        //if the list is empty, just insert at the front
        success = insertAtFront( data );
    }
    else if ( size == 1 ) {
        //if there is only 1 item in the list

        //create a new node and set its data
        Node *currentPtr = new Node;
        currentPtr->data = data;

        //the headPtr node is the only node in the list, so just set its next to the new node
        headPtr->next = currentPtr;
        ++size;
    }
    else {
        //otherwise there is more than 1 item in the list

        //create a new node and set its data
        Node *currentPtr = new Node;
        currentPtr->data = data;

        //step through the list with an iterator
        //until the nullptr is encountered
        //use node-> next to test for nullptr
        //so that we dont go too far forward
        //before the insertion
        for (Node *itrPtr = headPtr; itrPtr != nullptr; itrPtr = itrPtr->next) {
            if (itrPtr->next == nullptr) {
                itrPtr->next = currentPtr;
                success = true;
                break;
            }
        }

        ++size;
    }
    return success;
}

bool LinkedList::deleteAtFront( void ) {
    bool success = false;

    if ( size == 0 ) {
        //if the list is empty, there are no items to delete
        success = false;
    }
    else if ( size == 1 ) {
        //there is only 1 item in the list

        //delete the headPtr and make it point to null so that it isnt a dangling pointer
        delete headPtr;
        headPtr = nullptr;
        success = true;
        --size;
    } else {
        //otherwise there is more than 1 item in the list

        //make a temp pointer and point it at headPtr
        //move headPtr to the next node so that it isnt lost after the delete
        Node *currentPtr = headPtr;
        headPtr = headPtr->next;

        //delete the temp pointer and make it point to null before the end of the functions
        delete currentPtr;
        currentPtr = nullptr;

        success = true;
        --size;
    }

    return true;
}

bool LinkedList::deleteAtBack( void ) {
    bool success = false;

    if ( size == 0 ) {
        //if the list is empty, dont do anything
        success = false;
    }
    else if ( size == 1 ) {
        //there is only 1 item in the list

        //delete the headPtr and make it point to null now that the list is empty
        delete headPtr;
        headPtr = nullptr;
        success = true;
        --size;
    }
    else {
        //start at the headPtr
        //move forward until we are 1 node from the end of the list
        //send currentPtr ahead to the last node leaving itrPtr at
        //the second to last node
        //delete currentPtr (the last node)
        //and set itrPtr->next (the new last node) to nullptr
        Node *itrPtr = headPtr;

        while (itrPtr->next->next != nullptr) {
            itrPtr = itrPtr->next;
        }

        Node* currentPtr = itrPtr->next;
        itrPtr->next = nullptr;
        delete currentPtr;
        --size;
    }


    return success;
}

bool LinkedList::insertBeforePosition( int index, const T& data ) {
    bool success = false;

    if ( index < 0 || index > size - 1 ) {
        //make sure the index is within the bounds of the list
        success = false;
    }
    else if ( index == 0 ) {
        //if the list is empty, insert, just insert it at the front
        success = insertAtFront( data );
    }
    else {
        //otherwise, the list is not empty

        //step through the list until we get to the target index
        Node* currentPtr = headPtr;
        for ( int i = 0; i < index - 1; ++i ) {
            currentPtr = currentPtr->next;
        }

        //create a new node and set its data
        Node* newPtr = new Node;
        newPtr->data = data;

        //set the new node's next to currentPtr's next
        //and make the currentPtr point to the new node
        newPtr->next = currentPtr->next;
        currentPtr->next = newPtr;
        ++size;
    }

    return success;
}

bool LinkedList::deleteBeforePosition( int index ) {
    bool success = false;

    if ( index < 0 || index > size - 1 ) {
        //make sure the index is within the bounds of the list
        success = false;
    }
    else if ( index == 0 || index == 1 ) {
        //if index is either 0 or 1, delete the headPtr node
        //we are assuming that if 0 is passed in, we just delete the first node
        //and if 1 is passed in, we also delete the first node
        success = deleteAtFront( );
    }
    else {
        //step through the list until we get to the node 2 before
        //the one after the node we are going to delete (we need to know
        //the node before and the node after the target node to be deleted)
        Node* currentPtr = headPtr;
        for ( int i = 0; i < index - 2; ++i ) {
            currentPtr = currentPtr->next;
        }

        Node *deletePtr = currentPtr->next; //make a pointer to point at the target node to delete
        currentPtr->next = deletePtr->next; //make the node to the left point to the node to the right of the target node to delete
        delete deletePtr; //delete the middle node

        --size;
    }

    return success;
}

//void LinkedList::removeDuplicates( ) {
//    //remove duplicates
//    unsigned int count = 0;
//    auto currentPtr = headPtr;
//    bool moved = false;
//    while ( currentPtr->next != nullptr ){
//        moved = false;
//        int frequency = this->frequency( currentPtr->data );
//
//        //if there is more than 1 of this item
//        //delete one of them
//        if ( frequency > 1 ) {
//            //move the current pointer to the next node so that it is not invalidated by the delete
//            currentPtr = currentPtr->next;
//            //flag that we are doing a delete
//            moved = true;
//            //delete the node using deleteBeforePosition, which require the index of the next node
//            //after the one we are trying to delete (count + 1)
//            deleteBeforePosition( count + 1 );
//        }
//
//        if ( !moved ) {
//            currentPtr = currentPtr->next;
//            ++count;
//        }
//    }
//}

void LinkedList::clear() {
    //send headPtr ahead of the iterator so that we can move
    //forward after the delete
    //itrPtr will stay behind to delete the node, and then
    //move to headPtr after the delete
    Node* itrPtr = headPtr; //create a temp pointer
    while ( itrPtr != nullptr ) {
        headPtr = headPtr->next;
        delete itrPtr;
        itrPtr = headPtr;
    }
    size = 0;
    headPtr = nullptr;
}

//bool LinkedList::isPresent( const T& data ) const {
//    bool found = false;
//
//    //step through the array until the target value is found or i is the nullptr
//    for ( auto i = headPtr; i != nullptr; i = i->next ) {
//        if ( i->data == data ) {
//            found = true;
//            break;
//        }
//    }
//
//    //return if the value was found
//    return found;
//}
//
//LinkedList& operator+( const LinkedList& left, const LinkedList& right ) {
//    //operator+()
//    //create a union of the 2 linked lists
//    //
//    //PRECONDITION: left and right are both valid linked lists
//    //POSTCONDITION: The new list is a union of left and right
//
//    //create a new list to hold the union
//    LinkedList *unionList = new LinkedList;
//
//    //step through the first list, checking if the data in the node is already in
//    //the new union list so that duplicates are not added
//    for ( Node* itrPtr = left.headPtr; itrPtr != nullptr; itrPtr = itrPtr->next ) {
//        if ( !unionList->isPresent( itrPtr->data ) ) {
//            unionList->insertAtBack( itrPtr->data );
//        }
//    }
//
//    //step through the second list, checking if the data in the node is already in
//    //the new union list so that duplicates are not added
//    for ( Node* itrPtr = right.headPtr; itrPtr != nullptr; itrPtr = itrPtr->next ) {
//        if ( !unionList->isPresent( itrPtr->data ) ) {
//            unionList->insertAtBack( itrPtr->data );
//        }
//    }
//
//    return *unionList;
//
//}
//
//LinkedList& operator-( const LinkedList& left, const LinkedList& right ) {
//    LinkedList *differenceList = new LinkedList;
//    bool found = false;
//
//    //step though the array
//    for ( Node* i = left.headPtr; i != nullptr; i = i->next ) {
//        for ( Node* j = right.headPtr; j != nullptr; j = j->next ) {
//            //for each value in the left list, check if it is present in the right list
//            if ( j->data == i->data ) {
//                //the value in the left list is present in the right list
//                found = true;
//                break;
//            }
//        }
//        if ( !found ) {
//            //only add the value in the left list if it was not found in the right list
//            differenceList->insertAtBack( i->data );
//        }
//        found = false;
//    }
//
//    //remove all the duplicates from the resulting list
//    differenceList->removeDuplicates();
//
//    return *differenceList;
//}
//
//unsigned int LinkedList::frequency( const T& data ) const {
//    unsigned int count = 0;
//
//    //step through the list and count the number of occurrences of data
//    for ( auto itr = headPtr; itr != nullptr; itr = itr->next ) {
//        if ( itr->data == data ) {
//            ++count;
//        }
//    }
//
//    return count;
//}
//
//LinkedList& LinkedList::operator=( const LinkedList& in ) {
//    //clear the list before the new values are copied over
//    this->clear();
//
//    //copy the values from the in list into the current list
//    for ( Node* itrPtr = in.headPtr; itrPtr != nullptr; itrPtr = itrPtr->next ) {
//        this->insertAtBack( itrPtr->data );
//    }
//
//    return *this;
//}
//
void LinkedList::printVals() const {
    //step through the list and print out the data
    for ( Node* itrPtr = headPtr; itrPtr != nullptr; itrPtr = itrPtr->next ) {
        std::cout << itrPtr->data.pid << " ";
    }
}