
// Program to find the fingerprint of the given rotation system in a more efficent way.

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;
int search_in_array(int v[], int s , int l)
{
	int i;
	for(i=0; i< l; i++)
	{
		if (v[i]==s)
		{
			return i;
		}
	}
}	

int main()
{
	int m_vertices,i,j,k,l,m,dummy,r;
	cout<<"Enter the number of vertices"<<endl;
	cin>>m_vertices;
	 int rot_sys[m_vertices][m_vertices-1];
	int min[m_vertices][m_vertices-1];
	int new_clock[m_vertices][m_vertices-1];
	int new_counterclock[m_vertices][m_vertices-1];
	
	int v[m_vertices],p[m_vertices], v_anti[m_vertices];
	bool flag = false;
	bool changemin = false;
	
	
	
	// collecting the rotation sysytem
	cout<<"Enter the rotation system"<<endl;
	for(i=0; i< m_vertices; i++)
	  {
		  
		for(j=0; j<m_vertices-1; j++)
		  {
			cin>>rot_sys[i][j];
			min[i][j]=rot_sys[i][j];  //copiying the given rotation system as the mininum matrix.
		  }
			
   	}
	
	
		
	
	
	
	// generating all possible relabeling of the vertices
	for (v[0] =1; v[0] < m_vertices+1; v[0]++) // for choosing v1 and v2 for finding the finger print.
	{   v_anti[0]=v[0];
        p[v[0]-1] =1;
		for(int j=0;j<m_vertices-1;j++)
		{ 
			v[1] =rot_sys[v[0]-1][j];
			p[v[1]-1]=2;
			v_anti[1]= v[1];
			
			
			dummy = search_in_array( rot_sys[v[0]-1],v[1],m_vertices-1);
			
			for(k=1; k<m_vertices-1;k++)
			{
				v[k+1] = rot_sys[v[0]-1][(dummy+k)%(m_vertices-1)];
				p[v[k+1]-1]=k+2;
				
				
				
			}
			
				for(k=1; k<m_vertices-1;k++)
			{
				v_anti[k+1] = rot_sys[v[0]-1][(m_vertices-1 +dummy-k)%(m_vertices-1)];
			
			
			}
			
			
			
			
			for(i=0;i<m_vertices-1;i++) // the first row of the matrix will be always same.
			{
				new_clock[0][i]=i+2;
			    new_counterclock[0][i] =i+2;
				 
				
				if (min[0][i] >new_clock[0][i]) 
				{
					flag = true;
				}
			}
			
			 
			
		
			
			
			for(int h=1; h<m_vertices;h++) // finding the relabeled vertices and rotating them such that least element comes first.
			{
				 flag = false;
				dummy=search_in_array(rot_sys[v[h]-1],v[0],m_vertices-1); // looking for the clockwise direction
				for(i=0;i<m_vertices-1;i++)
				{
					 flag = false;
					new_clock[h][i] = 1+search_in_array(v, rot_sys[v[h]-1][(dummy+i)%(m_vertices-1)],m_vertices);
					
					
				}	
				
			
		}
			
		
		
			for(int h=1; h<m_vertices;h++)// looking for the counter clockwise direction.
			{
				dummy=search_in_array(rot_sys[v_anti[h]-1],v[0],m_vertices-1);
				for(i=0;i<m_vertices-1;i++)
				{
				
					new_counterclock[h][i] = 1+search_in_array(v_anti, rot_sys[v_anti[h]-1][(m_vertices-1+dummy-i)%(m_vertices-1)],m_vertices);
				}
			}
			
		
			cout<<"printing the new clockwise matrix for v_1 = "<<v[0]<<" and v_2= "<<v[1]<<endl;
			for(i=0;i<m_vertices;i++)
			{
				for(l=0;l<m_vertices-1;l++)
				{
					cout<<new_clock[i][l]<<" ";
				}
				cout<<endl;
			}
			 cout<<endl;
			 
			 
			 cout<<"printing the new counterclockwise for v_1= "<<v[0]<<" and v_2= "<<v[1]<<endl;
			for(i=0;i<m_vertices;i++)
			{
				for(l=0;l<m_vertices-1;l++)
				{
					cout<<new_counterclock[i][l]<<" ";
				}
				cout<<endl;
			}
			
	      cout<<endl;
		
			
		}
	}
	
	
	

   //TODO calling function of lexicomin.
  

	
}	