#include <iostream>
#include <vector>
#include <string>


class Set{
public:
    Set();
    Set(const Set& s);
    ~Set();
    void add(int elem);
    bool belong(int elem) const;
    bool is_empty() const;

    bool operator<=(const Set& s) const; //se B sottoinsieme di A, B può coincidere con A
    bool operator<(const Set& s) const; // se B sottoinsieme di A, A-B != vuoto
    bool operator==(const Set& s) const;

    Set& operator=(const Set& s); //assignment
    Set operator+(const Set& s) const ; //insieme UNIONE
    Set operator*(const Set& s) const; //insieme INTERSEZIONE
    Set operator-(const Set& s) const; //insieme DIFFERENZA

    void print() const; // DEVE STAMPARE IN ORDINE CRESCENTE, SE VUOTO stampa "EMPTY SET"
private:
    struct Impl;
    Impl* pimpl;
};

using namespace std;

struct Set::Impl{
    vector<int> nat;
}; //implementato con vector

Set::Set(){
    pimpl = new Impl;
}       //fatto

Set::Set(const Set& s){
    pimpl = new Impl;
    this->pimpl->nat = s.pimpl->nat;
}       //fatto

Set::~Set() {
   delete pimpl;
}       //fatto

void rearrange(vector<int>& x){
     int i = 0;
    while(i < x.size()){
        int j = i+1;
        while(j< x.size()){
            if(x.at(i)> x.at(j)){
                swap(x.at(i), x.at(j));
            }
            j++;
        }
        i++;
    }
} //UTILIZZARE NELLA PRINT

void Set::add(int elem){
    if (this->is_empty())
        pimpl->nat.push_back(elem);
    else{
        int count = 0;
        for (int i = 0; i < pimpl->nat.size(); i ++){
            if (pimpl->nat.at(i) == elem)
                count++;
        }
        if (count == 0)
            pimpl->nat.push_back(elem);
    }
}
/*void Set::add(int elem) {
    if(!this->pimpl->nat.empty()){
        bool not_found = true;
        int i = 0;
        while(i < this->pimpl->nat.size()&& not_found){
            if(elem == pimpl->nat.at(i)){
                not_found=false;
            }
            i++;
        }
        if(not_found){
            this->pimpl->nat.push_back(elem);
        }

    }else{
        this->pimpl->nat.push_back(elem);
    }
}  */     //fatto

bool Set::belong(int elem) const {
    for(int i = 0; i < pimpl->nat.size(); i++){
        if(elem == pimpl->nat.at(i)){
            return true;
        }
    }
    return false;
}       //fatto

bool Set::is_empty() const {
    if(this->pimpl->nat.empty() ){
        return true;
    }else{
        return false;
    }

}       //fatto

bool Set::operator<=(const Set &s) const {
    if(this->pimpl->nat.empty()){
        return true;
    }else {
        int i = 0;
        int count = 0;
        while (i < this->pimpl->nat.size()) {
            int j = 0;
            while (j < s.pimpl->nat.size()) {
                if (this->pimpl->nat.at(i) == s.pimpl->nat.at(j)) {
                    count++;
                    j++;
                } else {
                    j++;
                }
            }
            i++;
        }
        if (count == this->pimpl->nat.size() && count <= s.pimpl->nat.size()) {
            return true;
        } else {
            return false;
        }
    }
}       //fatto

bool Set::operator<(const Set &s) const {
    if(this->pimpl->nat.empty()){
        return true;
    }else {
        int i = 0;
        int count = 0;
        while (i < this->pimpl->nat.size()) {
            int j = 0;
            while (j < s.pimpl->nat.size()) {
                if (this->pimpl->nat.at(i) == s.pimpl->nat.at(j)) {
                    count++;
                    j++;
                } else {
                    j++;
                }
            }
            i++;
        }
        if (count == this->pimpl->nat.size() && count < s.pimpl->nat.size()) {
            return true;
        } else {
            return false;
        }
    }
}        //fatto

bool Set::operator==(const Set &s) const {

        int i = 0;
        int count = 0;
        while (i < this->pimpl->nat.size()) {
            int j = 0;
            while (j < s.pimpl->nat.size()) {
                if (this->pimpl->nat.at(i) == s.pimpl->nat.at(j)) {
                    count++;
                    j++;
                } else {
                    j++;
                }
            }
            i++;
        }
        if (count == this->pimpl->nat.size() && count == s.pimpl->nat.size()) {
            return true;
        } else {
            return false;
        }
}       //fatto

Set& Set::operator=(const Set &s) {
    if(this != &s){
        delete this->pimpl;
        this->pimpl = new Impl;
        this->pimpl->nat =s.pimpl->nat;
    }
    return *this;
} //fatto

