#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main()
{
  string P;
  vector<int> permutation;
  cout << "Input a permutation: " << endl;

  getline(cin, P);
  
  for(int i = 0; i < P.length(); i++)
    {
      if (isdigit(P[i]))
	{
	  string snum(1, P[i]);
	  int num = stoi(snum);
	  permutation.push_back(num);
	}
    }
  
  for(int i = 0; i < permutation.size(); i++)
    {
      cout << permutation[i] << " ";
    }
  cout << endl;

    
}
