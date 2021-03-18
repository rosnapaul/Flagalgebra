// This programm is to find the fingerprint of a  given rotation system. This programm first collects a rotation system(you can view it as a matrix) from the user and store it as a vector. Then you have to choose a vertex as 1and a vertex as2. This is done by using a for loop
//  When two vertices are fixed, the we name the the other vertices from 3, 4.. in the order of their clockwise apparence aftetr the vertex named as 2 in the row (/vertex) named as 1. Now we relace the the old naming with the new naming and store each of these matrices
// Now we rotate each row of the matrix so that the lowest elemt comes first( plz note that it is rotation but not the rearrangement). We also rotate the given rotation system(matrix) and store it as the mini matrix.
// Then we take each element from the list of matrices we formed by relabelling and compare each of them and find the lexicographic minimum among them.  Which gives the fingerprint.
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
#include<algorithm>
#include<sstream>
#include<istream>

using namespace std;

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

	ofstream outfile;
	do {
		if(bundle_size == 1) {
			stringstream filename;
			filename<<"./bundle_of_permutations/"<<num_bundle<<".txt";
			outfile.open(filename.str().c_str(), ofstream::out);
			if(!outfile.good()) {
				cout<<"failed opening file"<< filename.str()<<endl;
			}
		}
		for(i = 0; i < m_vertices; i++) {
				cout<<v[i]<<" ";
		}
		cout<<endl<<endl;

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
				outfile<<new_clock[i][j]<<" ";
			}
			outfile<<endl;
		}
		outfile<<endl;

		if(bundle_size == (final_bundle_size + 1)) {
				bundle_size = 1;
				num_bundle++;
				outfile.close();
		}
	}while(std::next_permutation(v,v+6));
	cout << "The output of this program is written to 'bundle_of_permutations' folder." << endl;
	return 0;
}
