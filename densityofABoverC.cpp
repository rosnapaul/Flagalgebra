// This program is to find the density of two labeled flags (A,B) over another unlabeled matrix C(big rotation system).
// How this program works? Suppose the small matrix A,B which belongs to the same type (of size 3) have size 5 and big matrix C has size 7.  To find the density of A, B in C, we have to choose  any 5 (=|A|) vertices from the 7 (=|C|) vertices. 
//This chossing can be done by relabeling the vertices of big matrix and consider only 5 of them. 
// Each vector "v" for the relabelling was given by the combination (5 \choose 10). 
// Once we obtained the relabeled of the big matrix, the first 3 vertices corresponds to type. The first 5 vertices corresponds to flag A and the first 3 together with last two (=5) corresponds to the seconf flagB.
// Here all the flags have labelling from 1 to 5. So for submatrix corresponding to B, the elements 6,7 has to be relabelled to 4,5 resp to help to get the comparision.


				// An example . 
			// In the next step, we find the matrix corresponding to this choosing. this matrix must be in the size of the given small matrix.
			// To fing the sub matrices we need to avoid some rows and columns. In our example to generate submatrix coresponding to A  we remove rows (>flagsize) 6,7 from C 
			// and also elements 6,7 from each of the remaining row.  To generate submatrix coresponding to B  we remove rows 4,5 from C 
			// and also elements 4,5 from each of the remaining row. 
			//
			// 2 3 4 5 6 7                                       2 3 4 5          2 3 6 7                                2 3 4 5              2 3 4 5
			// 1 3 4 5 6 7                                       1 3 4 5          1 3 6 7                                1 3 4 5               1 3 4 5
			// 1 2 4 5 6 7                                        1 2 4 5   &    1 2 6 7     .---------------->     1 2 4 5     &        1 2 4 5 
			// 1 2 3 5 6 7  ------------------------>       1 2 3 5                                                      1 2 3 5
			// 1 2 3 4 6 7                                        1 2 3 4                                                      1 2 3 4
			// 1 2 3 4 5 7                                                             1 2 3 7                                                              1 2 3 5                  
			//1 2 3 4 5 6                                                               1 2 3 6                                                              1 2 3 4
// compare these submatrices it with the given flags A and B. If the first submatrix matches with A and the second submatrix matches with B then we count it. 
// This count divided by the total number of combinations gives the densty of A over B.

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#include<sstream>
#include"read_matrix.h"
using namespace std;

typedef vector<int> row;
typedef vector<bool> bool_array;
typedef vector<vector<int> > matrix;
typedef vector<vector<vector<int> > > vector_matrix;

int lowestinarray(vector<int> arow) {
	int lowest_ele,k = 0;
	lowest_ele = arow[0];
	for(int i = 0; i < arow.size(); i++)
		if(arow[i] < lowest_ele) {
			lowest_ele = arow[i];
			k = i;
		}
	return k;
}

void rotating_array(vector<vector<vector<int> > > &compmat, int m_vertices) {
	int mini_position;
	int r,rotate_copy[compmat.size()][m_vertices - 1];
	for(int k = 0; k < compmat.size(); k++) {
		for(int i = 0; i < compmat[k].size(); i++) {          
			mini_position = lowestinarray(compmat[k][i]);
			for(int j = 0; j < compmat[k][i].size(); j++) {
				r = (mini_position + j) % (m_vertices - 1);
				rotate_copy[i][j] = compmat[k][i][r];
			}
			for(int j = 0; j < compmat[k][i].size(); j++)
				compmat[k][i][j] = rotate_copy[i][j];
		}
	}
}

int search_in_vector(vector<int> some_row, int s) {
	for(int i = 0; i < some_row.size(); i++)
		if(some_row[i] == s)
			return i;
	return 0;
}

int search_in_array(int v[], int s, int l) {
	for(int i = 0; i < l; i++)
		if(v[i] == s)
			return i + 1;
	return 0;
}	

bool_array compare_with_given_matrix(vector_matrix matrices, matrix given_matrix) {
	bool_array temp;
	for(int matrix = 0; matrix < matrices.size(); matrix++) {
		bool same = true;
		for(int row = 0; row < matrices[matrix].size(); row++) {
			for(int col = 0; col < matrices[matrix][row].size(); col++) {
				if(matrices[matrix][row][col] != given_matrix[row][col]) {
					same = false;
					break;
				}
			}
		}
		if(same == true) temp.push_back(true);
		else temp.push_back(false);
	}
	return temp;
}

int count_of_same_matrices(bool_array A, bool_array B) {
	int count = 0;
	if(A.size() != B.size()) {
		cout<<"Both arrays don't have same no. of elements."<<endl;
		return 1;
	} else {
		for(int temp = 0; temp < A.size(); temp++)
			if(A[temp] == true && B[temp] == true)
				++count;
	}
	return count;
}

row read_info(string filename) {
	char temp_char;
	ifstream infile;
	infile.open(filename); // To read the file
	row temp_row;
	int temp = 0;
	while(infile.get(temp_char) && temp_char != '\n') {
		if(temp_char == ' ') {
			temp_row.push_back(temp);
			temp = 0;
			continue;
		}
		temp = (temp * 10) + (temp_char - '0');
	}
	infile.close();
	return temp_row;
}

