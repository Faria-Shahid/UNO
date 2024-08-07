//
// Created by fariy on 1/5/2024.
//

#ifndef UNTITLED_STACK_H
#define UNTITLED_STACK_H


#include <iostream>
#include "SLLNODE.h"

using namespace std;

template<class Q>
class Stack {
    SLLNODE<Q> *head;
    int totalNodes;

public:
    Stack() : head(NULL), totalNodes(0) {}

    SLLNODE<Q> *getHead() const {
        return head;
    }

    void setHead(SLLNODE<Q> *head) {
        Stack::head = head;
    }

    void push(Q value) {
        SLLNODE<Q> *newNode = new SLLNODE<Q>;

        newNode->setData(value);
        newNode->setNext(head);

        head = newNode;

    }

    Q pop() {
        if (head != NULL) {
            SLLNODE<Q> *temp = head;

            head = head->getNext();

            Q tempValue = temp->getData();

            delete temp;

            return tempValue;
        } else {
            cout << "List is currently empty." << endl;
            return Q();
        }
    }

    Q peek() {
        if (head != NULL) {
            return head->getData();
        } else {
            cout << "List is currently empty." << endl;
            return Q();
        }
    }

    int getTotalNodes() {
        SLLNODE<Q> *current = head;
        totalNodes = 0;

        if (current != NULL) {
            while (current != NULL) {
                totalNodes++;
                current = current->getNext();
            }

            return totalNodes;
        }

        return -1;
    }
};

#endif //UNTITLED_STACK_H
