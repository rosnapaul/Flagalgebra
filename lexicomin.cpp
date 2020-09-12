#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>

using namespace std;



bool islexicomin (int min[][m_vertices], int new_mat[][], int m_vertices)
{
	for( int i=0; i< m_vertices; i++)
	  {
		for(int j=0; j<m_vertices-1; j++)
		  {
			  if ( new_mat[i][j] < min[i][j])
				  return true;
        	}
   	  }
	
	
	
	
	
	
}


int main()
{
	int m_verticesi,j,k,l,m;
	cout<<"Enter the number of vertices"<<endl;
	cin>>m_vertices;
	int min[m_vertices][m_vertices ], new_mat[m_vertices][m_vertices];
	int v[m_vertices];
	
	
	// collecting the rotation sysytem
	cout<<"Enter the rotation system"<<endl;
	for(i=0; i< m_vertices; i++)
	  {
		for(j=0; j<m_vertices-1; j++)
		  {
			cin>>new_mat[i][j];
        	}
   	}
	
	cout<<"Enter the minimun system"<<endl;
	for(i=0; i< m_vertices; i++)
	  {
		for(j=0; j<m_vertices-1; j++)
		  {
			cin>>min[i][j];
        	}
   	}
	
	if (islexicomin (min, new_mat, m_vertices))
	{
		cout<< " minimum has changed"<<endl;
	}
	
	else
		cout<<"mini remains same"<<endl;
		
}	