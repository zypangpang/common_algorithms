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

struct Edge{
	int u,v;
	int dist;
};
vector<vector<int>> G;
vector<int> vis;
vector<int> topo;
int t;
int m,n;
vector<int> degree;
queue<int> Q;
void readGraph(){
	cin>>m>>n;
	t=m;
	G.resize(m);
	vis.resize(m);
	topo.resize(m);
	degree.resize(m);
	for(int i=0;i<n;++i){
		int u,v,d;
		cin>>u>>v>>d;
		G[u-1].push_back(v-1);
		++degree[v-1];
	}
}
bool topoSortDegree(){
	topo.clear();
	for(int i=0;i<m;++i){
		if(degree[i]==0) Q.push(i);
	}
	while(!Q.empty()){
		auto u=Q.front();Q.pop();
		topo.push_back(u);
		for(auto v: G[u]){
			if(--degree[v]==0) Q.push(v);
		}
	}
	if(topo.size()<m) return false;
	return true;
}
bool _topoSortDFS(int u){
	vis[u]=-1;
	for(auto v: G[u]){
		if(vis[v]==-1) return false;
		if(vis[v]==0 && !_topoSortDFS(v)) return false;
	}
	vis[u]=1;
	topo[--t]=u;
	return true;
}
bool topoSortDFS(){
	for(int i=0;i<m;++i){
		if(vis[i]) continue;
		if(!_topoSortDFS(i)) return false;
	 }
	return true;
}
const int MAXINT=numeric_limits<int>::max();

int main()
{
	freopen("input.txt","r",stdin);
	readGraph();
	if(topoSortDFS()) printVec(topo);
	else cout<<"Loop"<<endl;
	return 0;
}
