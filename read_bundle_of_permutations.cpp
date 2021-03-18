#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

typedef vector<int> row;
typedef vector<vector<int>> collection_of_rows;
typedef vector<vector<vector<int>>> collection_of_matrices;

const unsigned short NO_OF_MATRICES = 6;
const unsigned short MATRIX_ROW_SIZE = 6;
const unsigned short MATRIX_COLUMN_SIZE = 5;
collection_of_matrices lexicographic_min;

collection_of_matrices get_matrices(int fileNumber) {
	collection_of_matrices matrices;
	unsigned short i,j,k,temp; // Variables for Looping or Temporary Purposes
	unsigned char temp_char;
	ifstream infile;
	string file_dir = "./bundle_of_permutations/";
	string fileNum = to_string(fileNumber);
	infile.open(file_dir+fileNum+".txt"); // To read from bundle_of_permutations folder
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

void lexicomini_of(vector<vector<vector<int>>> compmat, vector<vector<int>> &min) {
	bool flag = false;
	for(int k = 0; k < compmat.size(); k++) {
		flag = false;
		for(int i = 0; i < compmat[k].size(); i++) {  
	    for(int j = 0; j < compmat[k][i].size(); j++) {
				if(compmat[k][i][j] > min[i][j]) {
					flag = true;
			 		break;
				}
				if(compmat[k][i][j] < min[i][j]) { 
					collection_of_rows matrix;       
					for(int i = 0; i < compmat[k].size(); i++) {
						row temp_row;
						for(int j=0;j < compmat[k][i].size(); j++) {
							min[i][j] = compmat[k][i][j];
							temp_row.push_back(min[i][j]);
						}
						matrix.push_back(temp_row);
					}
					lexicographic_min.push_back(matrix);
					break;
				}
			}
		 	if(flag == true)
				break;
		}
	}
}

void dump_lexicomgraphic_min(void) {
	unsigned short i,j,k;
	ofstream outfile;
	outfile.open("./flags.txt", ofstream::out);
	if(!outfile.good())
		cout<<"failed opening file "<<"./flags.txt"<<endl;
	for(i = 0; i < lexicographic_min.size(); i++) {
		for(j = 0; j < MATRIX_ROW_SIZE; j++) {
				for(k = 0; k < MATRIX_COLUMN_SIZE; k++)
						outfile << lexicographic_min[i][j][k] << " ";
				outfile << endl;
		}
		outfile << endl;
	}
}

int main(void) {
	for(int i = 1; i <= 120; i++) {
		collection_of_matrices matrices = get_matrices(i);
		lexicomini_of(matrices, matrices[0]);
	}
	dump_lexicomgraphic_min();
	cout << "The output of this program is written to 'flags.txt'." << endl;
	return 0;
}