int main() {
	int m_vertices,i,j,k,l,m,dummy,r,type_size;
	cout<<"Enter the number of vertices"<<endl;
	cin>>m_vertices;
	type_size = 5; //TODO ask type size later
	matrix min, new_mat;
	vector_matrix compmat;

	int v[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
	std::sort(v,(v + m_vertices));

	// Collecting the Rotation System, this is the big rotation system . 
	matrix rot_sys {{2,3,4,5,6,7}, {1,3,4,5,6,7}, {1,2,4,5,6,7}, {1,2,3,5,6,7}, {1,2,3,4,6,7}, {1,2,3,4,5,7}, {1,2,3,4,5,6}};
	/* cout<<"Enter the rotation system"<<endl;
	for(i = 0; i < m_vertices; i++) {
		row temp1;
		for(j = 0; j < (m_vertices - 1); j++) {
			cin>>k;
			temp1.push_back(k);
		}
		rot_sys.push_back(temp1);
	} */
	
	//  Relabeling of the Vertices corresponding to combination
	do {
		matrix change_mat;
		for(l = 0; l < m_vertices; l++) { // we avoid the extra rows in the big matrix	
			row temp3;
			for(m = 0; m < m_vertices-1; m++) {
				k = search_in_array(v, rot_sys[v[l] - 1][m], m_vertices);
				temp3.push_back(k);
			}
			change_mat.push_back(temp3);
		} 
		compmat.push_back(change_mat);
	}while(std::next_permutation(v,v+m_vertices));
			
	rotating_array(compmat, m_vertices); 
	
	int extra_vert, flagsize;
	extra_vert = (m_vertices - type_size) / 2;
	//cout<<"extr vert"<<extra_vert<<endl;
	flagsize = type_size + extra_vert;
	//cout<<"flagsize"<<flagsize<<endl;
	int f_1[flagsize], f_2[flagsize];
	
	//TODO: make this program in such a way that the matrices F_1 and F_2 are automatically collected from the file.
	// we use flags only of the same type.
	// may be we can add some steps to check whether the flags are coming from the same type.

	//matrix F_1 = {{2,3,4,5}, {1,3,4,5}, {1,2,4,5}, {1,2,3,5}, {1,2,3,4}};
	//matrix F_2 = {{2,3,4,5}, {1,3,4,5}, {1,2,4,5}, {1,2,3,5}, {1,2,3,4}};
	
	// To read from type matrices
	row info = read_info("./output/info.txt");
	for(int z = 0; z < info.size(); z++) {
		string filename = "./output/type" + to_string(z+1) + ".txt";
		cout<<filename<<":"<<endl;
		vector_matrix tmp = get_matrices(filename,info[z],m_vertices,(m_vertices - 1));
		for(int y = 0; y < tmp.size(); y++) {
			matrix F_1 = tmp[y];
			for(int x = 0; x < tmp.size(); x++) {
				matrix F_2 = tmp[x];
				// matrix F_1 {{2,3,4,5,6}, {1,3,4,5,6}, {1,2,4,5,6}, {1,2,3,5,6}, {1,2,3,4,6},{1,2,3,4,5}};
				// matrix F_2 {{2,3,4,5,6}, {1,3,4,5,6}, {1,2,4,5,6}, {1,2,3,5,6}, {1,2,3,4,6},{1,2,3,4,5}};
				// Just to see the changed matrix.
				vector_matrix pruned_matrices_1;
				//cout<<"The first changed matrix is"<<endl;
				for(k = 0; k < compmat.size(); k++) {
					matrix temp_matrix;
					for(i = 0; i < flagsize; i++) {
						row temp_row;
						for(j=0;j<compmat[k][i].size();j++) {
							if(compmat[k][i][j] > flagsize) continue;
							//cout<<compmat[k][i][j]<<" ";
							temp_row.push_back(compmat[k][i][j]);
						}
						//cout<<endl;
						temp_matrix.push_back(temp_row);
					}
					//cout<<endl;
					pruned_matrices_1.push_back(temp_matrix);
				}      
				bool_array first_comparison = compare_with_given_matrix(pruned_matrices_1,F_1);
				// Just to see the changed matrix.
				vector_matrix pruned_matrices_2;
				//cout<<"The second changed matrix is"<<endl;
				for(k = 0; k < compmat.size(); k++) {
					matrix temp_matrix;
					for(i = 0; i < compmat[k].size(); i++) {
						row temp_row;
						if((type_size <= (i % m_vertices)) && ((i % m_vertices) < flagsize)) continue;
						for(j = 0; j < compmat[k][i].size(); j++) {
							if((type_size < (compmat[k][i][j])) && ((compmat[k][i][j]) < (flagsize + 1))) continue;
							if(compmat[k][i][j] > flagsize) compmat[k][i][j] = compmat[k][i][j] - extra_vert;
							//cout<<compmat[k][i][j]<<" "; 
							temp_row.push_back(compmat[k][i][j]);
						}
						//cout<<endl;
						temp_matrix.push_back(temp_row);
					}
					//cout<<endl;
					pruned_matrices_2.push_back(temp_matrix);
				}
				bool_array second_comparison = compare_with_given_matrix(pruned_matrices_2, F_2);
				int count = count_of_same_matrices(first_comparison, second_comparison);
				if(count > 0) cout<<"Count of Similar Matrices are: "<<count<<endl;
			}
		}
	}
	return 0;
}