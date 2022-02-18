// This program is to find the density of an unlabeled flag A over another unlabeled matrix B(big rotation system).
// How this program works? Suppose the small matrix A have size 4 and big matrix B has size 7.  To find the density of A in B, we have to choose  any 4 (=|A|) vertices from the 7 (=|B|) vertices.
//This chossing can be done by relabeling the vertices of big matrix and consider only 4 of them.
// Each vector "v" for the relabelling was given by the combination (7 \choose 4).
// Once we obtained the relabeled of the big matrix, the first 4 vertices corresponds to matrix A.



				// An example .

			// To find the sub matrices we need to avoid some rows and columns. In our example to generate submatrix coresponding to A  we remove rows (>smallsize) 5,6,7 from B
			// and also elements 5,6,7 from each of the remaining row.

			//
			// 2 3 4 5 6 7                                       2 3 4
			// 1 3 4 5 6 7                                       1 3 4
			// 1 2 4 5 6 7                                        1 2 4
			// 1 2 3 5 6 7  ------------------------>       1 2 3
			// 1 2 3 4 6 7
			// 1 2 3 4 5 7
			//1 2 3 4 5 6
// compare these submatrices it with the given  A. If they match, we count it.
// Here we are over counting. Since, the program runs for 7! permutations.

// if the first 4 vertices are fixed, then we dont have to bother about the remaining (3! is extra) and first four vertices is reapeating in 7!. Total we need only 35 cases out of 7!=5040.
// But since we also counting reverse rotation system, our base os in 70. So we have to divide our count by 72 (since 5040/72 = 70)
// This count gives us the density.
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
#include<algorithm>
#include <stdio.h>
#include <string.h>
#include"read_matrix.h"
using namespace std;

typedef vector<int> row;
typedef vector<bool> bool_array;
typedef vector<vector<int> > matrix;
typedef vector<vector<vector<int> > > vector_matrix;
typedef vector<vector<bool> > bool_matrix;
int lowestinarray(vector<int> arow) {
	int lowest_ele,k = 0;
	lowest_ele = arow[0];
	for(int i = 0; i < arow.size(); i++)
		if(arow[i] < lowest_ele){
			lowest_ele = arow[i];
	        k = i;
		}
	return k;
}

void rotating_array(vector<vector<vector<int> > > &compmat, int m_vertices) {
	int mini_position;
	int r,rotate_copy[compmat.size()][m_vertices-1];
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
	return -1;
}

int search_in_array(int v[], int s, int l) {
	for(int i = 0; i < l; i++)
		if(v[i]==s)
			return i+1;
	return 0;
}

