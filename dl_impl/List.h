//
// Created by Alessandro on 03/06/22.
//

#ifndef DL_IMPL_LIST_H
#define DL_IMPL_LIST_H
#include <iostream>
class List{
private:
    struct Impl;
    Impl* pimpl;
public:
    List();
    List(const List& l);
    ~List();
    void prepend(int el);
    void append(int el);
    void remove_elem(int el);

    List operator+(const List& l)const;
    List& operator=(const List& l);

    void print();
    void print_rev();
    int& at(int pos);
    const int& at(int pos)const;
};
#endif //DL_IMPL_LIST_H
