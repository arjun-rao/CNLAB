//Dijkstra's Algorithm

#include<iostream>
#include <cstdlib>
#include <climits>

using namespace std;



class Graph{

	
	 int vertex;
	 int **a;
	public:
		Graph(int ver){
			vertex=ver;
			a=new int*[ver];
			for(int i=0;i<ver;i++){
				a[i]=new int[ver];
				for(int j=0;j<ver;j++)a[i][j] = 0;
			}
			
		}
	 
		void inEdge(int x,int y)
		{
			a[x][y] = 1;
			a[y][x] = 1;
			
		}
		void input(){
			for(int i=0;i<vertex;i++){
				for(int j=0;j<vertex;j++){
					cin>>a[i][j];
				}
			}
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
		}
	        friend void dijkstra(Graph &G,int src);
};

int minVertex(int dist[],bool visited[],int V)
{
	int min_index,min= INT_MAX;
	for(int i=0;i<V;i++)
	{
		if(visited[i]==false && dist[i] < min)
		{
			min = dist[i];
			min_index=i;
		}	
	}
	return min_index;
}


void dijkstra(Graph &G, int src)
{
	int V = G.vertex;
	bool *visited = new bool[V];
	int *dist= new int [V];


	//make all nodes as unvisited, and distance from source as INFINTY
	for(int i=0;i<V;i++){
		dist[i] = INT_MAX;
		visited[i]= false;
	}

	//initialise distance of source to source as 0;
	dist[src]=0;

	//we will need to consider n vertices
	for(int i = 0; i<V-1;i++)
	{
		//pick u such that visited[u] is false and distance[u] is minimum
		int u = minVertex(dist,visited,V);

		//mark u as visited
		visited[u] = true;

		//for each edge (u,v) if v is unvisited, and distance needs updating, update
		
		for(int v=0;v<V;v++)
		{
			if(!visited[v] && G.a[u][v] && dist[u]!=INT_MAX && dist[v] > dist[u]+G.a[u][v])
				dist[v] = dist[u]+G.a[u][v];
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
	dijkstra(G,n);
	cout<<endl;
 
}