#include <iostream>
#include <fstream>
#include "string"

using namespace std;

int main(){

    ifstream test;
    test.open(R"(C:\Users\asaf4\CLionProjects\AdvEx2\test.csv)");     //test.is_open()
    if (!test.is_open()){
        cout << "Error" << endl;
    }
    while(test.good()) {
        string line;
        getline(test, line, ',');
        cout << line << endl;
    }
    test.close();
    return 0;
}
