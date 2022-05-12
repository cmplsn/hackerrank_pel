#include<vector>
#include<iostream>

void print(const std::vector<double>& v) {
    for (auto x: v) {
        std::cout<<x<<std::endl;
    }
}


void read(std::vector<double>& v) {
    int size;
    double el;
    std::cin>>size;

    v.clear(); //cancella tutti gli elementi del vettore
    for (;size>0;size--) {
        std::cin>>el;
        v.push_back(el);
    }
}

std::vector<double> moving_average(const std::vector<double> v, int k){
    std::vector<double> x(v.size());
    for(int i = 0; i<x.size(); i++){//scorrimento celle vector
        int prec = i - k;
        int succ =x.size() -1 - i;
        if(prec < 0){
            prec = i;
        }else{
            prec= k;
        }
        if(succ < k){
            succ=x.size()-1-i;
        }else{
            succ = k;
        }

        int j = i-prec;
        while(j <=i+succ){
            x[i]+= v[j] / (prec+succ+1);
            j++;
        }

    }
    return x;

}

int main() {
    std::vector<double> v;

    int mov;

    std::cin>>mov;

    read(v);

    std::vector<double> result;

    result = moving_average(v, mov);

    print(result);

    return 0;
}