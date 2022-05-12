
#include<iostream>
#include<string>
#include <sstream>

/*copia incolla il codice dal primo esercizio*/
class Number{
public:
    Number();
    Number(unsigned int m);
    Number(const Number& l);
    Number(std::string s);
    ~Number();

    void print() const;

    Number operator+(const Number& x) const;
    Number operator*(const Number& x) const;
    bool operator==(const Number& x) const;
    bool operator!=(const Number& x) const;
    Number& operator=(const Number& x);


private:
    //Non modificare
    struct Cell{
        char info;
        Cell* next;
    };

    typedef Cell* List;

    List n;
    List sum(List l1, List l2, char carry) const;
    void print_rec(List l) const;


    //Parte modificabile (ma attenzione: ora è progettata per guidarvi)
    void append(char el);
    void prepend(char el);
    List convert(unsigned int m);
    void destroy(List h);
    List copy(const List pc);
    bool equal(List l1, List l2) const;


};

Number::Number() {
    n=nullptr;
}

//converte un unsigned int nella lista richiesta
Number::Number(unsigned int m) {
    n = convert(m);
}

//studia questa funzione per comprendere completamente la rappresentazione nel numero
//e' un bell'esempio di ricorsione
Number::List Number::convert(unsigned int m) {
    if (m==0)
        return nullptr;
    else {
        List pc = new Cell;
        pc->info = m%10;
        pc->next = convert(m/10);
        return pc;
    }
}

//stampa la lista: siccome le cifre meno significative sono in testa, devo stampare al contrario
void Number::print() const {
    if (n==nullptr)
        std::cout<<"0";
    else
        print_rec(n);
}

//parte ricorsiva della stampa
void Number::print_rec(List l) const {
    if (l) {
        print_rec(l->next);
        std::cout<<static_cast<char>(l->info+'0'); //Ecco il type casting explicito in C++
    }
}

//distruttore
Number::~Number() {
    destroy(n);
}

//funzione di disruzione ricorsiva
void Number::destroy(List h) {
    if (h) {
        destroy(h->next);
        delete(h);
    }
}

void Number::prepend(char el) {
    List newone = new Cell;
    newone->info = el;
    newone->next = n;
    n = newone;
}
void Number::append(char el){
    if (n==nullptr)
        prepend(el);
    else {
        List pc = n;
        while (pc->next!=nullptr)
            pc = pc->next;
        pc->next = new Cell;
        pc->next->info = el;
        pc->next->next = nullptr;
    }
}

//primo metodo da implementare: dato un numero codificato con una stringa
//scritto in modo che la cifra piu' significativa e' nella prima posizione
//generare un Number. Attenzione non fare la conversione string->int->list
//perche' potresti avere errori di overflow
Number::Number(std::string s) {
    n = nullptr;

    for(int i = s.size()-1; i>=0; i --) {
        if(s.size()==1 && s.at(i)=='0'){
            n = nullptr;
        }else{
            if (n == nullptr) {
                prepend(s.at(i) - '0');
            } else {
                append(s.at(i) - '0');

            }}
    }


}

//secondo metodo da implementare: copy constructor
//consigliato far uso della funzione privata ricorsiva copy
//potrebbe esserti utile anche per l'assegnamento!
Number::Number(const Number&x) {
    n= copy(x.n);
}


Number::List Number::copy(const List pc) {
    if(pc== nullptr){
        return nullptr;
    }else{
        List copied = new Cell;
        copied->info = pc->info;
        copied->next = copy(pc->next);
        return copied;
    }
//se preferisci non usarla, cancellala anche dall'intestazione
}


//l'operatore + non va modificato. Deve utilizzare il meotodo sum come indicato
Number Number::operator+(const Number& x) const {
    Number res;
    res.n = sum(x.n, n, 0);
    return res;
}

//Questa funzione deve essere ricorsiva. Implementala con cura. Ricorda
//che l'ultimo carry potrebbe essere diverso da 0
Number::List Number::sum(List l1, List l2, char carry) const {
    char aux;


    if(l1==nullptr && l2==nullptr&& carry==0){
        return nullptr;
    }else{
        List result =new Cell;
        if(l1==nullptr&&l2==nullptr && carry!=0){
            result->info =(int)carry;
            carry = 0;
            result->next =sum(l1,l2,carry);

        }else{
            if(l1==nullptr){
                aux = (int)(l2->info+carry);
                carry = (int)aux/10;
                result->info=(int)aux%10;
                result->next= sum(l1, l2->next, carry);
            }else{
                if(l2==nullptr){
                    aux=(int)(l1->info+carry);
                    carry=(int)aux/10;
                    result->info=(int)aux%10;
                    result->next =sum(l1->next, l2,carry);
                }else{
                    if(l1!=nullptr&&l2!=nullptr){
                        aux=(int)(l1->info + l2->info+carry);
                        carry=(int)aux/10;
                        result->info = (int)aux%10;
                        result->next=sum(l1->next, l2->next, carry);
                    }
                }
            }}
        return result;
    }
}


//operatore di assegnamento. Segui la traccia
Number& Number::operator=(const Number& x) {
    if (this!=&x) {
        //aggiungi qui le istruzioni!
        destroy(n);
        n =copy(x.n);

    }
    return *this;
}


//La seguente funzione puo' essere modificata, ma e'
//consigliato usare la equal sviluppata ricorsivamente
bool Number::operator==(const Number& x) const{
    return equal(x.n, n);
}

//Da sviluppare
bool Number::equal(List l1, List l2) const {
    if(l1==nullptr && l2==nullptr){
        return true;
    }else{
        if(l1==nullptr){
            return false;
        }else{
            if(l2==nullptr){
                return false;
            }else{
                if(l1!=nullptr && l2!=nullptr){
                    if(l1->info == l2->info){
                        return equal(l1->next, l2->next);
                    }else{return false;}
                }
            }
        }
    }
    return false;
}

//Metodo velore per implementare il !=
bool Number::operator!=(const Number& x) const{
    return !(*this==x);
}

//Fare il prodotto x*y significa sommare x+x+x+..+x (y volte...)
//non il modo piu' efficiente, ma il piu' facile
//Ricorda che tutte le operazioni vanno fatte coi numbers!
Number Number::operator*(const Number& x) const{
    Number res(0);
    Number increment("1");
    if(*this == Number(0)  || x == Number(0)){
        return res;
    }else{
        for(Number count(0); count != *this; count = count + 1){
            res = res+x;
        }
    }
    return res;
}

Number opera(Number x, Number y) {
    return x*y;
}


int main() {
    std::string s1, s2;
    std::cin>>s1;
    std::cin>>s2;
    Number n1(s1), n2(s2);
    Number n3=24593;

    n3 = opera(n1, n2);

    n1.print();
    std::cout<<std::endl;
    n2.print();
    std::cout<<std::endl;
    n3.print();
    std::cout<<std::endl;
    if (n1==n2)
        std::cout<<"Numeri uguali inseriti"<<std::endl;


    return 0;
}
