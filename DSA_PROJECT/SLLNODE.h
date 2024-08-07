//
// Created by fariy on 12/26/2023.
//

#ifndef UNTITLED_SLLNODE_H
#define UNTITLED_SLLNODE_H

#include <iostream>

using namespace std;

template<class T>
class SLLNODE {
    T data;
    SLLNODE *next;

public:
    SLLNODE():data(T()),next(NULL){}

    T getData() const {
        return data;
    }

    void setData(T data) {
        SLLNODE::data = data;
    }

    SLLNODE *getNext() const {
        return next;
    }

    void setNext(SLLNODE *next) {
        SLLNODE::next = next;
    }


};


#endif //UNTITLED_SLLNODE_H
