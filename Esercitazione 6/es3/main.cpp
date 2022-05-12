#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector<vector<int>> mat;
    // funzione Bingo

    int  n = mat.size();
    int m = mat.at(0).size();

    vector<pair<int, int>> pos(m*n+1);

    for(int r = 0; r < n; r++){
        for(int c=0; c<m; c++){
            pos[mat[r][c]] = {r,c};
        }
    }



    return 0;
}
