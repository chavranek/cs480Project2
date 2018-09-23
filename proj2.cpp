/*
Authors: Christian Havranek, Christopher Tran, Cole Watson
Project: Project 2 (BFS and IDS with permutation)
 */

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> getInput ();
void BFS (vector<int> Permutation, int size);
bool checkGoal (vector<int> Permutation, int size);
void printOutput (vector<int> Pointers, int index);


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
    vector<int> permutation = getInput();
    int size = permutation.size();
    
    for(int i = 0; i < size; i++)
    {
      cout << permutation[i] << " ";
    }
    cout << endl;
    
    bool a = checkGoal(permutation, size);
    cout << "true or false: " << a << endl;
    
    BFS(permutation, size);
    
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
  int size = permutation.size();

  successors(permutation, size);
    }
  cout << endl;*/
  return permutation;
}

void BFS(vector<int> Permutation, int size)
{
    vector<Node> Pointers;
    queue<Node> Queue;
    
    Node initial;
    initial.parent = -1;
    for (int i = 0; i < size; i++)
        initial.Perm.push_back(Permutation[i]);
        
    Pointers.push_back(initial);
    Queue.push(initial);
    
        while(!Queue.empty())
    {
        Node currentNode = Queue.front();
        //cout << "current node parent: " << currentNode.parent << endl;
        Queue.pop();
        if (checkGoal(currentNode.Perm, size))
        {
            printOutput(Pointers, currentNode.parent);
            return;
        }
        
        //successor code goes here
            
    }
}

bool checkGoal(vector<int> Permutation, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (Permutation[i] > Permutation[i+1])
            return false;
    }
    for (int i = 0; i < size; i++)
        cout << Permutation[i] << ' ';
    return true;
}

void printOutput(vector<int> Pointers, int index)
{
    while (index != -1)
    {
        cout << Pointers[index].Perm << endl;
        index = Pointers[index].parent;
    }
}
