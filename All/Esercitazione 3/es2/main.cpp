#include <iostream>
#include <vector>

class Primes {
private:
    int size;

public:
    std::vector<int> primi;
    Primes(int size) {
        int el =2;
        while(primi.size()< size){
            int cont = 0;
            for(int i=1; i <=el;i++){
                if(el%i == 0){
                    cont ++;
                }
            }
            if(cont == 2){
                primi.push_back(el);
            }
            el++;
        }
    }

    int get_prime(int n) {
        int trovato;
        if(n >= 0 && n<primi.size()){
            trovato =primi.at(n);
        }
        if (n >= primi.size()){
            int diff = n - (primi.size()-1);
            int num = primi.at(primi.size()-1) +1;
            int count = 0;
            while(count < diff){
                int diviso = 0;
                for(int i = 1; i <= num; i++){
                    if(num%i == 0 ){
                       diviso++;
                    }
                }
                if(diviso == 2){
                   trovato = num;
                   count++;
                }
                num++;
            }
        }
        if(n<0){
        return -1;}
        return trovato;
    }
};

int main() {
    int size = 100, n, prime;
    std::cin>>n;

    Primes prime_gen = Primes(size);
    prime = prime_gen.get_prime(n);

    std::cout << prime << std::endl;
    return 0;
}