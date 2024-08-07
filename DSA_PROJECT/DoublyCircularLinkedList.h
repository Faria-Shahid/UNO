//
// Created by fariy on 12/20/2023.
//

#ifndef UNTITLED_DOUBLYCIRCULARLINKEDLIST_H
#define UNTITLED_DOUBLYCIRCULARLINKEDLIST_H

#include <iostream>
#include "DLLNode.h"

using namespace std;

template<class P>
class DoublyCircularLinkedList {
    DLLNode<P> *head;
    DLLNode<P> *tail;

public:
    DoublyCircularLinkedList() : head(nullptr), tail(nullptr) {}

    DLLNode<P> *getHead() const {
        return head;
    }

    void setHead(DLLNode<P> *head) {
        DoublyCircularLinkedList::head = head;
    }

    DLLNode<P> *getTail() const {
        return tail;
    }

    void setTail(DLLNode<P> *tail) {
        DoublyCircularLinkedList::tail = tail;
    }

    void insert(const P &value) {
        DLLNode<P> *newNode = new DLLNode<P>();
        newNode->setData(value);

        if (!head) {
            newNode->setNext(newNode);
            newNode->setPrev(newNode);
            head = tail = newNode;
        } else {
            newNode->setNext(head);
            newNode->setPrev(tail);
            head->setPrev(newNode);
            tail->setNext(newNode);
            head = newNode;
        }
    }

    P remove() {
        if (head != NULL) {
            DLLNode<P> *temp = head;
            P tempValue = temp->getData();
            head = head->getNext();
            head->setPrev(tail);
            temp->setNext(nullptr);
            delete temp;
            return tempValue;
        } else {
            cout << "List is currently empty." << endl;
            return P();
        }
    }

    P searchByPosition(int pos) {
        DLLNode<P> *current = getHead();

        if (current != NULL) {
            int i = 0;
            while (i != current - 1) {
                current = current->getNext();
                i++;
            }

            return current->getData();
        }
        return P();
    }

};


#endif //UNTITLED_DOUBLYCIRCULARLINKEDLIST_H
