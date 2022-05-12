#include<iostream>



//questa parte andrebbe nel file hpp
class List_dl{
public:
    List_dl();  //Default constructor
    List_dl(const List_dl& copy);  //Copy constructor
    ~List_dl();

    void prepend(int elem);
    void append(int elem);

    void remove_elements(int elem);

    List_dl operator+(const List_dl& l) const;
    List_dl& operator=(const List_dl& l);


    void print();
    void print_rev();

    int& at(int pos);
    const int& at(int pos) const;
private:
    struct Impl;
    Impl* pimpl;
};

//questa parte andrebbe nel file cpp

struct Cell {
    int info;
    Cell* next;
    Cell* prev;
};

typedef Cell* Pcell;

struct List_dl::Impl{
    Pcell head;
    Pcell tail;
    int dummy;
    void destroy(Pcell head) const;
    //copy the list and return the pointer to the last element, nullptr for the empty list
    Pcell copy(Pcell& dest, Pcell source) const;
};

//Default constructor
List_dl::List_dl() {
    pimpl = new Impl;
    pimpl->head = nullptr;
    pimpl->tail = nullptr;
}

//Copy constructor
List_dl::List_dl(const List_dl& source) {
    pimpl = new Impl;
    pimpl->tail = pimpl->copy(pimpl->head, source.pimpl->head);
}

List_dl::~List_dl() {
    pimpl->destroy(pimpl->head);
    delete pimpl;
}

void List_dl::Impl::destroy(Pcell head) const{
    if (head) {
        destroy(head->next);
        delete head;
    }
}

void List_dl::prepend(int el) {
    Pcell pcell = new Cell;
    pcell->prev = nullptr;
    pcell->info = el;
    pcell->next = pimpl->head;
    if (pimpl->head!=nullptr)
        pimpl->head->prev = pcell;
    else
        pimpl->tail = pcell;
    pimpl->head = pcell;
}

void List_dl::append(int el) {
    Pcell pcell = new Cell;
    pcell->next = nullptr;
    pcell->info = el;
    pcell->prev = pimpl->tail;
    if (pimpl->tail!=nullptr)
        pimpl->tail->next = pcell;
    else
        pimpl->head = pcell;
    pimpl->tail = pcell;
}

void List_dl::print() {
    Pcell pc = pimpl->head;
    while (pc) {
        std::cout<<pc->info<<std::endl;
        pc = pc->next;
    }
}

void List_dl::print_rev() {
    Pcell pc = pimpl->tail;
    while (pc) {
        std::cout<<pc->info<<std::endl;
        pc = pc->prev;
    }
}

//deep copy the list from source to dest and return the pointer to the last element of the list
//pointed by dest, nullptr for the empty list
Pcell List_dl::Impl::copy(Pcell& dest, Pcell source) const{
    Pcell aux;
    if(source == nullptr){
        return nullptr;
    }else{
        dest = new Cell;
        dest->info = source->info;
        dest->prev = source->prev;
        aux = dest;
        while(source->next){
            source = source->next;
            aux->next = new Cell;//inserire in ciclo while
            aux->next->prev = aux;
            aux->next->info = source->info;
            aux = aux->next;
        }//inserire dentro a ciclo while
    }
    return aux;
}

/*Returns the element in position pos. If pos>=0 then the
 * positions are counted from head starting by 0
 * if pos < 0 then we count from tail backword. Hence the last
 * position is -1, the one before -2 and so on
 * If pos is not in the list, return the dummy int present in struct pimpl
 */

 int& List_dl::at(int pos) {
     if(pimpl->head != nullptr && pimpl->tail!=nullptr){
         if(pos< 0){
             int count = -1;
             while(count != pos ){
                 count--;
                 if( pimpl->tail->prev != nullptr){
                     pimpl->tail = pimpl->tail->prev;
                 }else{
                     return pimpl->dummy;
                 }
             }
            return pimpl->tail->info;
         }else{
             int count = 0;
             while(count!=pos){
                 count++;
                 if(pimpl->head->next !=nullptr){
                     pimpl->head = pimpl->head->next;
                 }else{
                     return pimpl->dummy;
                 }
             }
             return pimpl->head->info;
         }
     }else{
         return pimpl->dummy;
     }
}

/*const int& List_dl::at(int pos) const {
    return pimpl->dummy;
}*/

/*Assignment with deep copy*/
List_dl& List_dl::operator=(const List_dl& l) {
    if (this != &l) { //protect from self-assignment
        pimpl->destroy(pimpl->head);
        pimpl->tail = pimpl->copy(pimpl->head,l.pimpl->head);


    }
    return *this;
}

/*This operator concatenates the two list (*this first and l follows)*/
List_dl List_dl::operator+(const List_dl& l) const {
    List_dl result = *this;
    Pcell pc = l.pimpl->head;
    while(pc->next !=nullptr){
       result.append(pc->info);
        pc=pc->next;
    }
    return result;
}


/*Remove all the elements equal to elem*/
/*void List_dl::remove_elements(int elem) {
}*/

//controllo degli operatori + e =

int main() {
    int x;
    List_dl res;
    {
        List_dl l1, l2;
        do {
            std::cin>>x;
            if (x!=0)
                l1.append(x);
        } while (x!=0);

        do {
            std::cin>>x;
            if (x!=0)
                l2.append(x);
        } while (x!=0);
        res = l1+l2;
    }
    res.print();
    res.print_rev();

    return 0;

}
