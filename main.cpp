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

int main(void) {
	collection_of_collection_of_matrices classification_of_permutation;
	collection_of_matrices matrices;
	collection_of_rows matrix;
	row temp_row;
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
	type_size = 5;
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
	}
	return 0;
}
