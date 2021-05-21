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

using namespace std;

typedef vector<int> row;
typedef vector<vector<int>> collection_of_rows;
typedef vector<vector<vector<int>>> collection_of_matrices;
typedef vector<vector<vector<vector<int>>>> collection_of_collection_of_matrices;

collection_of_collection_of_matrices classification_of_permutation;
collection_of_matrices matrices,lexicographic_min;
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
	int rot_sys[m_vertices][m_vertices-1] = {{2,3,4,5,6},
						{1,3,4,5,6},
						{1,2,4,5,6},
						{1,2,3,5,6},
						{1,2,3,4,6},
						{1,2,3,4,5}};
	int new_clock[m_vertices][m_vertices-1];
	memset( new_clock, 0, m_vertices*(m_vertices-1)*sizeof(int) );
	/* cout<<"Enter the type size: ";
	cin>>type_size; */
	type_size = 3;
	/* cout<<"Enter the rotation system: "<<endl;
 	 for(i = 0; i < m_vertices; i++)
		for(j = 0; j < (m_vertices-1); j++)
			cin>>rot_sys[i][j]; */

	int v[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};

	std::sort(v, v+m_vertices);

	int final_bundle_size = factorial(m_vertices - type_size);

	cout<<"The size of the bundles "<< final_bundle_size<<endl;

	int num_bundle = 1, bundle_size = 1;

	do {
		/* for(i = 0; i < m_vertices; i++) {
				cout<<v[i]<<" ";
		}
		cout<<endl<<endl; */

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

	/* // To print `classfication_of_permutation`
	cout<<"Classification of Permutation:"<<endl;
	for(int i=0; i<classification_of_permutation.size(); i++) {
		cout<<"The bundle size "<<i+1<<": "<<endl;
		for(int j=0; j<classification_of_permutation[i].size(); j++) {
			cout<<"Matrix "<<j+1<<": "<<endl;
			for(int k=0; k<classification_of_permutation[i][j].size(); k++) {
				for(int l=0; l<classification_of_permutation[i][j][k].size(); l++) {
					cout<<classification_of_permutation[i][j][k][l]<<" ";
				}
				cout<<endl;
			}
			cout<<endl;
		}
	} */

	for(int i=0; i<classification_of_permutation.size(); i++) {
		if(classification_of_permutation[i].size() > 1) {
			for(int j=0; j<classification_of_permutation[i].size(); j++) {
				lexicomini_of(classification_of_permutation[i], classification_of_permutation[i][0]);
			}
		} else if(classification_of_permutation[i].size() == 1) {
			lexicographic_min.push_back(classification_of_permutation[i][0]);
		}
		
	}
	
	// To print `lexicographic_min`
	cout<<"Lexicographic Minimum:"<<endl;
	for(int i=0; i<lexicographic_min.size(); i++) {
		cout<<"Matrix "<<i+1<<": "<<endl;
		for(int j=0; j<lexicographic_min[i].size(); j++) {
			for(int k=0; k<lexicographic_min[i][j].size(); k++) {
				cout<<lexicographic_min[i][j][k]<<" ";
			}
			cout<<endl;
		}
		cout<<endl;
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
	int counter = 0;
	cout<<"After Removing Duplicates:"<<endl;
	for(i = 0; i < lexicographic_min.size(); i++) {
		if(isDuplicate(i,duplicate_entries) == false) {
			cout<<"Matrix "<<++counter<<":"<<endl;
			for(j = 0; j < lexicographic_min[i].size(); j++) {
				for(k = 0; k < lexicographic_min[i][j].size(); k++) {
					cout << lexicographic_min[i][j][k] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
	}
	return 0;
}
