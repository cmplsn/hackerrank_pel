#include <iostream>
#include <string>
#include <sstream>
#include<fstream>
using namespace std;
int main() {
    /*string date="22/12/2022";
    istringstream iss{date};
    string day, month,year;
    getline(iss,day,'/');
    getline(iss,month,'/');
    getline(iss,year,'/');
    int dd = stoi(day);
    int mm = stoi(month);
    int yy= stoi(year);

    if(iss.fail() || !iss.eof()){
        cout<<"no";
    }else{
        cout<<"day"<<dd<<"month"<<mm<<"year"<<yy<<endl;
    }*/
    string content;
    ifstream file{"Libritxt.txt"};
    while(file.good()){
        file>>content;
        cout<<content<<endl;
    }

    return 0;
}
