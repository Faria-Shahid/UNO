//
// Created by fariy on 12/20/2023.
//

#ifndef UNTITLED_DOUBLYLINKEDLIST_H
#define UNTITLED_DOUBLYLINKEDLIST_H

#include <iostream>
#include "DLLNode.h"

using namespace std;

template<class Q>
class DoublyLinkedList {
    DLLNode<Q> *head;
    int numberOfNodes = 0;

public:
    DoublyLinkedList() : head(nullptr) {}

    DLLNode<Q> *getHead() const {
        return head;
    }

    void setHead(DLLNode<Q> *head) {
        DoublyLinkedList::head = head;
    }

    void insert(Q value) {
        DLLNode<Q> *newNode = new DLLNode<Q>;

        newNode->setData(value);
        newNode->setNext(head);

        if (head != nullptr) {
            head->setPrev(newNode);
        }

        head = newNode;
    }

//    Q removeFromHead() {
//        if (head != NULL) {
//            DLLNode<Q> *temp = head;
//            Q tempValue = temp->getData();
//            head = head->getNext();
//
//            if (head != NULL) {
//                head->setPrev(NULL);
//            }
//
//            delete temp;
//            return tempValue;
//        } else {
//            cout << "List is currently empty." << endl;
//            return Q();
//        }
//    }

    Q removeFromHead() {
        if (head == nullptr) {
            std::cout << "The list is empty. Cannot remove head." << std::endl;
            return Q();
        }

        if (head->getNext() == nullptr) {
            // Only one element in the list
            delete head;
            head = nullptr;
            return Q();
        } else {
            // More than one element in the list
            DLLNode<Q>* newHead = head->getNext();
            newHead->setPrev(nullptr) ;
            Q temp = head->getData();
            delete head;
            head = newHead;
            return temp;
        }

    }


    Q removeFromTail() {
        if (head != nullptr) {
            DLLNode<Q> *temp = head;
            DLLNode<Q> *prev;

            do {
                temp = temp->getNext();
            } while (temp->getNext() != nullptr);

            Q tempValue = temp->getData();

            prev = temp->getPrev();

            prev->setNext(nullptr);

            delete temp;

            return tempValue;
        } else {
            cout << "List is currently empty.";
            return Q();
        }
    }

    Q removeInBetween(Q data) {
        DLLNode<Q> *current = getHead();
        DLLNode<Q> *prev;
        DLLNode<Q> *next;

        if (current != nullptr) {
            while (current != nullptr) {
                if (current->getData() == data) {
                    break;
                }
                current = current->getNext();
            }

            prev = current->getPrev();
            next = current->getNext();

            prev->setNext(next);
            next->setPrev(prev);

            Q tempValue = current->getData();

            delete current;

            return tempValue;
        } else {
            cout << "List is currently empty.";
            return Q();
        }
    }

    Q removeFromList(DLLNode<Q>*key){
        Q data;

        if (key->getPrev()== nullptr){
            data=removeFromHead();
        }

        else if (key->getNext()== nullptr){
            data=removeFromTail();
        }

        else {
            data = removeInBetween(key->getData());
        }

        return data;
    }

    int totalNodes() {
        DLLNode<Q> *current = getHead();

        numberOfNodes=0;

        if (current != nullptr) {
            while (current != nullptr) {
                numberOfNodes++;
                current = current->getNext();
            }

            return numberOfNodes;
        }

        return -1;
    }


};


#endif //UNTITLED_DOUBLYLINKEDLIST_H
