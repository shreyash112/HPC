
#include<bits/stdc++.h>

//#include<vectors>
using namespace std;
# define infi 0x3f3f3f3 ///total line in the text file
//int num_size = size_of_file * 3;
typedef pair<int, float> v_w;
//e functions
//starts
void readinput();
void input_matrix(string l1[]);
#define numbers 317080
#define maxints 1049866 * 2  //for the maximum number of elements to be read from the text file
ifstream inf;

//initializing global variable which are used in between functions
int count1 =0;
int j = 0;
int x;
int v1[maxints];
int v2[maxints];
int u;
int l1[maxints];
int count2;
int count_1[numbers];
int count_num;
//int count[numbers];
vector<vector<int>> adj(numbers);
//Read the inputs from the file
void readinput()
{
  inf.open("dblp-co-authors.txt");
  
  if (inf.fail())
  {
    cerr << "Error: Could not open input file\n";
    exit(1);
  }
  while (count1 < maxints)
  {
    try
    {
        inf >> x;
    }
    catch (std::ifstream::failure e)
    {
        break;
    }
    l1[count1++] = x;
  }
//  count2 = count1;
inf.close(); //Close the file at the end of your program.
}

void input_matrix(int l1[])
{
	for(int i = 0; i < maxints ; i=i+2)
	{
		v1[j] = l1[i] ;
        	j++;
    	}
 	j =0;
	for(int i = 1;i < maxints; i=i+2)
	{
		v2[j] = l1[i];
		j++;
	}
}

void countFreq(int arr[])
{
	unordered_map<int,int> freq;
	int i;
	for(i = 0; i < maxints/2; i++)
	{
		freq[arr[i]]++;
	}
	int count_freq = 0;
	int res = -1;
	for(auto x: freq)
	{
		if(count_freq < x.second)
		{
			res = x.first;
			count_freq = x.second;
		}
	}
	cout << "Result "<< res << " " << count_freq <<endl;		
	//	cout << x.first << " " << x.second <<endl;
}
void addEdge(vector<vector<int>> adj,int u, int v)
{
	adj[u].push_back(v);
	adj[v].push_back(u);
}

void printAdj(vector<vector<int>> adj)
{
	for(int i=0;i<numbers;i++)
	{
		for(auto x: adj[i])
			count_1[i]++; 
}
} 

//Main starts
int main()
{
	int final_element;
//	final_element = maxints/2;
	
	readinput();
	input_matrix(l1);
	int i;
	for(i =0; i < j;i++)
	{
		addEdge(adj,v1[i],v2[i]);
	}
//	printAdj(adj);
//	printf("\nCount : %d\n",count_1[3336]);
	return 0;
}
