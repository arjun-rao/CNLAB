// Bellman Ford Algorithm

#include<iostream>
#include <cstdlib>
#include <climits>

using namespace std;



class Graph{

	
	 int vertex,E;
	 int **a,**edge;
	public:
		Graph(int ver){
			vertex=ver;
			a=new int*[ver];
			for(int i=0;i<ver;i++){
				a[i]=new int[ver];
				for(int j=0;j<ver;j++)a[i][j] = 0;
			}
			edge=new int*[ver*ver];
			for(int i=0;i<ver*ver;i++){
				edge[i]=new int[2];				
			}
			
		}
	 
		
		void input(){
			int k = 0;
			for(int i=0;i<vertex;i++){
				for(int j=0;j<vertex;j++){
					cin>>a[i][j];
				if(a[i][j]!=0)
                	edge[k][0]=i,edge[k++][1]=j;
				}
			}
			E = k;
		}
		void display(){
			for(int i=0;i<vertex;i++){
				for(int j=0;j<vertex;j++){
					cout<<a[i][j]<<" ";
				}
				cout<<endl;
			}
		}
		~Graph()
		{
			
			for(int i=0;i<vertex;i++){
				delete [] a[i];
			}
			delete [] a;
			for(int i=0;i<vertex*vertex;i++){
				delete [] edge[i];
			}
			delete [] edge;
		}
	        friend void bford(Graph &G,int src);
};



void bford(Graph &G, int src)
{
	int V = G.vertex,E = G.E;

	int *dist= new int [V];


	//make all nodes as unvisited, and distance from source as INFINTY
	for(int i=0;i<V;i++){
		dist[i] = INT_MAX;		
	}

	//initialise distance of source to source as 0;
	dist[src]=0;

	//we will need to consider n vertices
	for(int i = 0; i<V-1;i++)
	{
		int u = i;					
		//for each edge (u,v), and update distance		
		for(int k=0;k<E;k++)
		{
			int u = G.edge[k][0], v = G.edge[k][1];
			if(dist[u]!=INT_MAX && dist[v] > dist[u]+G.a[u][v])
				dist[v] = dist[u]+G.a[u][v];
		}
	}
	
    
			
	//for each edge (u,v), check negative cycle		
	for(int k=0;k<E;k++)
	{
		int u = G.edge[k][0], v = G.edge[k][1];
		if(dist[u]!=INT_MAX &&  dist[v] > dist[u]+G.a[u][v])
		{
			cout<<"\nGraph contains a negative-weight cycle\n";
			return;
		}
			
	}


	//print the solution
	cout<<"\nSingle Source Shortest Paths:\nVertex- Distance from Source\n";
	for(int i=0;i<V;i++)
	{
		cout<<i<<"- "<<dist[i]<<endl;
	}

}


int main()
{

	int n;
	cout<<"Vertices:";
	cin>>n;
	Graph G(n);
	cout<<"Adjacency Matrix:\n";
	G.input();
	cout<<"Source:\n";
	cin>>n;
	bford(G,n);
	cout<<endl;
 
}