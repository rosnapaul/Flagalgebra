#include<iostream>
#include<fstream>
#include<sstream>
#include<istream>
#include<string>
#include"read_matrix.h"

static bool isDuplicate(int value, std::vector<int> vec) {
  for(int i = 0; i < vec.size(); i++) {
    if(vec[i] == value) {
      return true;
    }
  }
  return false;
}

int main(void) {
  row duplicate_entries;
  unsigned short i,j,k; // Variables Needed For Loop
  collection_of_matrices matrices = get_matrices("flags.txt",120); // `matrices` gets initialized with those matrices.

  for(unsigned short counter = 0; counter < matrices.size() - 1; counter++) {
    for(i = (counter + 1); i < matrices.size(); i++) { // matrices.size() gives 261
      bool duplicate = true;
      for(j = 0; j < MATRIX_ROW_SIZE; j++) { // MATRIX_ROW_SIZE is set as 6
        for(k = 0; k < MATRIX_COLUMN_SIZE; k++) { // MATRIX_COLUMN_SIZE is set as 5
          if(matrices[i][j][k] != matrices[counter][j][k]) {
            duplicate = false;
            break;
          }
				}
      }
      if(duplicate && (i != counter) && (isDuplicate(i,duplicate_entries) == false)) {
        duplicate_entries.push_back(i);
      }
    }
  }
  ofstream outfile;
  stringstream filename;
  filename<<"./distinct_flags.txt";
  outfile.open(filename.str().c_str(), ofstream::out);
  if(!outfile.good()) {
    cout << "failed opening file: " << filename.str() << endl;
	}
  for(i = 0; i < matrices.size(); i++) {
    if(isDuplicate(i,duplicate_entries) == false) {
      for(j = 0; j < MATRIX_ROW_SIZE; j++) {
        for(k = 0; k < MATRIX_COLUMN_SIZE; k++) {
          outfile << matrices[i][j][k] << " ";
        }
        outfile << endl;
      }
      outfile << endl;
    }
  }
  outfile.close();
  cout << "The output of this program is written to 'distinct_flags.txt'" << endl;
  return 0;
}