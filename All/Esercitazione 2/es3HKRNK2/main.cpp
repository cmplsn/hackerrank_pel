#include <iostream>
#include <string>

using std::string;

bool anagramma(string s1, string s2){
    int i = 0;
    int j = 0;
    while(i < s1.size()){
        if(s1.at(i)==' '){
            std::swap(s1.at(i), s1.at(s1.size()-1));
            s1.pop_back();
        }else{
            i++;
        }
    }
    while(j < s2.size()){
        if(s2.at(j) == ' '){
            std::swap(s2.at(j), s2.at(s2.size()-1));
            s2.pop_back();
        }else{
            j++;
        }
    }

    int k = 0;
    int l = 0;

    if(s1.size()!= s2.size()){
    return false;}
    else{
        while(k<s1.size()){
            while(l<s2.size()){
                if(s1.at(k) ==s2.at(l)){
                    std::swap(s1.at(k), s1.at(s1.size() - 1));
                    s1.pop_back();
                    std::swap(s2.at(l), s2.at(s2.size() - 1));
                    s2.pop_back();
                    l = 0;
                    k = 0;
                }else{
                    l++;
                }
            }
            k++;
        }
    }
    if(s1.size()==0 && s2.size()==0){
        return true;
    }else{
        return false;
    }
}

int main() {
    string a, b;
    getline(std::cin, a);
    getline(std::cin, b);

    if (anagramma(a,b))
        std::cout << "Si" <<std::endl;
    else
        std::cout << "No" <<std::endl;
    return 0;
}