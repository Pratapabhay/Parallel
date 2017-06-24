
#include <iostream>
#include <list>

using namespace std;
 
class Graph
{
    int N;    
    list<int> *adj_list;    
    
public:
    Graph(int N);   
    void Insert_Edge(int v, int w);   
    void DFS(int src);
    void helper(int v, bool visited[]);     
};
 
Graph::Graph(int N)
{
    this->N = N;
    adj_list = new list<int>[N];
}
 
void Graph::Insert_Edge(int v, int w)
{
    adj_list[v].push_back(w); 
}


void Graph::helper(int v, bool visited[])
{
    
    visited[v] = true;
    cout << v << " ";
 
    list<int>::iterator i;
    

    //#pragma omp critical

    for(i = adj_list[v].begin(); i != adj_list[v].end(); ++i)
       
        if(!visited[*i])
            helper(*i, visited);
}
 
void Graph::DFS(int src)
{
    bool *visited = new bool[N];
    
    
    
    #pragma omp parallel
	{
	#pragma omp for
  		for (int i = 0; i < N; i++)
		visited[i] = false;
	
	
	#pragma omp single
	helper(src, visited);
    
    
   

    //cout<<"Nodes not reachable from src : \n";
    
    
   	#pragma omp for
  		for (int i = 0; i < N; i++)
		     if(visited[i] = false) helper(i, visited);
		     
 	}

}
 
int main()
{


	

    int n,i,sr,vi,vj,no_of_edges;
    cout<<"Enter number of vertices:";
   

    cin>>n;
    Graph gr(n);

       
    cout<<"Enter number of edges:";
    cin>>no_of_edges;

        if(no_of_edges > n*(n-1)) {cout<<"Can't Have that many edges!! Exiting...\n"; return 0;}
        
        for(i=0;i<no_of_edges;i++)
        {
            cout<<"Enter an edge(u,v)(u,v should be in the range (0 - N-1):";
            cin>>vi>>vj;
        if((vi<0 || vi>n-1) || (vj<0 || vj>n-1)){cout<<"Can't Accept that edge. Exiting...\n"; return 0;}
    
            gr.Insert_Edge(vi,vj);
        }
    
    cout<<"Enter the Source: ";
    cin>>sr;
    cout << "DFS_recrsion Traversal: \t";
  
  
    
    clock_t tstart = clock();
    //cout<<tstart;
    gr.DFS(sr);
    cout<<"Time Taken: "<<double(clock()-tstart)/CLOCKS_PER_SEC;
    cout<<endl;
 
    return 0;
}
