/*
Authors: Christian Havranek, Christopher Tran, Cole Watson
Project: Project 2 (BFS and IDS with permutation)
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> getInput ();

struct Node
{
    vector<int> Perm;
    int parent;
    
    Node()
    {
        vector<int> Perm;
        parent = -1;
    }
};

int main()
{
  vector<int> i = getInput();
  for(int i = 0; i < permutation.size(); i++)
    {
      cout << permutation[i] << " ";
    }
  cout << endl;
	
  return 0;
}

vector<int> getInput()
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
/*
  // just to make sure the vector is correct
  for(int i = 0; i < permutation.size(); i++)
    {
      cout << permutation[i] << " ";
    }
  cout << endl;*/
  return permutation;
}
