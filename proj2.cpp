/*
Authors: Christian Havranek, Christopher Tran, Cole Watson
Project: Project 2 (BFS and IDS with permutation)
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
  string P;
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
	  int num = stoi(snum);
	  permutation.push_back(num);
	}
    }

  // just to make sure the vector is correct
  for(int i = 0; i < permutation.size(); i++)
    {
      cout << permutation[i] << " ";
    }
  cout << endl;

    
}
