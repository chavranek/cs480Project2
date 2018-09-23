/*
Authors: Christian Havranek, Christopher Tran, Cole Watson
Project: Project 2 (BFS and IDS with permutation)
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void successors(vector<int> permutation, int size)
{
  for(int i = 2; i <= size; i++)
    {
      for(int j = 0; j + i <= size; j++)
        {
          vector<int> succ;
	  succ = permutation;
          reverse(succ.begin()+j, succ.begin()+j+i);
	  if (!equal(succ.begin(), succ.end(), permutation.begin()))
	    {
	      //push node into vector
	      //push node into queue
	    }
	  for(int m = 0; m < succ.size(); m++)
	    {
	      cout << succ[m] << " ";
	    }
          cout << endl;
	  
        }
    }
  
}

int main()
{
  int num = 0;
  string P;
  string number;
  vector<int> permutation;
  cout << "Input a permutation: " << endl;

  // grabs the entire line of user input
  getline(cin, P);

  // moves through the entire user input and
  // converts all characters to ints, then
  // pushes them onto a vector.
  for(int i = 0; i < P.length(); i++)
  {
      if (isdigit(P[i]))
    	{
    	  string snum(1, P[i]);
	  number += snum;
	}
      else if(P[i] == ' ')
	{
	  int num = stoi(number);
          permutation.push_back(num);
          number = "";

	}
      if(i == P.length()-1)
	{
	  int num = stoi(number);
          permutation.push_back(num);
	  number = "";
	}
    }
  
  // just to make sure the vector is correct
  /*for(int i = 0; i < permutation.size(); i++)
    {
      cout << permutation[i] << " ";
    }*/
  cout << endl;

  int size = permutation.size();

  successors(permutation, size);
    
}
