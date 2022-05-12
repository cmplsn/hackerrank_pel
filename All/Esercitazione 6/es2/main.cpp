#include <iostream>
#include <string>


std::string decomprimi(const std::string& s) {
    std::string *res = new std::string;
    char let;
    int rep;
    for(int i = 0; i < s.size(); i= i+2){
        let = s.at(i);
        rep =s.at(i+1) - '0';
        for(int j = 0; j < rep; j++){
            *res += let;
        }
    }

    return *res;
}
int main() {
    std::string buff;
    std::string res;

    std::cin>>buff;

    res = decomprimi(buff);

    std::cout<<res;
    return 0;
}