//
// Created by fariy on 12/22/2023.
//

#ifndef UNTITLED_DLLNODE_H
#define UNTITLED_DLLNODE_H

#include <iostream>

using namespace std;

template<class T>
class DLLNode{
    T data;
    DLLNode *next,*prev;

public:
    DLLNode(): data(T()), next(NULL), prev(NULL){}

    void setData(T data) {
        DLLNode::data = data;
    }

    void setNext(DLLNode *next) {
        DLLNode::next = next;
    }

    T getData() const {
        return data;
    }

    DLLNode *getNext() const {
        return next;
    }

    DLLNode *getPrev() const {
        return prev;
    }

    void setPrev(DLLNode *prev) {
        DLLNode::prev = prev;
    }


};

#endif //UNTITLED_DLLNODE_H
