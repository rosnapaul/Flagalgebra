#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> row;
typedef vector<vector<int>> matrix;

int main () {
    short unsigned int i,j,temp; // Variables for Looping or Temporary Purposes
    char data;
    matrix vec;
    ifstream infile; 
    infile.open("rotationinmyform.txt"); // To read "rotationinmyform.txt" file
    // To Read Data from File and Insert into `vec`
    for(i = 0; i < 6; i++) {
        row temp_row;
        for(j = 0; j < 5; j++) {
            infile >> data;
            temp = (int) data - 48; // To Convert ASCII Number to Digit
            temp_row.push_back(temp);
        }
        vec.push_back(temp_row);
    }
    // To Print the Read Matrix
    for(i = 0; i < vec.size(); i++) {
        for(j = 0; j < vec[i].size(); j++)
            cout << vec[i][j] << " ";
        cout << endl;
    }
    infile.close();
    return 0;
}