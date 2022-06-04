//
// Created by Alessandro on 04/06/22.
//
#include "stack.hpp"
struct Stack::Impl{
    int info;
    Impl* next;
};

Stack::Stack() {
    pimpl = nullptr;
}
Stack::Stack(const Stack &s) {
    Impl* pc =s.pimpl;
    Impl* final;
    Impl* prev= nullptr;
    while(pc->next){
       final =new Impl;
       final->info =pc->info;
       if(pimpl ==nullptr){
           pimpl = final;
       }else{
           prev->next = final;
       }
       prev =final;
       pc = pc->next;
    }
}

Stack::~Stack() {
    Impl* pc;
    while(pimpl){
        pc =pimpl;
        pimpl = pimpl->next;
        delete pc;
    }
}

void Stack::push(int el) {
    Impl* pc =new Impl;
    pc->info = el;
    pc->next = pimpl;
    pimpl = pc;
}

int Stack::pop() {
    int result;
    if(pimpl){
        Impl* pc = pimpl;
        result = pc->info;
        pimpl = pimpl->next;
        delete pc;
        return result;
    }else{
        return 0;
    }

}

bool Stack::isempty() const {
   return pimpl == nullptr;
}
void Stack::empty() {
    while(pimpl) {
        this->pop();
    }
}

