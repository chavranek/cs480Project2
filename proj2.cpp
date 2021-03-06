/*
Authors: Christian Havranek, Christopher Tran, Cole Watson
Project: Project 2 (BFS and IDS with permutation)
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <queue>
#include <time.h>
#include <iomanip>
#include <stack>

using namespace std;

int bfsVisited = 0;
int bfsMaxQueueSize = 0;
int idsVisited = 0;
int idsMaxStackSize = 0;


vector<int> getInput ();
void BFS (vector<int> Permutation, int size);
bool checkGoal (vector<int> Permutation, int size);
void IDS(vector<int>Permutation, int size);
bool DFS(vector<int> Permutation, int size, int depth);

struct Node
{
  vector<int> Perm;
  int parent;
  int depth;
  
  
  Node()
  {
    vector<int> Perm;
    parent = -1;
    int depth = 0;
  }
};

void printOutput (vector<Node> Pointers, int index);

void successors(vector<Node>&Pointers, queue<Node>&Queue, vector<int>permutation, int parent, int size)
{
  
  for(int i = 2; i <= size; i++)
    {
      for(int j = 0; j + i <= size; j++)
        {
	  vector<int> cycle;
          vector<int> succ;
	  succ = permutation;
          reverse(succ.begin()+j, succ.begin()+j+i);
	  cycle = Pointers[parent].Perm;
	  if (!equal(succ.begin(), succ.end(), cycle.begin()))
	    {
	      Node childNode;
	      childNode.Perm = succ;
	      childNode.parent = parent;
	      Pointers.push_back(childNode);

	      childNode.parent = Pointers.size() - 1;
	      Queue.push(childNode);
	      bfsVisited++;
	      if (Queue.size() > bfsMaxQueueSize)
	        bfsMaxQueueSize = Queue.size();
	    }
	}
    }
}

//used for DFS
void successors(vector<Node>&Pointers, stack<Node>&Stack, vector<int>permutation, int parent, int size, int depth)
{
  for(int i = 2; i <= size; i++)
    {
      for(int j = 0; j + i <= size; j++)
        {
          vector<int> cycle;
          vector<int> succ;
          succ = permutation;
          reverse(succ.begin()+j, succ.begin()+j+i);
          cycle = Pointers[parent].Perm;
          if (!equal(succ.begin(), succ.end(), cycle.begin()))
            {
              Node childNode;
              childNode.Perm = succ;
              childNode.parent = parent;
	      childNode.depth = depth + 1;
              Pointers.push_back(childNode);

              childNode.parent = Pointers.size() - 1;
	      //childNode.depth = depth + 1;
              Stack.push(childNode);
	      idsVisited++;
              if (Stack.size() > idsMaxStackSize)
		{
		  idsMaxStackSize = Stack.size();
		}
            }
        }
   }
}


int main()
{
    vector<int> permutation = getInput();
    int size = permutation.size();
    
    clock_t t;
    t = clock();
    BFS(permutation, size);
    t = clock() - t;

    cout << "BFS time in seconds:  " << fixed << setprecision(6) << (float(t))/CLOCKS_PER_SEC << endl;
    cout << "BFS total number of visited states: " << bfsVisited << endl;
    cout << "BFS max queue size: " << bfsMaxQueueSize << endl;

    cout << "\n" << endl;

    clock_t d;
    d = clock();
    IDS(permutation, size);
    d = clock() - d;

    cout << "IDS time in seconds:  " << fixed << setprecision(6) << (float(d))/CLOCKS_PER_SE\
C << endl;
    cout << "IDS total number of visited states: " << idsVisited << endl;
    cout << "IDS max stack size: " << idsMaxStackSize << endl;


    
    
    return 0;
}

vector<int> getInput()
{
  int num = 0;
  string P;
  string number;
  vector<int> permutation;
  cout << "Input a permutation with a bracket at the beginning, commas " << endl;
  cout << "between each number, and a closing bracket at the end of" << endl;
  cout << "your permutation. Follow the format of the example below:" << endl;
  cout << "[1,2,3,4,5,6,7,8,9]" << endl;

  // grabs the entire line of user input
  getline(cin, P);
  cout << endl;

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
    else if(P[i] == ' ' || P[i] == ',')
      {
	if (i != P.length()-1)
	  {
	    if (!number.empty())
	      {
		int num = stoi(number);
		permutation.push_back(num);
		number = "";
	      }
	  }
      }
    if(i == P.length()-1)
      {
        int num = stoi(number);
        permutation.push_back(num);
        number = "";
      }

  }
  
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
    initial.parent = Pointers.size()-1;
    Queue.push(initial);
    bfsVisited++;
    bfsMaxQueueSize = Queue.size();
    
    while(!Queue.empty())
    {
        Node currentNode = Queue.front();
	Queue.pop();
        if (checkGoal(currentNode.Perm, size))
        {
	  cout << "Answer for BFS:" << endl;
            printOutput(Pointers, currentNode.parent);
            return;
        }
        
        successors(Pointers, Queue, currentNode.Perm, currentNode.parent, size);
    }
    return;
}

void IDS(vector<int> Permutation, int size)
{
  int depth = 0;
  bool dfs = false;
  while(dfs == false)
    {
      dfs = DFS(Permutation, size, depth);
      if (dfs == false)
	{
	  depth++;
	}
    }
}
  
bool DFS(vector<int> Permutation, int size, int depth)
{
  vector<Node> Pointers;
  stack<Node> Stack;

    Node initial;
    initial.parent = -1;
    for (int i = 0; i < size; i++)
        initial.Perm.push_back(Permutation[i]);

    Pointers.push_back(initial);
    initial.parent = Pointers.size()-1;
    initial.depth = 0;
    Stack.push(initial);
    idsVisited++;
    idsMaxStackSize = Stack.size();

    while(!Stack.empty())
    {
        Node currentNode = Stack.top();
        Stack.pop();
        if (checkGoal(currentNode.Perm, size))
        {
	  cout << "Answer for IDS:" << endl;
	  printOutput(Pointers, currentNode.parent);
	  return true;
        }
	if (currentNode.depth == depth && Stack.size() ==0)
	  {
	    //cout << "depth: " << depth << endl;
	    return false;
	  }

	if(currentNode.depth < depth)
	  {
	    successors(Pointers, Stack, currentNode.Perm, currentNode.parent, size, currentNode.depth);
	  }
    }
    return false;

}


bool checkGoal(vector<int> Permutation, int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        if (Permutation[i] > Permutation[i+1])
            return false;
    }
    return true;
}

void printOutput(vector<Node> Pointers, int index)
{
  vector< vector < int> > moves;

    int moveNum = 1;
    while (index != -1)
    {
      moves.push_back(Pointers[index].Perm);
      index = Pointers[index].parent;
    }
    
    reverse(moves.begin(), moves.end());
    cout << "The number of moves = " << moves.size()-1 << endl;
    for(int i = 1; i < moves.size(); i++)
      {
	cout << "Move " << moveNum << ": " << "[";
	for(int j = 0; j < moves[i].size(); j++)
	  {
	    if(j < (moves[i].size()-1))
	      {
		cout << moves[i][j] << ",";
	      }
	    else
	      {
		cout << moves[i][j] << "]";
	      }
	  }
	moveNum++;
	cout << endl;
      }
}
