// TODO: if you are given with a matrix. take each row and then find the element wich is the smallest aong all the elements of the row. now rotate the elements in the row either in clockwise or counter clockwise such
// that the smallest element comes first in the row.

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>
using namespace std;

//first trying to rotate an array.

void rotating_array (int *&arr, int mini_position, int m_vertices)
{
	int r, rotate_copy[m_vertices-1];
	 for(int i=0; i<m_vertices-1;i++)
  {
	r= (mini_position + i) % (m_vertices-1);

	  rotate_copy[i] = arr[r];
	
  }
  
   delete[] arr;
   for(int i=0; i<m_vertices-1;i++)
	{
		arr[i]=rotate_copy[i];
	}
   
}

int main()

{
	int r, mini_position, m_vertices;
	int *arr = new int[m_vertices];
	cout<<"Enter the number of vertices"<<endl;
	cin>>m_vertices;
	cout<<" Enter the elements of the array"<<endl;
	for(int i=0; i<m_vertices-1;i++)
	{
		cin>>arr[i];
	}

   cout<<"Enter a position	"<<endl;
   cin>>mini_position;

  rotating_array(arr, mini_position,m_vertices);
	
	cout<<" The rotated array is:"<<endl;
	for(int i=0;i<m_vertices-1;i++)
		{
			cout<<arr[i];
    	}

cout<<endl;
	}		