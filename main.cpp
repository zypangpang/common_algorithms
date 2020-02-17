#include <iterator>
#include <limits>
#include <iostream>
#include <vector>
#include <queue>
#include <array>
#include <algorithm>
#include <unordered_set>
#include <stack>
#include <unordered_map>

using namespace std;
template <typename T>
void printVec(vector<T> const& v){
	copy(v.begin(),v.end(),ostream_iterator<T>(cout," "));
}

/*void readGraph(){
	int m,n;
	cin>>m>>n;
	G.resize(m);
	d.resize(m,MAXINT);
	s.resize(m);
	p.resize(m);
	for(int i=0;i<n;++i){
		int u,v,d;
		cin>>u>>v>>d;
		edges.push_back(Edge{u,v,d});
		G[u].push_back(edges.size()-1);
	}
}*/
class Solution {

/*struct Edge{
	int u,v;
	int dist;
};*/

/*************** below are Dijkstra template codes ******************/
const int MAXINT=numeric_limits<int>::max();
struct Node{
	int u,d;
	bool operator<(Node const& rhs) const{
		return d>rhs.d; // > for min root heap
	}
};
//Do not forget to initialize these vectors with node numbers N
vector<vector<Node>> G;
vector<int> d; //Initialize as MAXINT
vector<bool> s; 
vector<int> p; // path: node id before
//vector<Edge> edges;

int dijkstra(int u){
	priority_queue<Node> q;
	d[u]=0;
	p[u]=-1;
	q.push(Node{u,0});
	while(!q.empty()){
		auto node=q.top();q.pop();
		auto u=node.u;
		if(s[u]) continue; //Important!
		s[u]=1;
		for(auto node:G[u]){
			auto v=node.u;
			auto dist=node.d;
			if(d[u]+dist<d[v]){ //Relax all
			  d[v]=d[u]+dist;
			  q.push(Node{v,d[v]});
			  p[v]=u;
			}
		}
	}
	int maxD=*max_element(d.begin(),d.end());
	return maxD<MAXINT?maxD:-1;
}
/*******************************************************************/

public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
		G.resize(N);d.resize(N,MAXINT);s.resize(N);
		for(auto triple: times){
			auto u=triple[0]-1;
			auto v=triple[1]-1;
			auto d=triple[2];
			//edges.push_back(Edge{u,v,d});
			//G[u].push_back(edges.size()-1);
			G[u].push_back(Node{v,d});
		}
		return dijkstra(K-1);
    }
};
int main()
{
	freopen("input.txt","r",stdin);
	/*readGraph();
	dijstra(0);
	printVec(d);
	cout<<endl;
	printVec(p);*/
	return 0;
}
