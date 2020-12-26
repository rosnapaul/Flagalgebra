#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> row;
typedef vector<vector<int>> collection_of_rows;
typedef vector<vector<vector<int>>> collection_of_matricies;

const unsigned short NO_OF_MATRICIES = 262;
const unsigned short MATRIX_ROW_SIZE = 6;
const unsigned short MATRIX_COLUMN_SIZE = 5;

int main () {
    collection_of_matricies matricies;
    unsigned short i,j,k,temp; // Variables for Looping or Temporary Purposes
    unsigned char temp_char;
    ifstream infile;
    infile.open("rotationinmyform.txt"); // To read "rotationinmyform.txt" file
    // To Read Data from File and Insert into `matricies`
    for(i = 0; i < NO_OF_MATRICIES; i++) {
        collection_of_rows matrix;
        for(j = 0; j < MATRIX_ROW_SIZE; j++) {
            row temp_row;
            for(k = 0; k < MATRIX_COLUMN_SIZE; k++) {
                infile >> temp_char;
                temp = (int) temp_char - 48; // To Convert ASCII Number to Digit
                temp_row.push_back(temp);
            }
            matrix.push_back(temp_row);
        }
        matricies.push_back(matrix);
    }
    // To Print the Read Matrix
    for(i = 0; i < matricies.size(); i++) {
        cout << "Matrix " << i+1 << ":" << endl;
        for(j = 0; j < MATRIX_ROW_SIZE; j++) {
            for(k = 0; k < MATRIX_COLUMN_SIZE; k++)
                cout << matricies[i][j][k] << " ";
            cout << endl;
        }
        cout << endl;
    }
    infile.close();
    return 0;
}