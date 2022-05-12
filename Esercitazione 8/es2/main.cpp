#include<string>
#include<iostream>
#include<stack>

using namespace std;


bool bilanciata (string& s){
    bool found=false;
    if(s.empty()){
        found= true;
    }else{
        if(s.size()%2 != 0){
            found = false;
        }else{
            stack<char> copy;
            for(int i = 0; i < s.size(); i++){ /*for( char c : s)*/
                if(s.at(i)<='Z' && s.at(i)>='A'){
                    copy.push(s.at(i));
                }else{
                    found = false;
                }
                if(!copy.empty() && s.at(i) - copy.top() == 32 ){
                    copy.pop();
                }
            }
            if(copy.empty()){
                found = true;
            }else{
                found = false;
            }
        }
    }
    return found;
}

int main(){

    string s;
    getline(cin,s);

    cout << boolalpha <<  bilanciata(s);

    return 0;
}