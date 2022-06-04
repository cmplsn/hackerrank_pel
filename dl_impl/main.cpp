#include <iostream>
#include "List.h"

int main() {
    List a;

   a.append(3);
   a.append(4);
   a.append(5);
   a.append(12);
   a.prepend(12);
   a.remove_elem(12);
   a.print();
   std::cout<<std::endl;
   a.print_rev();
   std::cout<<std::endl;
   List b;
   b.append(12);
   b.append(7);
   b.append(9);
   a.at(2);
   List c;
   c= a+b;
   c.print();
    return 0;
}

