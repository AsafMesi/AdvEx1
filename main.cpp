#include <iostream>
#include <fstream>

using namespace std;

int main(){

    ifstream test;
    test.open("test.csv");     //test.is_open()

    while(test.good()) {
        string line;
        getline(test, line, ',');
        cout << line << endl;
    }
    return 0;
}
