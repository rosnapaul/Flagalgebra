#ifndef READ_MATRIX_H
#define READ_MATRIX_H

#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> row;
typedef vector<vector<int>> collection_of_rows;
typedef vector<vector<vector<int>>> collection_of_matrices;
typedef vector<vector<vector<vector<int>>>> collection_of_collection_of_matrices;

inline collection_of_matrices get_matrices(string filename,unsigned short NO_OF_MATRICES,unsigned short MATRIX_ROW_SIZE,unsigned short MATRIX_COLUMN_SIZE) {
    collection_of_matrices matrices;
    unsigned short i,j,k,temp; // Variables for Looping or Temporary Purposes
    unsigned char temp_char;
    ifstream infile;
    infile.open(filename); // To read the file
    // To Read Data from File and Insert into `matricies`
    for(i = 0; i < NO_OF_MATRICES; i++) {
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
        matrices.push_back(matrix);
    }
    infile.close();
    return matrices;
}

inline void write_info(string file_dir,collection_of_collection_of_matrices data) {
    ofstream outfile;
    stringstream filename;
    filename<<file_dir+"info.txt";
    outfile.open(filename.str().c_str(), ofstream::out);
    outfile<<data.size()<<" ";
    for(int i = 0; i < data.size(); i++) {
        outfile<<data[i].size()<<" ";
    } 
    outfile<<endl;
    for(int i = 0; i < data.size(); i++) {
        if(data[i].size()) {
            outfile<<data[i][0].size()<<" "<<data[i][0][0].size();
            break;
        }
    }
    outfile.close();
}

inline row read_info(string file_dir) {
    unsigned char temp_char;
    ifstream infile;
    infile.open(file_dir); // To read the file
    row temp_row;
    infile >> temp_char;
    temp = (int) temp_char - 48; // To Convert ASCII Number to Digit
    temp_row.push_back(temp);
    infile.close();
    return temp_row;
}

#endif