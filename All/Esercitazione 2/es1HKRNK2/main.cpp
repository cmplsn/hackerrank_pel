#include <iostream>
#include <vector>

using namespace std;
vector<int> read_vector() {
    int size;
    vector<int> res;
    std::cin>>size;

    for( ; size>0; size--) {
        int elem;
        std::cin>>elem;
        res.push_back(elem);
    }
    return res;
}

void print_vector(const vector<int>& v) {
    for (int el: v) {
        std::cout<<el<<std::endl;
    }
}

void apply(vector<int>& v, const vector<int>& perm) {

  for(int i = 0; i < perm.size()-1;i++){
        swap(v.at(perm.at(perm.size()-1)), v.at(perm.at(i)));
    }

}
int main() {
    vector<int> input = read_vector();
    vector<int> permutation = read_vector();

    apply(input, permutation);

    print_vector(input);

    return 0;
}
