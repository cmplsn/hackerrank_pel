#include<iostream>
#include<string>

using std::string;

struct Cella{
    string info;
    Cella* next;
};

typedef Cella* Lista;

void prepend(Lista& l, const string& s) {
    Lista nuova = new Cella;

    nuova->next=l;
    nuova->info = s;
    l=nuova;
}


void append(Lista& l, const string& s) {
    if (!l)
        prepend(l, s);
    else
        append(l->next, s);
}

void leggi(Lista& l) {
    int e;
    std::cin>>e;

    while (e>0) {
        string buffer;
        std::cin>>buffer;
        append(l, buffer);
        e--;
    }
}

void distruggi(Lista& l) {
    if (l) {
        distruggi(l->next);
        delete l;
        l=nullptr;
    }
}


string concat(Lista l, int pos, int len) {
    string res;
    if(len==0 || l == nullptr){
        return res;
    }else{
        for(int count = 0; count < pos; count++){
            if(l->next!=nullptr){
                l=l->next;
            }else{

            }
        }
        res+=l->info;
    }
    return res+concat(l->next, 0, len-1);
}

int main() {
    Lista l = nullptr;
    int da, quanti;


    leggi(l);

    std::cin>>da;
    std::cin>>quanti;
    std::cout<<concat(l, da, quanti);

    distruggi(l);

    return 0;
}