bool_array compare_with_given_matrix(vector_matrix matrices, matrix given_matrix) {
	bool_array temp;
	for(int matrix=0; matrix<matrices.size(); matrix++) {
		bool same = true;
		for(int row=0; row<matrices[matrix].size(); row++) {
			for(int col=0; col<matrices[matrix][row].size(); col++) {
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

static bool isDuplicate(int value, std::vector<int> vec) {
  for(int i = 0; i < vec.size(); i++) {
    if(vec[i] == value) {
      return true;
    }
  }
  return false;
}

bool_array compare_with_bool_functions(bool_array A_1, bool_array A_2, bool_array A_3, bool_array A_4, bool_array A_5, bool_array A_6) {
	bool_array temp;
	for(int matrix=0; matrix<A_1.size(); matrix++) {

			 if (A_1[matrix] == true) {
				 temp.push_back(true);
				 continue;
			 }
			 else {
				 if (A_2[matrix] == true){
					 temp.push_back(true);
					 continue;

				 }
				 else {
					 if (A_3[matrix] == true){
						 temp.push_back(true);
						 continue;

					 }
					 else{
						 if (A_4[matrix] == true){
							 temp.push_back(true);
							 continue;

						 }
						 else{
							 if (A_5[matrix] == true){
								 temp.push_back(true);
								 continue;

							 }
							 else{
								 if (A_6[matrix] == true){
									 temp.push_back(true);


								 }
								 else{
									 temp.push_back(false);
								 }
							 }
						 }

					 }

				 }
			 }
		 }

	return temp;
}

int count_of_same_matrices(bool_array A) {
	int count = 0;

		for(int temp=0; temp<A.size(); temp++)
			if(A[temp] == true )
				++count;

	return count;
}

int main() {
	int m_vertices,i,j,k,l,m,dummy,r,smallsize,my_row;
	cout<<"Enter the number of vertices"<<endl;
	cin>>m_vertices; // in our case it is 7
	smallsize = 4; //TODO ask  size of the small matrix later
	matrix min, new_mat;
	vector_matrix compmat;
	matrix crossing0;
  row counting;
	int current_value;
	int v[] = {0,0,0,0};
	bool_matrix collection_bool_strings;



	ofstream outfile;
  	stringstream filename;
  	filename<<"./output/density_A_over_B.txt";
  	outfile.open(filename.str().c_str(), ofstream::out);
	// Collecting the Rotation System, this is the big rotation system .
	//matrix rot_sys {{2, 3, 4 ,5, 6, 7},{1, 3, 4, 5, 7, 6},{1, 2, 6, 4, 5, 7},{1, 2, 3, 6, 5, 7},{1, 2, 3, 4, 6, 7},{1, 2, 7, 5, 4, 3},{1, 6, 2, 3, 4, 5}};
	vector_matrix tmp = get_matrices("densityofAoverB_input.txt",6,m_vertices,m_vertices-1);
	for(int z=0; z< tmp.size(); z++)
	{
		int matcount = 0;
	matrix rot_sys = tmp[z];
	for(i = 0; i < m_vertices; i++) {
		for(j = 0; j < (m_vertices-1); j++)
			cout<<rot_sys[i][j]<<" ";
		cout<<endl;
	}
	// TODO: collect the rotation system from the file.
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
   	for(int a_1=1;a_1<m_vertices-2;a_1++){
			v[0] = a_1;

			for(int a_2 = a_1+1;a_2<m_vertices-1;a_2++){
				v[1] = a_2;

				for(int a_3 = a_2+1; a_3<m_vertices; a_3++){
					v[2] = a_3;

					for(int a_4 = a_3+1; a_4<m_vertices+1; a_4++){
						v[3] = a_4;

						matrix change_mat;
						for(l = 0; l <m_vertices; l++) { // we avoid the extra rows in the big matrix
							my_row= search_in_array(v,l+1,4);


							if(my_row>0){

							row temp3;
							for(m = 0; m < m_vertices-1; m++) {
								k = search_in_array(v, rot_sys[l][m], m_vertices-1);
				        if(k>0){
								 temp3.push_back(k);

								}}
							 change_mat.push_back(temp3);


					}
				}
						compmat.push_back(change_mat);
						matcount++;


					}
				}
			}
		}



	rotating_array(compmat, 4);



	for(int q_1=0; q_1<compmat.size();q_1++){
		cout<<"matrix"<<q_1<<endl;
		for(int q_2=0; q_2<compmat[q_1].size(); q_2++){
			for(int q_3=0; q_3<compmat[q_1][q_2].size();q_3 ++){

				cout<<compmat[q_1][q_2][q_3]<<" ";

			}
			cout<<endl;
		}
		cout<<endl;
	}

	int f_1[smallsize], f_2[smallsize];

	for(i=0;i<smallsize;i++){
		f_1[i]=0;
		f_2[i]=0;
		cout<<f_1[i]<<f_2[i];
	}
	cout<<endl;
	matrix F_1 = {{2,3,4}, {1,3,4}, {1,2,4}, {1,2,3}};
	matrix F_2 = {{2,3,4}, {1,3,4}, {1,4,2}, {1,3,2}};
	matrix F_3 = {{2,3,4}, {1,4,3}, {1,4,2}, {1,2,3}};
	matrix F_4 = {{2,4,3}, {1,4,3}, {1,2,4}, {1,2,3}};
	matrix F_5 = {{2,4,3}, {1,4,3}, {1,4,2}, {1,3,2}};
	matrix F_6 = {{2,4,3}, {1,3,4}, {1,2,4}, {1,3,2}};



	//changed matrix
	//TODO: no need to print these!!
	/*
	vector_matrix pruned_matrices_1;
	//cout<<"The first changed matrix is"<<endl;
	for(k = 0; k < compmat.size(); k++) {

		matrix temp_matrix;

			for(i = 0; i < smallsize; i++) {
			row temp_row;

			for(j=0;j<compmat[k][i].size();j++) {
				if(compmat[k][i][j] > smallsize) continue;
				//cout<<compmat[k][i][j]<<" ";
				temp_row.push_back(compmat[k][i][j]);
			}
			//cout<<endl;
			temp_matrix.push_back(temp_row);
		}
		//cout<<endl;
		pruned_matrices_1.push_back(temp_matrix);
	}
 */
	bool_array first_comparison_1 = compare_with_given_matrix(compmat,F_1);
  bool_array first_comparison_2 = compare_with_given_matrix(compmat,F_2);
	bool_array first_comparison_3 = compare_with_given_matrix(compmat,F_3);
	bool_array first_comparison_4 = compare_with_given_matrix(compmat,F_4);
	bool_array first_comparison_5 = compare_with_given_matrix(compmat,F_5);
	bool_array first_comparison_6 = compare_with_given_matrix(compmat,F_6);
	bool_array final_comparison = compare_with_bool_functions(first_comparison_1, first_comparison_2, first_comparison_3,first_comparison_4,first_comparison_5,first_comparison_6);
  collection_bool_strings.push_back(final_comparison);

	current_value = (count_of_same_matrices(final_comparison));
   cout<<"count"<<current_value<<endl;
		if(search_in_vector(counting,current_value) == -1) counting.push_back(current_value);


	outfile<<"Count of Similar Matrices are: "<<(count_of_same_matrices(final_comparison))<<endl;

	rot_sys.clear();
	//change_mat.clear();
	//pruned_matrices_1.clear();
	compmat.clear();
	//temp_matrix.clear();
}

 matrix converted_bool;
 for(int i=0; i<collection_bool_strings.size(); i++ )
 { row temp;
	 for(int j=0; j<collection_bool_strings[i].size(); j++)
	 {
		 if (collection_bool_strings[i][j] == true){
			 temp.push_back(1);
			 cout<<"it is done"<<endl;
		 }
		 else {
			 temp.push_back(0);
			 cout<<"false part also done";
		 }

	 }
	 converted_bool.push_back(temp);

 }

 for(int i=0; i<converted_bool.size(); i++ )
 {
	for(int j=0; j<converted_bool[i].size(); j++)
	{
	 cout<<converted_bool[i][j]<<" ";

	}
	 cout<<endl;

 }
 cout<<"now going to duplicate"<<endl;
 row duplicate_entries;
 for(unsigned int counter = 0; counter < converted_bool.size() - 1; counter++) {
	 for(i = (counter + 1); i < converted_bool.size(); i++) {
		 bool duplicate = true;
		 for(j = 0; j < converted_bool.size(); j++) {
			 for(k = 0; k < converted_bool[i].size(); k++) {
				 if(converted_bool[i][j] != converted_bool[counter][j]) {

					 duplicate = false;
					 break;
				 }
			 }
		 }
		 cout<<"here is the issue"<<endl;
		 if(duplicate && (i != counter) && (isDuplicate(i,duplicate_entries) == false)) {
			 duplicate_entries.push_back(i);
			 cout<<"i pushed it"<<endl;
		 }
	 }
 }

	matrix pruned_lexico_min;
 for(i = 0; i < converted_bool.size(); i++) {
	 if(isDuplicate(i,duplicate_entries) == false) {
		 pruned_lexico_min.push_back(converted_bool[i]);
	 }
 }

 // To print the pruned matrices
 cout<<endl;
 cout<<endl;
	cout<<"After Pruning:"<<endl;
 int counter = 0;
 for(i = 0; i < pruned_lexico_min.size(); i++) {

		 for(j = 0; j < pruned_lexico_min[i].size(); j++) {

				 cout << pruned_lexico_min[i][j] << " ";


		 }
		 cout << endl;
 }
  for(int g=0;g<counting.size();g++){
		outfile<<counting[g]<<" ";
	}
	outfile<<"total number of different graphs"<<counting.size();
	outfile.close();
	return 0;
}
