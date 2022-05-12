#include <iostream>
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

int main() {

    return 0;
}
