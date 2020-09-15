#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;

bool islexicomin(int **min,int **given_mat, int m_vertices) 
{
	for(int i=0; i< m_vertices; i++) 
	{
		for(int j=0; j<m_vertices-1; j++) 
		{
			if (given_mat[i][j] < min[i][j]) 
			{
				cout<<given_mat[i][j] <<"<"<<min[i][j]<<endl;
				
				return true;
				break;
			}
			 else if (given_mat[i][j] > min[i][j]) 
			{
				cout<<given_mat[i][j] <<">"<<min[i][j]<<endl;
				
				return false;
				break;
			}	
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
	
	int **given_mat= new int*[m_vertices];
	for(i=0;i<m_vertices;i++)
	{
		given_mat[i]= new int[m_vertices-1];
	}	
		
	// collecting the rotation sysytem
	cout<<"Enter the rotation system: "<<endl;
	for(i=0; i< m_vertices; i++) {
		for(j=0; j<m_vertices-1; j++) {
			cin>>given_mat[i][j];
        }
   	}
	// collecting the minimum system
	cout<<"Enter the minimum system: "<<endl;
	for(i=0; i<m_vertices; i++) {
		for(j=0; j<m_vertices-1; j++) {
			cin>>min[i][j];
        }
   	}
	
	if(islexicomin(min, given_mat, m_vertices)) {
		cout<<"minimum has changed"<<endl;
	}
	else {
		cout<<"minimum remains same"<<endl;
	}
	return 0;
}	