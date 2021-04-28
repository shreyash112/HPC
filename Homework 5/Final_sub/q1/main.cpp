//Author: Shreyash
//MPI Program to calculate the maximum number of co-authors
//Run srun --pty --export=ALL --partition=short --nodes=1 --tasks-per-node=4 mpirun --mca btl_base_warn_component_unused 0 main 1 to run 1.a 
//Or Run srun --pty --export=ALL --partition=short --nodes=1 --tasks-per-node=4 mpirun --mca btl_base_warn_component_unused 0 main 0 to run 1.b
#include<bits/stdc++.h>
#include<mpi.h>
using namespace std;
void readinput();
#define numbers 317080
#define maxints 2099732 //for the maximum number of elements to be read from the text file

//initializing global variable which are used in between functions
int count1 =0;
int j = 0;
int x;
int u;
int l1[maxints]={0};
int count2;
int count_1[numbers];
vector<int>adj[numbers];

//Read the inputs from the file
void readinput()
{
  ifstream inf;
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
  inf.close(); //Close the file at the end of your program.
}

void addEdge(vector<int> adj[],int u,int v)
{
	adj[u-1].push_back(v-1);
	adj[v-1].push_back(u-1);
}

void make_adj()
{		
	int i;
	for(i =0; i < maxints;i=i+2)
	{	
		addEdge(adj,l1[i],l1[i+1]);
	}
}

//Main starts
int main(int argc, char** argv)
{
  int  x, y;
	int num;
  int problem = atoi(argv[1]);
  vector<int> number;
  //For Calculating the Author with maximum co-authors
  if(problem)
  {
    priority_queue<pair<long ,long> > temp;
    priority_queue<pair<long ,long> > final;
	  MPI_Init(NULL,NULL);
	  int rank, comm_size;
	  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    long divide = numbers/comm_size; //Divide the numbers among the processes
    if(rank == 0)
    {
      readinput();
    }
    MPI_Bcast(&l1[0], maxints, MPI_INT, 0, MPI_COMM_WORLD);
    make_adj();
    long num = 0;
    for(long i = rank*divide; num<divide; i++)
    {
        int size = adj[i].size();
        temp.push(make_pair(size, i+1));
        num++;
    }
    
    vector<long> local_vec;
    pair<long, long> top = temp.top();
    long local_best = top.first;
    cout<<"Rank :"<<rank<<": Number of Co-author: "<<top.first<< " Author Number :"<< top.second<<endl;
    //int waste = 0;
    while(!temp.empty())
    {
      local_vec.push_back(top.first);
      local_vec.push_back(top.second);
      temp.pop();
      top = temp.top();
      if(top.first != local_best)
        break;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    int *counts = new int[comm_size];
    int nelements = (int)local_vec.size();
    // Each process tells the root how many elements it holds
    MPI_Gather(&nelements, 1, MPI_INT, counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    int *displacement = new int[comm_size];
    for (int i = 0; i < comm_size; i++)
    {
      if(i > 0)
      {
        displacement[i] = displacement[i-1] + counts[i-1];  
      }
      else
      {
        displacement[i] = 0;
      }
    }   
    
    long* final_vec = NULL;
    long total = displacement[comm_size-1] + counts[comm_size-1];
    if(rank == 0)
    {
        final_vec = new long [total];
    }
   
    MPI_Gatherv(&local_vec[0], nelements, MPI_LONG, final_vec, counts, displacement, MPI_LONG, 0, MPI_COMM_WORLD);

    if(rank == 0)
    {
        for(int i=0; i<total; i=i+2)
            final.push(make_pair(final_vec[i], final_vec[i+1]));

        pair<long, long> top_final = final.top();
        
        int best = top_final.first;
        //cout<<"The maximum number of co-authors is = "<<best<<endl;
        cout<<"Author with maximum co-authors is: ";
        while(!final.empty())
        {
            cout<<top_final.second<<" with total number = "<< best<<endl;
            final.pop();
            top_final = final.top();
            if(top_final.first != best)
                break;
        }
    }
    MPI_Finalize();
    }
    
  //For plotting the histogram 
  else
  {
    MPI_Init(NULL,NULL);
	  int rank, comm_size;
	  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	  MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
    long divide = numbers/comm_size;
    //Read the text file from the head node
    if(rank == 0)
    {
      readinput();
    }
    //Broadcast the array to all the nodes 
    MPI_Bcast(&l1[0], maxints, MPI_INT, 0, MPI_COMM_WORLD);
    // Each Node will make the adjacency list 
    make_adj();
    long num = 0;
    //Divide the Authors among the each participating nodes
    for(long i = rank*divide; num<divide; i++)
    {
        int length = adj[i].size();    //number of co-authors
        number.push_back(length);
        num++;
    }
    MPI_Barrier(MPI_COMM_WORLD);

    int *counts = new int[comm_size];
    //Send the size of the vector 
    int nelements = (int)number.size();
    MPI_Gather(&nelements, 1, MPI_INT, counts, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    //Calculate the displacement 
    int *displacement = new int[comm_size];
    for (int i = 0; i < comm_size; i++)
    {
      if(i > 0)
      {
        displacement[i] = displacement[i-1] + counts[i-1];  
      }
      else
      {
        displacement[i] = 0;
      }
    }   
    
    int* final_list = NULL;
    int total = displacement[comm_size-1] + counts[comm_size-1];
    if(rank == 0)
    {
        final_list = new int [total];
    }
    
    //Gatherv is used to gather the elements from the vector
    MPI_Gatherv(&number[0], nelements, MPI_INT, final_list, counts, displacement, MPI_INT, 0, MPI_COMM_WORLD);
    //On the head node the counts and frequency are written in the text file
    if(rank == 0)
    {
        ofstream out;
        out.open("plotting_coordinate.txt");
        int count = 0, curr, prev;
        sort(final_list, final_list + total);
        prev = final_list[0];
        for(int i=0; i<total; i++)
        {
            curr = final_list[i];
            if(prev != curr)
            {
                out<<prev<<" "<<count<<endl;
                count = 0;
            }
            count++;
            prev = curr;
        }
        out<<prev<<" "<<count<<endl;
    }
    MPI_Finalize();
    }

	return 0;
}
