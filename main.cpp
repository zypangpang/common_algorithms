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
const int MAXINT=numeric_limits<int>::max();
struct Edge{
	int u,v,cap,flow;
};
ostream& operator<<(ostream& out, Edge const& e){
	cout<<"("<<e.u<<","<<e.v<<","<<e.cap<<","<<e.flow<<")";
	return out;
}
vector<Edge> edges;
vector<vector<int>> G;
vector<int> a;
vector<int> p;
void addEdge(int u,int v,int c){
	edges.push_back(Edge{u,v,c,0});
	edges.push_back(Edge{v,u,0,0});
	G[u].push_back(edges.size()-2);
	G[v].push_back(edges.size()-1);
}
int maxFlow(int s,int t){
	int flow=0;
	while(1){
		fill(a.begin(),a.end(),0);
		a[s]=MAXINT;
		queue<int> Q;
		Q.push(s);
		while(!Q.empty()){
			auto u=Q.front();Q.pop();
			for(auto eid: G[u]){
				auto const& e=edges[eid];
				if(a[e.v]==0&&e.cap>e.flow){
					Q.push(e.v);
					a[e.v]=min(a[u],e.cap-e.flow);
					p[e.v]=eid;
				}
			}
			if(a[t]) break;
		}
		if(a[t]==0) break;
		for(int v=t;v!=s;v=edges[p[v]].u){
			edges[p[v]].flow+=a[t];
			edges[p[v]^1].flow-=a[t];
		}
		flow+=a[t];
	}
	return flow;
}
void readGraph(){
	int n,m;
	cin>>n>>m;
	G.resize(n);a.resize(n);p.resize(n);
	for(int i=0;i<m;++i){
		int a,b,c;
		cin>>a>>b>>c;
		addEdge(a,b,c);
	}
}
int main()
{
	freopen("input.txt","r",stdin);
	readGraph();
	cout<<maxFlow(0,5)<<endl;
	printVec(edges);
    return 0;
}
