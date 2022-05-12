#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

long cost(vector<int> arr){
    long tot =0;
    for(int i = 1; i < arr.size();i++){

        tot += pow(arr[i-1]-arr[i], 2);
    }
    return tot;
}

long getMinimumCost(vector<int> arr) {
    long min = cost(arr);
    for (int i = 1; i < arr.size(); i++) {
        long media = (arr[i - 1] + arr[i]) / 2;
        arr.insert(arr.begin() + i , media);
        long y = cost(arr);
        if (cost(arr) < min) {
            min = y;
        }
        arr.erase(arr.begin() + i);
    }
    return min;
}

int main() {
    std::vector<int> x={4,7,7};
    cout<<getMinimumCost(x);
    return 0;
}