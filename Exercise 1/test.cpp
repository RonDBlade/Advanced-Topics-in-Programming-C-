#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;


int main(){
    string test =  "C:/Developing/C++/Advanced-Topics-in-Programming-C-/Exercise 1/input.txt";
    ifstream input_file (test);
    string line;
    string word, delimiter = " \r\t";
    while(getline(input_file, line)){
        std::stringstream ss(line);
        getline(ss, word, " ");
        cout << word << endl;
    }
    cout << test;
}
