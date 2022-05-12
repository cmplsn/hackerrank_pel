#include<vector>
#include<iostream>

void print(const std::vector<int>& v) {
    for (auto x: v) {
        std::cout<<x<<std::endl;
    }
}
std::vector<int> fill_with_primes(int size) {
    std::vector<int> primi;
    int el =2;
    while(primi.size()<size){
        int cont = 0;
        for(int i=1; i<=el; i++){
            if(el%i == 0){
                cont++;
            }
        }
        if(cont==2){
            primi.push_back(el);
        }
        el++;
    }

    return primi;
}

int main() {
    int size;

    std::cin>>size;

    std::vector<int> v;

    v = fill_with_primes(size);

    print(v);

    return 0;
}