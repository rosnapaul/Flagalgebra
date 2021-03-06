#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
#include<algorithm>
#include<sstream>
#include<istream>
#include <typeinfo>
#include<cstring>
#include"read_matrix.h"

using namespace std;

typedef vector<int> row;
typedef vector<vector<int> > collection_of_rows;
typedef vector<vector<vector<int> > > collection_of_matrices;
typedef vector<vector<vector <vector<int> > > > collection_of_collection_of_matrices;

collection_of_collection_of_matrices classification_of_permutation, matrices_in_type_matrix;
collection_of_matrices matrices,lexicographic_min,pruned_lexico_min;
collection_of_rows matrix;
row temp_row,duplicate_entries;

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

void lexicomini_of(vector<vector<vector<int> > > compmat, vector<vector<int> > &min) {
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
					//lexicographic_min.push_back(matrix);
					break;
				}
			}
		 	if(flag == true)
				break;
		}
	}
}

static bool isDuplicate(int value, std::vector<int> vec) {
  for(int i = 0; i < vec.size(); i++) {
    if(vec[i] == value) {
      return true;
    }
  }
  return false;
}

int main(void) {
	int i,j,k,l,m,h,dummy,r,type_size,m_vertices;
	bool flag = false;
	bool changemin = false;

	/* cout<<"Enter the m_vertices: ";
	cin>>m_vertices; */
	m_vertices = 6;
	//int rot_sys[m_vertices][m_vertices-1] = {{2,3,4,5,6}, {1,3,4,5,6}, {1,2,4,5,6}, {1,2,3,5,6}, {1,2,6,3,4}, {1,2,5,3,4}};
	// To read from the `input.txt` file (reads only one matrix)
	collection_of_matrices tmp = get_matrices("input.txt",1,m_vertices,m_vertices-1);
	collection_of_rows rot_sys;
	for(i = 0; i < 1; i++)
  for(j = 0; j < tmp[i].size(); j++){
		   row temp_rot;
			for(k = 0; k < tmp[i][j].size(); k++){
				temp_rot.push_back(tmp[i][j][k]);
			}
			rot_sys.push_back(temp_rot);
		}
  cout<<"hello";
				for(j = 0; j < tmp[i].size(); j++){
					for(k = 0; k < tmp[i][j].size(); k++)
						cout<<tmp[i][j][k]<<" ";
						cout<<endl;
					}
	// To print the `rot_sys` matrix.
	for(i = 0; i < rot_sys.size(); i++) {
		for(j = 0; j < rot_sys[i].size(); j++)
			cout<<rot_sys[i][j]<<" ";
		cout<<endl;
	}

 /*
	int new_clock[m_vertices][m_vertices-1];
	memset( new_clock, 0, m_vertices*(m_vertices-1)*sizeof(int) );

	type_size = 5;

	int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

	std::sort(v, v+m_vertices);

	int final_bundle_size = factorial(m_vertices - type_size);

	cout<<"The size of the bundles "<< final_bundle_size<<endl;

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

		for(i = 0; i < m_vertices; i++) {
			for(j = 0; j < (m_vertices - 1); j++) {
				//cout<<new_clock[i][j]<<" ";
				temp_row.push_back(new_clock[i][j]);
			}
			matrix.push_back(temp_row);
			temp_row.clear();
		}
		matrices.push_back(matrix);
		matrix.clear();

		if(bundle_size == final_bundle_size) {
			bundle_size = 1;
			++num_bundle;
			classification_of_permutation.push_back(matrices);
			matrices.clear();
		} else {
			++bundle_size;
		}
	}while(std::next_permutation(v,v+m_vertices));



	for(int i=0; i<classification_of_permutation.size(); i++) {
		if(classification_of_permutation[i].size() > 1) {
			//for(int j=0; j<classification_of_permutation[i].size(); j++) {
				lexicomini_of(classification_of_permutation[i], classification_of_permutation[i][0]);
				lexicographic_min.push_back(classification_of_permutation[i][0]);
			//}
		} else if(classification_of_permutation[i].size() == 1) {
			lexicographic_min.push_back(classification_of_permutation[i][0]);
		}

	}


	// To prune the duplicates
	for(unsigned int counter = 0; counter < lexicographic_min.size() - 1; counter++) {
    	for(i = (counter + 1); i < lexicographic_min.size(); i++) {
      		bool duplicate = true;
      		for(j = 0; j < lexicographic_min[i].size(); j++) {
        		for(k = 0; k < lexicographic_min[i][j].size(); k++) {
          			if(lexicographic_min[i][j][k] != lexicographic_min[counter][j][k]) {
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
	for(i = 0; i < lexicographic_min.size(); i++) {
		if(isDuplicate(i,duplicate_entries) == false) {
			pruned_lexico_min.push_back(lexicographic_min[i]);
		}
	}


	// To reduce the matrix
	collection_of_matrices reduced_matrices;
	for(i = 0; i < pruned_lexico_min.size(); i++) {
			collection_of_rows temp_matrix;
			for(j = 0; j < (pruned_lexico_min[i].size() - 1); j++) {
				row temp_row;
				for(k = 0; k < pruned_lexico_min[i][j].size(); k++) {
					if(pruned_lexico_min[i][j][k] < (type_size + 1)) {
						temp_row.push_back(pruned_lexico_min[i][j][k]);
					}
				}
				temp_matrix.push_back(temp_row);
			}
			reduced_matrices.push_back(temp_matrix);
	}



	// To retrieve `type_matrices`
	collection_of_matrices type_matrices = get_matrices("file5vertices.txt",6,5,4);



	// To populate `matrices_in_type_matrix`
	for(i = 0; i < type_matrices.size(); i++) {
		collection_of_matrices temp_collection;
		matrices_in_type_matrix.push_back(temp_collection);
	}

	// To compare reduced matrices with type matrices
	for(i = 0; i < reduced_matrices.size(); i++) {
		for(int type = 0; type < type_matrices.size(); type++) {
			bool is_same = true;
			for(j = 0; j < reduced_matrices[i].size(); j++) {
				for(k = 0; k < reduced_matrices[i][j].size(); k++) {
					// To break the loop if element is not same
					if(reduced_matrices[i][j][k] != type_matrices[type][j][k]) {
						is_same = false;
						break;
					}
				}
				// To prevent checking other rows since one element is not same
				if(is_same == false) break;
			}
			// To push to the specific type the equivalent matrix from the pruned_lexico_min matrices.
			if(is_same == true) {
				matrices_in_type_matrix[type].push_back(pruned_lexico_min[i]);
				break;
			}
		}
	}
	// To write the all matrices present in type matrices as separate file in `output` folder
  for(i = 0; i < matrices_in_type_matrix.size(); i++) {
  	ofstream outfile;
  	stringstream filename;
  	filename<<"./output/type"+std::to_string(i+1)+".txt";
  	outfile.open(filename.str().c_str(), ofstream::out);
		for(j = 0; j < matrices_in_type_matrix[i].size(); j++) {
			for(k = 0; k < matrices_in_type_matrix[i][j].size(); k++) {
				for(l = 0; l < matrices_in_type_matrix[i][j][k].size(); l++) {
					outfile<<matrices_in_type_matrix[i][j][k][l]<<" ";
				}
				outfile<<endl;
			}
			outfile<<endl;
		}
		 outfile.close();
	}
	write_info("./output/info.txt",matrices_in_type_matrix);
	// To print the all matrices present in type matrices
	for(i = 0; i < matrices_in_type_matrix.size(); i++) {
		cout<<"Matrices in Type "<<(i + 1)<<":"<<endl;
		for(j = 0; j < matrices_in_type_matrix[i].size(); j++) {
			cout<<"Matrix "<<(j + 1)<<":"<<endl;
			for(k = 0; k < matrices_in_type_matrix[i][j].size(); k++) {
				for(l = 0; l < matrices_in_type_matrix[i][j][k].size(); l++) {
					cout<<matrices_in_type_matrix[i][j][k][l]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
		}
		cout<<endl;
	}
*/
	return 0;
}
