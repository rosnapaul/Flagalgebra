// TODO: if you are given with a matrix. take each row and then find the element wich is the smallest aong all the elements of the row. now rotate the elements in the row either in clockwise or counter clockwise such
// that the smallest element comes first in the row.

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;

typedef vector<int> row;
typedef vector < vector<int> > matrix;


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
	

void rotating_array (vector<vector<int> >& stuff, int m_vertices)
{
	int mini_position;
	
   int r, rotate_copy[m_vertices][m_vertices-1];
	
	for(int i=0; i< stuff.size();i++)
	{
		mini_position = lowestinarray( stuff[i]);
		for(int j=0; j<stuff[i].size();j++)
		{
			
			r= (mini_position + j) % (m_vertices-1);

	  rotate_copy[i][j] = stuff[i][r];
	 
				
			
		}
		cout<<endl;
	}
	
	for(int i=0;i<stuff.size();i++)
	{
		for(int j=0;j<stuff[i].size(); j++)
		{
		stuff[i][j]=rotate_copy[i][j];
			
		}
	
	}
}

int main()

{
	int r, m_vertices,i,j;
	cout<<"Enter the size"<< endl;
	cin>>m_vertices;
	matrix stuff;
	
	
	cout<<" Enter the elements of the array"<<endl;
	for(i=0; i< m_vertices; i++) {
		row temp;
		for(j=0; j<m_vertices-1; j++) {
			
			cin>>r;
			temp.push_back(r);
        }
		stuff.push_back(temp);
   	}

 

  rotating_array(stuff,m_vertices);
  for(i=0; i< stuff.size();i++){
		for(j=0; j<stuff[i].size();j++){
			cout<<stuff[i][j];
        }
		cout<<endl;
		
   	}
	
	
	
	}		