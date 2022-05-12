#include<iostream>
#include<vector>

using std::vector;
using std::string;

string carta(int n){
    string card;
    string seme;
    int mod = n%10;
    int div = n/10;
    if(n<0 || n>39){
        return "Errore di conversione";
    } else{
        switch (mod){
            case 0:{
                card = "Asso";
                break;
            }
            case 1 ... 6:{
                card = std::to_string(mod +1);
                break;
            }
            case 7:{
                card = "Donna";
                break;
            }
            case 8:{
                card ="Fante";
                break;
            }
            case 9:{
                card ="Re";
                break;
            }
        }

        switch(div){
            case 0:{
                seme =" di denari";
                break;
            }
            case 1:{
                seme = " di coppe";
                break;
            }
            case 2:{
                seme =" di bastoni";
                break;
            }
            case 3:{
                seme =" di spade";
                break;
            }
        }
    }
    return card + seme;
}

int main() {
    int c;
    string cstr;
    std::cin>>c;
    std::cout<<"**";
    cstr = carta(c);
    std::cout<<"**";
    std::cout<<std::endl<<cstr<<std::endl;
    return 0;
}
