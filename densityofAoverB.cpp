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
using namespace std;

typedef vector<int> row;
typedef vector<bool> bool_array;
typedef vector<vector<int>> matrix;
typedef vector<vector<vector<int>>> vector_matrix;

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

void rotating_array(vector<vector<vector<int>>> &compmat, int m_vertices) {
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
	return 0;
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

int count_of_same_matrices(bool_array A) {
	int count = 0;
	
		for(int temp=0; temp<A.size(); temp++)
			if(A[temp] == true )
				++count;
	
	return count;
}

int main() {
	int m_vertices,i,j,k,l,m,dummy,r,smallsize;
	cout<<"Enter the number of vertices"<<endl;
	cin>>m_vertices;
	smallsize = 4; //TODO ask  size of the small matrix later
	matrix min, new_mat;
	vector_matrix compmat;
 int matcount =0;

		
	int v[] = {1,2,3,4,5,6,7,8,9,10,11,12,13};
	
	std::sort(v,v+m_vertices);
	

	// Collecting the Rotation System, this is the big rotation system . 
	matrix rot_sys {{2, 3, 4 ,5, 6, 7}, 
		{1, 3, 4, 5, 7, 6}, 
			{1, 2, 6, 4, 5, 7}, 
				{1, 2, 3, 6, 5, 7}, 
					{1, 2, 3, 4, 6, 7}, 
						{1, 2, 7, 5, 4, 3}, 
	{1, 6, 2, 3, 4, 5}}; 
	
	
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
	
	
	        
				

   			do{
				   matrix change_mat;
			for(l = 0; l <m_vertices; l++) { // we avoid the extra rows in the big matrix
			     
				row temp3;
				for(m = 0; m < m_vertices-1; m++) {
					k = search_in_array(v, rot_sys[v[l]-1][m], m_vertices);
					
					temp3.push_back(k);
				}
				change_mat.push_back(temp3);
			} 
			     compmat.push_back(change_mat);
				 
				 matcount++;
			}while(std::next_permutation(v,v+m_vertices));
			
			rotating_array(compmat, m_vertices); 
			
			
			
			int f_1[smallsize], f_2[smallsize];
			
			for(i=0;i<smallsize;i++){
				f_1[i]=0;
				f_2[i]=0;
				cout<<f_1[i]<<f_2[i];
			}	
			
			
			cout<<endl;
			
		

			matrix F_1 = {{2,3,4}, {1,4,3}, {1,2,4}, {1,3,2}};
			
			//changed matrix
			//TODO: no need to print these!!
			vector_matrix pruned_matrices_1;
			cout<<"The first changed matrix is"<<endl;
			for(k = 0; k < compmat.size(); k++) {
				
				matrix temp_matrix;
				
					for(i = 0; i < smallsize; i++) {
					row temp_row;
				
					for(j=0;j<compmat[k][i].size();j++) {
						if(compmat[k][i][j] > smallsize) continue;
						cout<<compmat[k][i][j]<<" ";
						temp_row.push_back(compmat[k][i][j]);
					}
					cout<<endl;
					temp_matrix.push_back(temp_row);
				}
				cout<<endl;
				pruned_matrices_1.push_back(temp_matrix);
			}      



      
			bool_array first_comparison = compare_with_given_matrix(pruned_matrices_1,F_1);
			
		
			
		
		
		

			cout<<"Count of Similar Matrices are: "<<(count_of_same_matrices(first_comparison))/72<<endl;
			
		 cout<<"The total count is "<<matcount<<endl;
	
	
	

	return 0;
}	
