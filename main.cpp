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
struct Node{
	int u,d;
};
vector<vector<Node>> G;
vector<int> d;
vector<int> p;
vector<bool> inque;
vector<int> cnt;
void readGraph(){
	int m,n;
	cin>>m>>n;
	G.resize(m);
	d.resize(m,MAXINT);
	p.resize(m);
	cnt.resize(m);
	inque.resize(m);
	for(int i=0;i<n;++i){
		int u,v,d;
		cin>>u>>v>>d;
		G[u].push_back(Node{v,d});
	}
}
bool SPFA(int u){
	queue<int> q;
	q.push(u);
	inque[u]=1;
	d[u]=0;
	p[u]=-1;
	int n=G.size();
	while(!q.empty()){
		auto u=q.front();q.pop();
		inque[u]=0;
		for(auto const& node: G[u]){
			auto v=node.u;
			auto dist=node.d;
			if(d[u]<MAXINT && d[u]+dist<d[v]){
				d[v]=dist+d[u];
				p[v]=u;
				if(!inque[v]){
					q.push(v);
					inque[v]=1;
					if(++cnt[v]>n) return false;
				}
			}
		}
	}
	return true;
}
class Solution {

/*struct Edge{
	int u,v;
	int dist;
};*/


public:
    int networkDelayTime(vector<vector<int>>& times, int N, int K) {
		G.resize(N);d.resize(N,MAXINT);
		for(auto triple: times){
			auto u=triple[0]-1;
			auto v=triple[1]-1;
			auto d=triple[2];
			//edges.push_back(Edge{u,v,d});
			//G[u].push_back(edges.size()-1);
			G[u].push_back(Node{v,d});
		}
		//return SPFA(K-1);
    }
};
int main()
{
	freopen("input.txt","r",stdin);
	readGraph();
	SPFA(0);
	printVec(d);
	cout<<endl;
	printVec(p);
	return 0;
}
