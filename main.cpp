#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
#include<algorithm>
#include<sstream>
#include<istream>

using namespace std;

typedef vector<int> row;
typedef vector<vector<int>> collection_of_rows;
typedef vector<vector<vector<int>>> collection_of_matrices;

const unsigned short NO_OF_MATRICES = 6;
const unsigned short MATRIX_ROW_SIZE = 6;
const unsigned short MATRIX_COLUMN_SIZE = 5;
collection_of_matrices matrices;
collection_of_matrices lexicographic_min;

int search_in_array(int v[], int s, int l) {
	for(int i = 0; i < l; i++) {
		if(v[i] == s) {
			return i;
		}
	}
	return 0;
}

int factorial(int n) {
	return (n == 1 || n == 0) ? 1 : n * factorial(n-1);
}

int classification_of_permutations(void) {
	int i,j,k,l,m,h,dummy,r,type_size,m_vertices;
	bool flag = false;
	bool changemin = false;

	cout<<"Enter the m_vertices: ";
	cin>>m_vertices;
	int rot_sys[m_vertices][m_vertices-1];
	int new_clock[m_vertices][m_vertices-1];
	cout<<"Enter the type size: ";
	cin>>type_size;
	cout<<"Enter the rotation system: "<<endl;
	for(i = 0; i < m_vertices; i++)
		for(j = 0; j < (m_vertices-1); j++)
			cin>>rot_sys[i][j];

	int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

	std::sort(v, v+m_vertices);

	int final_bundle_size = factorial(m_vertices - type_size);

	int num_bundle = 1, bundle_size = 1;

	do {
		dummy = search_in_array(rot_sys[v[0]-1], v[1], (m_vertices - 1));
		for(i = 0; i < (m_vertices - 1); i++) {
			flag = false;
			new_clock[0][i] = 1 + search_in_array(v, rot_sys[v[0]-1][(dummy+i) % (m_vertices-1)], m_vertices);
		}
		for(int h = 1; h < m_vertices; h++) { // finding the relabeled vertices and rotating them such that least element comes first.
			flag = false;
			dummy = search_in_array(rot_sys[v[h]-1], v[0], (m_vertices-1)); // looking for the clockwise direction
			for(i = 0; i < (m_vertices - 1); i++) {
				flag = false;
				new_clock[h][i] = 1 + search_in_array(v, rot_sys[v[h]-1][(dummy + i) % (m_vertices - 1)], m_vertices);
			}
		}

		collection_of_rows matrix;
		for(i = 0; i < m_vertices; i++) {
			row temp_row;
			for(j = 0; j < (m_vertices - 1); j++) {
				temp_row.push_back(new_clock[i][j]);
			}
			matrix.push_back(temp_row);
		}
	matrices.push_back(matrix);
	}while(std::next_permutation(v,v+6));
	return 0;
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

int main(void) {
	classification_of_permutations();
	collection_of_matrices temp_matrices = matrices;
	for(int i = 0; i < 120; i++) {
		lexicomini_of(matrices, matrices[0]);
	}
	for(int i = 0; i < lexicographic_min.size(); i++) {
		cout << "Matrix " << i+1 << ":" << endl;
		for(int j = 0; j < MATRIX_ROW_SIZE; j++) {
				for(int k = 0; k < MATRIX_COLUMN_SIZE; k++)
						cout << lexicographic_min[i][j][k] << " ";
				cout << endl;
		}
		cout << endl;
	}
  return 0;
}