Set Set::operator+(const Set &s) const {
   Set copy(*this);
   int i = 0;

   while(i < s.pimpl->nat.size()){
       int j=0;
       bool not_found= true;
       while(j<copy.pimpl->nat.size() && not_found){
           if(s.pimpl->nat.at(i)!= copy.pimpl->nat.at(j)){
               j++;
           }else{
               not_found=false;
           }

       }
       if(not_found){
           copy.add(s.pimpl->nat.at(i));
       }
       i++;
   }

   return copy;

}       //fatto

Set Set::operator-(const Set &s) const {
    Set copy(*this);
    int i=0;
    while(i<s.pimpl->nat.size()){
        int j = 0;
        bool found =false;
        while(j<copy.pimpl->nat.size() && !found){
            if(s.pimpl->nat.at(i) ==copy.pimpl->nat.at(j)){
                found=true;
            }else{j++;}
        }
        if(found){
            copy.pimpl->nat.erase(copy.pimpl->nat.begin()+j);
        }
        i++;
    }

    return copy;
}

Set Set::operator*(const Set &s) const {
    Set res;
    int elem;
    int i = 0;
    while(i < this->pimpl->nat.size()){
        int j = 0;
        bool found = false;
        while(j<s.pimpl->nat.size()&& !found){
            if(this->pimpl->nat.at(i) == s.pimpl->nat.at(j)){
                found = true;
                elem = this->pimpl->nat.at(i);

            }else{
                j++;
            }
        }
        if(found){
            res.add(elem);
        }
        i++;
    }
    return res;
}
void ordina(std::vector<int>& r){
    int aux;
    for (int i = 0; i < r.size() - 1; i++){
        for (int j = 0; j < r.size() - 1; j++){
            if (r.at(j) > r.at(j + 1)){
                aux = r.at(j);
                r.at(j) = r.at(j + 1);
                r.at(j + 1) = aux;
            }
        }
    }
}
void Set::print() const {
    if(this->pimpl->nat.empty()){
        cout<<"Empty set"<<endl;
    }else{
        ordina(this->pimpl->nat);
        for(int i = 0;i < this->pimpl->nat.size();i++){
            cout<<this->pimpl->nat.at(i)<<endl;
        }
    }
}


void dosomething(Set s1, Set s2){
    if (s1<=s2)
        std::cout<<"s1 is included in s2"<<std::endl;
    else
        std::cout<<"s1 is not included in s2"<<std::endl;

    if (s1<s2)
        std::cout<<"s1 is strictly included in s2"<<std::endl;
    else
        std::cout<<"s1 is not strictly included in s2"<<std::endl;

    if (s1==s2)
        std::cout<<"s1 is equal to s2"<<std::endl;
    else
        std::cout<<"s1 is not equal to s2"<<std::endl;
}

int main() {
    Set s1, s2;

    int input1, input2;

    std::cin>>input1;
    std::cin>>input2;

    for (int i=0; i<input1; i++) {
        int elem;
        std::cin>>elem;
        s1.add(elem);
    }


    for (int i=0; i<input2; i++) {
        int elem;
        std::cin>>elem;
        s2.add(elem);
    }

    std::cout<<"Output"<<std::endl;

    dosomething(s1, s2);

    std::cout<<std::endl;
    s1.print();
    std::cout<<std::endl;
    s2.print();

    return 0;

}//MAIN_DOSOMETHING ESERCIZIO 1

/*void dosomething(Set s1, Set s2){
    Set res;
    res = s1+s2;
    std::cout<<"Union set"<<std::endl;
    res.print();
    s1 = s1*s2;
    std::cout<<"Intersection set"<<std::endl;
    s1.print();
}




int main() {
    Set s1, s2;

    int input1, input2;

    std::cin>>input1;
    std::cin>>input2;

    for (int i=0; i<input1; i++) {
        int elem;
        std::cin>>elem;
        s1.add(elem);
    }


    for (int i=0; i<input2; i++) {
        int elem;
        std::cin>>elem;
        s2.add(elem);
    }

    std::cout<<"Output"<<std::endl;

    dosomething(s1, s2);

    std::cout<<std::endl;
    s1.print();
    std::cout<<std::endl;
    s2.print();

    return 0;

}*/ //MAIN_DOSOMETHING ESERCIZIO 2

/*void dosomething(Set s1, Set s2){
    s1 = s1-s2;
    std::cout<<"Differece set"<<std::endl;
    s1.print();
}*/

/*int main() {
    Set s1, s2;


    int input1, input2;

    std::cin>>input1;
    std::cin>>input2;

    for (int i=0; i<input1; i++) {
        int elem;
        std::cin>>elem;
        s1.add(elem);
    }


    for (int i=0; i<input2; i++) {
        int elem;
        std::cin>>elem;
        s2.add(elem);
    }

    std::cout<<"Output"<<std::endl;

    dosomething(s1, s2);

    std::cout<<std::endl;
    s1.print();
    std::cout<<std::endl;
    s2.print();
    cout<<boolalpha<<(s1<s2);

    return 0;

}*/ //MAIN_DOSOMETHING ESERCIZIO 3