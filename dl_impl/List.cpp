//
// Created by Alessandro on 03/06/22.
//
#include <iostream>
#include "List.h"

struct Cell{
    int info;
    Cell* next;
    Cell* prev;
};
typedef Cell* Pcell;

struct List::Impl{
    Pcell head;
    Pcell tail;
    void destroy(Pcell head) const;
    Pcell copy(Pcell& dest, Pcell source)const;
};

List::List() {
    pimpl = new Impl;
    pimpl->head = nullptr;
    pimpl->tail = nullptr;
}// default constructor

List::List(const List &l) {
    pimpl =new Impl;
    pimpl->tail = pimpl->copy(this->pimpl->head, l.pimpl->head);
}//copy constructor

Pcell List::Impl::copy(Pcell &dest, Pcell source) const {
    Pcell pc;
    if(source ==nullptr){
        dest =nullptr;
        return dest;
    }else{
        dest=new Cell{source->info, nullptr, nullptr};
        pc =dest;
        source =source->next;
        while(source){
            pc->next =new Cell;
            pc->next->info = source->info;
            pc->next->prev =pc;
            pc=pc->next;
            source = source->next;
        }
        pc->next =nullptr;
    }
    return pc;
}

List::~List() {
    pimpl->destroy(pimpl->head);
    delete pimpl;
}//destructor

void List::Impl::destroy(Pcell head) const {
    if(head){
        destroy(head->next);
        delete head;
    }
}//FATTO

void List::append(int el) {
    Pcell pc;
    if(pimpl->head ==nullptr){
        prepend(el);
    }else{
       pc=new Cell;
       pc->info =el;
       pc->prev = pimpl->tail;
       pc->prev->next =pc;
       pimpl->tail =pc;
    }
    pimpl->tail->next =nullptr;

}//FATTO

void List::prepend(int el) {
    Pcell pc = new Cell;
    pc->info =el;
    if(pimpl->head == nullptr){
        pimpl->tail = pc;
    }else{
        pc->next = pimpl->head;
        pc->next->prev =pc;

    }
    pimpl->head =pc;

}//FATTO

void List::remove_elem(int el) {
    Pcell pc = pimpl->head;
   if(pc == nullptr){
       return;
   }else{
       pc=pc->next;
       while(pc->next){
           if(pc->info ==el){
               Pcell aux = pc;
               aux->prev->next = aux->next;
               aux->next->prev =aux->prev;
               aux=aux->next;
               delete pc;
               pc =aux;
           }else{
               pc = pc->next;
           }
       }

       pc = pimpl->head;
       if(pc->info ==el) {
           if (pc->prev == nullptr && pc->next == nullptr) {
               pimpl->head = nullptr;
               pimpl->tail = nullptr;
               delete pc;
           } else {
               Pcell aux = pc;
               aux->next->prev = nullptr;
               aux = aux->next;
               delete pc;
               pc = aux;
               pimpl->head = pc;
           }
       }

       pc =pimpl->tail;
       if(pc->info == el) {
           if (pc->prev == nullptr && pc->next == nullptr) {
               pimpl->tail = nullptr;
               pimpl->head = nullptr;
           } else {
               Pcell aux = pc;
               aux->prev->next = nullptr;
               aux = aux->prev;
               delete pc;
               pc = aux;
               pimpl->tail = pc;
           }
       }

   }

}

List List::operator+(const List &l) const {
    List result = *this;
    if(l.pimpl == nullptr){
        return result;
    }else{
        Pcell pc = l.pimpl->head;
        while(pc){
            result.append(pc->info);
            pc =pc->next;
        }
    }
    return result;

}

List& List::operator=(const List &l) {
    if(this != &l){
        if(pimpl->head !=nullptr) {
            pimpl->destroy(pimpl->head);
        }
        pimpl->tail = pimpl->copy(pimpl->head, l.pimpl->head);
    }
    return *this;
}

void List::print() {
    Pcell pc = pimpl->head;
    while(pc){
        std::cout<<pc->info<<std::endl;
        pc = pc->next;
    }
}//FATTO

void List::print_rev() {
    Pcell pc =pimpl->tail;
    while(pc){
        std::cout<<pc->info<<std::endl;
        pc =pc->prev;
    }
}//FATTO

int& List::at(int pos) {
    if(pos >= 0){
        Pcell pc =pimpl->head;
        int i = 0;
        while(i!=pos && pc ){
            i++;
            pc =pc->next;
        }
        if(i != pos){
            std::cout<<"out of range"<<std::endl;
        }else{
            return pc->info;
        }
    }else{
        Pcell pc = pimpl->tail;
        int i = -1;
        while(i!=pos &&pc){
            i--;
            pc = pc->prev;
        }
        if(i!=pos){
            std::cout<<"out of range"<<std::endl;
        }else{
            return pc->info;
        }
    }
}

const int& List::at(int pos) const {}