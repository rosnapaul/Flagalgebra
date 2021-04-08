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
	int i,j,k,l,m,h,dummy,r,type_size,m_vertices = 6;
	int rot_sys[m_vertices][m_vertices-1];
	int new_clock[m_vertices][m_vertices-1];
	bool flag = false;
	bool changemin = false;

	cout<<"Enter the type size: ";
	cin>>type_size;
	cout<<"Enter the rotation system: "<<endl;
	for(i = 0; i < m_vertices; i++)
		for(j = 0; j < (m_vertices-1); j++)
			cin>>rot_sys[i][j];

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

		cout << "bundle size " << bundle_size++ << endl;
		for(i = 0; i < m_vertices; i++) {
			for(j = 0; j < (m_vertices - 1); j++) {
				cout<<new_clock[i][j]<<" ";
			}
			cout<<endl;
		}

	}while(std::next_permutation(v,v+6));
	cout << "The output of this program is written to the terminal." << endl;
	return 0;
}

int main(void) {
    classification_of_permutations();
    return 0;
}