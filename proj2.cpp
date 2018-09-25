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

using namespace std;

int bfsVisited = 0;
int bfsMaxQueueSize = 0;
int idsVisited = 0;
int idsMaxStackSize = 0;


vector<int> getInput ();
void BFS (vector<int> Permutation, int size);
bool checkGoal (vector<int> Permutation, int size);
void IDS(vector<int>Permutation, int size);

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
void successors(vector<Node>&Pointers, stack<Node>&Stack, vector<int>permutation, int parent\, int size)
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

              childNode.parent = Pointers.size() -1;
              Stack.push(childNode);
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

    clock_t d;
    d = clock();
    IDS(permutation, size);
    d = clock() - d;

    cout << "IDS time in seconds:  " << fixed << setprecision(6) << (float(d))/CLOCKS_PER_SE\
C << endl;
    cout << "IDS total number of visited states: " << idsVisited << endl;
    cout << "IDS max queue size: " << idsMaxStackSize << endl;


    
    
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
    else if(P[i] == ' ')
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
  while(dfs = false)
    {
      dfs = DFS(Permutation, size, depth);
      if (dfs =false)
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
    Stack.push(initial);

    while(!Stack.empty())
    {
                cout << "Depth in function:" << depth << endl;
        Node currentNode = Stack.top();
        //cout << "current node parent: " << currentNode.parent << endl;
        Stack.pop();
        if (checkGoal(currentNode.Perm, size))
        {
            printOutput(Pointers, Pointers.size()-1);
            return true;
        }
        if(depth > 0)
        {
        successors(Pointers, Stack, currentNode.Perm, currentNode.parent, size);
        depth--;
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
    cout << "Solution from goal to start: " << endl;
    
    while (index != -1)
    {
      for (int i = 0; i < Pointers[index].Perm.size(); i++)
	{
	  cout << Pointers[index].Perm[i] << " ";
	}
      cout << endl;
      index = Pointers[index].parent;
    }
}
