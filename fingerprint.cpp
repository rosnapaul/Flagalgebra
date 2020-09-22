// This programm is to find the fingerprint of a  given rotation system. This programm first collects a rotation system(you can view it as a matrix) from the user and store it as a vector. Then you have to choose a vertex as 1and a vertex as2. This is done by using a for loop
//  When two vertices are fixed, the we name the the other vertices from 3, 4.. in the order of their clockwise apparence aftetr the vertex named as 2 in the row (/vertex) named as 1. Now we relace the the old naming with the new naming and store each of these matrices
// Now we rotate each row of the matrix so that the lowest elemt comes first( plz note that it is rotation but not the rearrangement). We also rotate the given rotation system(matrix) and store it as the mini matrix. 
// Then we take each element from the list of matrices we formed by relabelling and compare each of them and find the lexicographic minimum among them.  Which gives the fingerprint.




#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>

using namespace std;


typedef vector<int> row;
typedef vector < vector<int> > matrix;
typedef vector<vector<vector<int> >  > vector_matrix;

int lowestinarray(vector <int> arow)
{
	int lowest_ele,k;
	k=0;
	lowest_ele = arow[0];
	for(int i=0;i< arow.size(); i++)
	{
		if(arow[i]<lowest_ele)
		{ lowest_ele = arow[i];
	          k=i;
		}
	}
	return k;
}
	

void rotating_array (vector<vector<int> > & new_mat, int m_vertices)
{
	int mini_position;
	
   int r, rotate_copy[new_mat.size()][m_vertices-1];
        cout<<new_mat.size()<<endl;
 
	
	   for(int i=0; i< new_mat.size();i++)
	{  
                
		mini_position = lowestinarray( new_mat[i]);
		for(int j=0; j<new_mat[i].size();j++)
		{
			
			r= (mini_position + j) % (m_vertices-1);

	  rotate_copy[i][j] = new_mat[i][r];
	 
				
				
			
		}
		 
	
	for(int j=0; j<new_mat[i].size();j++)
		{
			
		

	  new_mat[i][j] = rotate_copy[i][j] ;
	 
				
			
		}
	
}
}



int search_in_vector( vector<int> some_row , int s)
{ 
   for(int i=0; i< some_row.size(); i++)
   {
	   if (some_row[i] == s)
	   { 
             
			 return i;
	   }
   }
}
			 



int search_in_array(int v[], int s , int l)
{
	int i;
	for(i=0; i< l; i++)
	{
		if (v[i]==s)
		{
			return i+1;
		}
	}
}	

int main()
{
	int m_vertices,i,j,k,l,m,dummy,r;
	cout<<"Enter the number of vertices"<<endl;
	cin>>m_vertices;
	matrix rot_sys;
	matrix min;
	matrix new_mat;
	vector_matrix compmat;
	
	
	int v[m_vertices];
	
	
	
	// collecting the rotation sysytem
	cout<<"Enter the rotation system"<<endl;
	for(i=0; i< m_vertices; i++)
	  {
		  row temp1;
		for(j=0; j<m_vertices-1; j++)
		  {
			cin>>k;
			temp1.push_back(k);
			
        	}
			rot_sys.push_back(temp1);
   	}
	
	
	
	//copiying the given rotation system as the mininum matrix.
	
	
	for(i=0; i< rot_sys.size(); i++)
	  {
		   row temp2;
		for(j=0; j<rot_sys[i].size(); j++)
		  {
		     temp2.push_back(rot_sys[i][j]);
			
        	}
			min.push_back(temp2);
   	  }
	
	
	// generating all possible relabeling of the vertices
	for (v[0] =1; v[0] < m_vertices+1; v[0]++) // for choosing v1 and v2 for finding the finger print.
	{ 
        for(v[1]=1; v[1] < m_vertices+1; v[1]++)
		{ 
   		if (v[1]==v[0]) continue;
           
		   dummy = 1+search_in_vector( rot_sys[v[0]-1], v[1]);
			for (j=0; j< m_vertices-2; j++)
			{ 
                      
                     r= (dummy +j) % (m_vertices -1);
				 
				     v[j+2] = rot_sys[v[0] -1][r];
					 
					 
			}	
			
			

                 for (l=0; l< m_vertices; l++)
	          {    row temp3;
		  
		          for(m=0; m< m_vertices-1; m++)
		               {
			                 k= search_in_array(v,rot_sys[v[l]-1][m], m_vertices);
			                 temp3.push_back(k);
							
		                }
		            
		           new_mat.push_back(temp3);
				    
	            } 
	             
		}
	}
	 cout<<"i am here"<<endl;
	rotating_array(new_mat, m_vertices);

   //TODO calling function of lexicomin.
  
 
for(i=0; i< new_mat.size(); i++)
   {
		for(j=0; j<new_mat[i].size();j++){
			cout<<new_mat[i][j]<<"  ";
        }
		cout<<endl;
		if((i%m_vertices) ==m_vertices-1)
			cout<<endl;
		
   	}



  
	
	
	//printing the rotation system

//	for(i=0; i<  m_vertices; i++)
//	{
		
//		for(j=0;j<m_vertices-1; j++)
//		{
//			cout<<rot_sys[i][j]<<"     ";
//		}
//		cout<<endl;
//	}
	
}	