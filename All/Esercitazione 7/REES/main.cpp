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



/*copia incolla qui il tuo codice*/
Pcell List_dl::Impl::copy(Pcell& dest, Pcell source) const{
    Pcell aux;
    if(source == nullptr){
        dest = nullptr;
        return dest;
    }else{
        //dest =new Cell;
        dest=new Cell{source->info,nullptr,nullptr};
        //dest->info = source->info;
        //dest->prev = nullptr;
        aux = dest;
        source =source->next;
        while(source){
            aux->next = new Cell;
            aux->next->info = source->info;
            aux->next->prev = aux;
            aux = aux->next;
            source = source->next;
        }
        aux->next = nullptr;
    }
    return aux;
}

/*Returns the element in position pos. If pos>=0 then the
 * positions are counted from head starting by 0
 * if pos < 0 then we count from tail backword. Hence the last
 * position is -1, the one before -2 and so on
 * If pos is not in the list, return the dummy int present in struct pimpl
 */

int& List_dl::at(int pos)  {
    Pcell pc;

    if(pimpl->head!=nullptr && pimpl->tail!=nullptr){
        if(pos<0){
            int count = -1;
            while(count!=pos && pimpl->tail->prev){
                count--;
                pimpl->tail = pimpl->tail->prev;
            }
            pc= pimpl->tail;
            while(pimpl->tail->next != nullptr){
                pimpl->tail = pimpl->tail->next;
            }
            if(count != pos && pc->prev ==nullptr){
                return pimpl->dummy;
            }else{
                return pc->info;
            }

        }else{
            int count = 0;
            while(count != pos && pimpl->head->next){
                count++;
                pimpl->head = pimpl->head->next;

            }
            pc= pimpl->head;
            while(pimpl->head->prev !=nullptr){
                pimpl->head = pimpl->head->prev;
            }
            if(count !=pos && pc->next==nullptr){
                return pimpl->dummy;
            }else{
                return pc->info;
            }

        }
    }else {
        return pimpl->dummy;
    }
}

const int& List_dl::at(int pos) const {
    Pcell pc;

    if(pimpl->head!=nullptr && pimpl->tail!=nullptr){
        if(pos<0){
            int count = -1;
            while(count!=pos && pimpl->tail->prev){
                count--;
                pimpl->tail = pimpl->tail->prev;
            }
            pc= pimpl->tail;
            while(pimpl->tail->next != nullptr){
                pimpl->tail = pimpl->tail->next;
            }
            if(count != pos && pc->prev ==nullptr){
                return pimpl->dummy;
            }else{
                return pc->info;
            }

        }else{
            int count = 0;
            while(count != pos && pimpl->head->next){
                count++;
                pimpl->head = pimpl->head->next;

            }
            pc= pimpl->head;
            while(pimpl->head->prev !=nullptr){
                pimpl->head = pimpl->head->prev;
            }
            if(count !=pos && pc->next==nullptr){
                return pimpl->dummy;
            }else{
                return pc->info;
            }

        }
    }else {
        return pimpl->dummy;
    }
}

/*Assignment with deep copy*/
List_dl& List_dl::operator=(const List_dl& l) {
    if (this != &l) { //protect from self-assignment
        /* Add here your code */
        //this->pimpl->destroy(this->pimpl->head);
        //this->pimpl->head = nullptr;
        pimpl->tail = pimpl->copy(pimpl->head,l.pimpl->head);
    }
    return *this;
}

/*This operator concatenates the two list (*this first and l follows)*/
List_dl List_dl::operator+(const List_dl& l) const {
    List_dl result = *this;
    if(l.pimpl==nullptr){
        result = *this;
    }else{
        Pcell pc = l.pimpl->head;
        while(pc !=nullptr){
            result.append(pc->info);
            pc=pc->next;
        }
    }


    return result;
}

/*Remove all the elements equal to elem*/
void List_dl::remove_elements(int elem) {
    Pcell pc = pimpl->head;
    if(pc == nullptr){
        return;
    }else{
        pc=pc->next;
        while(pc->next){
            if(pc->info == elem){
                if(pc->prev !=nullptr && pc->next !=nullptr){
                    pc->prev->next =pc->next;
                    pc->next->prev = pc->prev;
                    Pcell aux =pc->next;
                    delete pc;
                    pc =aux;
                }
            }else{
                pc=pc->next;}
        }

        pc = pimpl->head;
        if(pc->info == elem){
            if(pc->next ==nullptr && pc->prev == nullptr){
                pimpl->head = nullptr;
                pimpl->tail =nullptr;
            }else{
                pc->next->prev = nullptr;
                Pcell aux = pc->next;
                delete pc;
                pc=aux;
                pimpl->head = pc;
            }
        }
        pc =pimpl->tail;
        if(pc->info == elem){
            if(pc->prev == nullptr && pc->next == nullptr){
                pimpl->head=nullptr;
                pimpl->tail = nullptr;
            }else{
                pc->prev->next = nullptr;
                Pcell aux = pc->prev;
                delete pc;
                pc=aux;
                pimpl->tail=pc;
            }
        }

    }
}

void modify(List_dl lin) {
    int pos, value;
    for (int i=0; i<3; i++) {
        std::cin>>pos;
        std::cin>>value;
        lin.at(pos)=value;
    }
    lin.print();
    lin.print_rev();
}

/*int main() {
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

}*/ // MAIN DI CONTROLLO FUNZIONAMENTO = E +

/*int main() {
    int x;
    List_dl l;
    do {
        std::cin>>x;
        if (x!=0)
            l.append(x);
    } while (x!=0);

    modify(l);  //Whoops call the copy constructor!

    l.print();
    l.print_rev();


}*/ //MAIN DI CONTROLLO FUNZIONAMENTO AT E COPY CONSTRUCTOR

int main() {
    int x;
    List_dl l;
    do {
        std::cin>>x;
        if (x!=0)
            l.append(x);
    } while (x!=0);

    std::cin>>x;

    l.remove_elements(x);

    l.print();
    l.print_rev();

    return 0;
}   //MAIN FUNZIONAMENTO REMOVE

