//
// Created by Alessandro on 04/06/22.
//

#ifndef STACK_STACK_HPP
#define STACK_STACK_HPP
class Stack{
public:
    Stack();
    Stack(const Stack& s);
    ~Stack();

    void push(int el);
    int pop();
    bool isempty() const;
    void empty();

private:
    struct Impl;
    Impl* pimpl;
};
#endif //STACK_STACK_HPP
