// This program is to find the density of an unlabeled flag( small matrix) over another unlabeled flag (big rotation system)
// How this program works? Suppose the small matrix A has size 5 and big matrix B has size 10.  To find the density of A in B we have to choose  any 5 (=|A|) vertices from the 10 (=|B|) vertices. This chossing can be done by relabeling the vertices of big matrix and consider only 5 of them. 
// Each vector "v" for the relabelling was given by the combination (5 \choose 10). Here i am giving this combinations manually. TO DO: we should  rewrite the program such that the values if "v" are taken from a file.
// Once we obtained the relabeled sub matric of the big matrix, we find the lexicominimum of it ( ie we find the fingerprint of it) and compare it with the given small matrix. If the comparision is true then we count it. 
// This count divided by the total number of combinations gives the densty of A over B.

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
using namespace std;

typedef vector<int> row;
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

/*
void lexicomini_of( vector<vector<vector<int> > > compmat, vector<vector<int> >& min) { //call this function in the main() 
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
					for(int i = 0; i < compmat[k].size(); i++)
						for(int j=0;j < compmat[k][i].size(); j++)
							min[i][j] = compmat[k][i][j];
					break;
				}
			}
		 	if(flag == true)
				break;
		}
	}
}

void reverse_rotation (vector<vector<vector<int>>> &compmat, int size) {
	int h;
	for(int k = 0; k < size; k++) { 
        matrix new_mat;
		for(int i = 0; i < compmat[k].size(); i++) {           
        	row temp;
			temp.push_back(compmat[k][i][0]);
	        h = 1;
			for(int j = 0; j < (compmat[k][i].size() - 1); j++) {
				temp.push_back(compmat[k][i][(compmat[k][i].size()) - 1 - j]);
				h++;
			}
	    	new_mat.push_back(temp);
    	}
	    compmat.push_back(new_mat);
	}
}
*/
int main() {
	int m_vertices,i,j,k,l,m,dummy,r,type_size;
	cout<<"Enter the number of vertices"<<endl;
	cin>>m_vertices;
	matrix rot_sys, min, new_mat;
	vector_matrix compmat;

	//int v[m_vertices];
		
	int v[] = { 1,2,3,4,5,6,7,8,9,10,11,12,13};
	
	std::sort(v,v+m_vertices);
	

	// Collecting the Rotation System, this i the big rotation system . We still havent inputed the small matrix. which actually can be done by reading a file.
	cout<<"Enter the rotation system"<<endl;
	for(i = 0; i < m_vertices; i++) {
		row temp1;
		for(j = 0; j < (m_vertices - 1); j++) {
			cin>>k;
			temp1.push_back(k);
        }
		rot_sys.push_back(temp1);
   	}
	

	
	//  Relabeling of the Vertices corresponding to combination
	
	// here I explicitly giving the combinations, actually it has to be in a loop kinda structure where each
	// value of "v'" has to be taken from a file. In this loop like thing we introduce a variable "total_count" and increment it when we take new value for "v",
    // Hence "total_count" counts the total number of combinations. 
	
	  // cout<<"Enter the combination of all vertices"<<endl;
          // for(i=0;i<m_vertices;i++)
                       // cin>>v[i];	  // give here the coresponding combinations 
	        
				

				// An example suppose our chooen vertices are 1,2,3,5,6 out of, say 6 vertices. then our v = {1,2,3,5,6,4).
			// In the next step, we find the matrix corresponding to this choosing. this matrix must be in the size of the given small matrix.
			// to acheive that we need to avoid some extra rows and some extra integers in the remaining rows. 
			//
			// 2 3 4 5 6 7                                        2 3 4 5 6
			// 1 3 4 5 6 7                                       1 3 4 5 6            Here we avoided the 6th row and the interger 6.
			// 1 2 4 5 6 7                                        1 2 4 5 6
			// 1 2 3 5 6 7  ------------------------>            1 2 3 5 6 
			// 1 2 3 4 6 7                                        1 2 3 4 6
			// 1 2 3 4 5 7                                         1 2 3 4 5
			//1 2 3 4 5 6
   			do{
				   matrix change_mat;
			for(l = 0; l <m_vertices; l++) { // we avoid the extra rows in the big matrix
			     
				row temp3;
				for(m = 0; m < m_vertices-1; m++) {
					k = search_in_array(v, rot_sys[v[l]-1][m], m_vertices);
					//if(k>type_size) continue;  // here we avoid the appearence of the extra vertices in the remaining rows.
					temp3.push_back(k);
				}
				change_mat.push_back(temp3);
			} 
			     compmat.push_back(change_mat);
				 
				 
			}while(std::next_permutation(v,v+m_vertices));
			
			int f_1[5]= {0,0,0,0,0};
			
				cout<<"the array   f1"<<endl;
			for(i=0; i< 5;i++){
				cout<<f_1[i];
			}
			cout<<endl;
			
			int f_2[5]= {0,0,0,0,0};
			rotating_array(compmat, m_vertices);
			
			int F_1[m_vertices-1][m_vertices-2] = {{2,3,4,5,6},
			{1,3,4,5,6}, {1,2,4,5,6}, {1,2,3,5,6}, {1,2,3,4,6}, {1,2,3,4,5}};
			
			int F_2[m_vertices-1][m_vertices-2] = {{2,3,4,6,5}, {1,3,4,6,5}, {1,2,4,6,5}, {1,2,3,6,5}, {1,2,3,4,6}, {1,2,3,4,5}};
			
			// Just to see the changed matrix.
			cout<<" The changed matrix is"<<endl;
			for(k = 0; k <5; k++) {
				
			for(i = 0; i < compmat[k].size(); i++) {
				if ((i+1)%7 ==0) continue;
		for(j=0;j<compmat[k][i].size();j++){
			if (compmat[k][i][j] ==7) continue;
		//	if (compmat[k][i][j]  != F_1[i][j])
		//	{
		//		f_1[k]=1;
		//		cout<<k<<" "<<i<<" "<<j<<" "<<compmat[k][i][j]<<" "<<F_1[i][j]<<endl;
		//	}
			cout<<compmat[k][i][j];
			
		}
		cout<<endl;
		
	}      
			cout<<endl;
			cout<<k<<endl;
			cout<<endl;
			}			
			
			
				// Just to see the changed matrix.
			cout<<" The changed matrix is"<<endl;
			for(k = 0; k <5; k++) {
				
			for(i = 0; i < compmat[k].size(); i++) {
				if ((i+1)%6==0) continue;
		for(j=0;j<compmat[k][i].size();j++){
			if (compmat[k][i][j] ==6) continue;
			if (compmat[k][i][j]==7){
				compmat[k][i][j] = 6;
			    
			 }
				
		//	if(compmat[k][i][j]!= F_1[i][j])
		//	{
		//		f_2[k]=1;
		//		cout<<k<<" "<<i<<" "<<j<<" "<<compmat[k][i][j]<<" "<<F_1[i][j]<<endl;
		//	}
			
			cout<<compmat[k][i][j]; 
		}
		cout<<endl;
		
	}      
			cout<<endl;
			cout<<k<<endl;
			cout<<endl;
			}		
			
			
			cout<<"the array   f1"<<endl;
			for(i=0; i< 5;i++){
				cout<<f_1[i];
			}
			cout<<endl;
			
			cout<<"the array   f2"<<endl;
			for(i=0; i< 5;i++){
				cout<<f_2[i];
			}
			cout<<endl;
		//	Now take this matrix and find the fingerprint of this matrix by calling the function.
		// Then compare the fingerprint with the given small matrix.
		// if the comparision is true, int count++
		// then count/total_count gives the density. this value is retured to the "main" funtion in the original program.
		

		//-----------------------------------------------------------------------------------------------------------------------------------------------------------------
	
	
	
	
	/*
	// Copying the given Rotation System as the Mininum Matrix
	for(i = 0; i < rot_sys.size(); i++) {
		row temp2;
		for(j = 0; j < rot_sys[i].size(); j++)
		    temp2.push_back(rot_sys[i][j]);
		min.push_back(temp2);
		new_mat.push_back(temp2);
   	}

	compmat.push_back(new_mat);
	*/
	
/*
	// Generating All Possible Relabeling of the Vertices
	for (v[0] = 1; v[0] < (m_vertices + 1); v[0]++) { // For Choosing v1 and v2 for Finding the Fingerprint.
        for(v[1] = 1; v[1] < (m_vertices + 1); v[1]++) {
	        matrix new_mat;
   			if(v[1] == v[0]) continue;
			dummy = 1 + search_in_vector(rot_sys[v[0]-1], v[1]);
			for(j = 0; j < (m_vertices - 2); j++) {
				r = (dummy +j) % (m_vertices -1);
				v[j+2] = rot_sys[v[0] -1][r];
			}	
			for(l = 0; l < m_vertices; l++) {
				row temp3;
				for(m = 0; m < m_vertices-1; m++) {
					k = search_in_array(v, rot_sys[v[l]-1][m], m_vertices);
					temp3.push_back(k);
				}
				new_mat.push_back(temp3);
			} 
			compmat.push_back(new_mat);

		}
	}

	rotating_array(compmat, m_vertices);
    reverse_rotation(compmat, compmat.size());
	lexicomini_of(compmat,min);

   // TODO Calling Function of Lexicomin
	for(k=0; k< compmat.size();k++) {
    	for(i=0; i< compmat[k].size(); i++) {
			for(j=0; j<compmat[k][i].size();j++)
				cout<<compmat[k][i][j]<<"  ";
			cout<<endl;
			//if((i%m_vertices) ==m_vertices-1)
			//cout<<endl;
    	}
 		cout<<endl;
 	}

	cout<<" The lexicographic minimum is:"<<endl;
	for(i = 0; i < min.size(); i++) {
		for(j=0;j<min[i].size();j++)
			cout<<min[i][j]<<"     ";
		cout<<endl;
	}
	*/
	return 0;
}	
