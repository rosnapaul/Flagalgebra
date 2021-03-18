#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;

void islexicomin(int **min, int m_vertices, int mini_position)
{
	int r, rotate_copy[m_vertices][m_vertices-1];
	
	for(int i=0; i< m_vertices; i++) 
	{
		for(int j=0; j<m_vertices-1; j++) 
		{
			r= (mini_position + j) % (m_vertices-1);

	  rotate_copy[i][j] = min[i][r];
	 
				
			
		}
		cout<<endl;
	}
	
	for(int i=0;i<m_vertices;i++)
	{
		for(int j=0;j<m_vertices-1;j++)
		{
			min[i][j] =rotate_copy[i][j];
			
		}
	
	}
}

int main() {
	int m_vertices,i,j,k,l,m;
	cout<<"Enter the number of vertices: ";
	cin>>m_vertices;
	int **min = new int*[m_vertices];
	for(i=0;i<m_vertices; i++)
	{
		min[i] = new int [m_vertices-1];
	}
	
	
		
	// collecting the rotation sysytem
	cout<<"Enter the rotation system: "<<endl;
	for(i=0; i< m_vertices; i++) {
		for(j=0; j<m_vertices-1; j++) {
			cin>>min[i][j];
        }
   	}
	
	
	islexicomin(min, m_vertices,2);
	
	
	return 0;
}	