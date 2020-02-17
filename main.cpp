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
struct Comp{
	bool operator()(Edge const& e1,Edge const& e2) const {
		return e1.dist>e2.dist;
	}
};
ostream& operator<<(ostream& out,Edge const& e){
	out<<"("<<e.u<<","<<e.v<<","<<e.dist<<")";
	return out;
}
priority_queue<Edge,vector<Edge>,Comp> Q;
vector<int> fa;
int findFather(int p){
	if(fa[p]==p) return p;
	return fa[p]=findFather(fa[p]);
}
void myUnion(int p,int q){
	int u=findFather(p);
	int v=findFather(q);
	fa[v]=u;
}
int m,n;
void readGraph(){
	cin>>m>>n;
	fa.resize(m);
	for(int i=0;i<m;++i){
		fa[i]=i;
	}
	for(int i=0;i<n;++i){
		int u,v,d;
		cin>>u>>v>>d;
		Q.push(Edge{u,v,d});
	}
}
vector<Edge> MST(){
	vector<Edge> mst;
	while(!Q.empty()){
	auto e=Q.top();Q.pop();
	if(findFather(e.u)!=findFather(e.v)){
		mst.push_back(move(e));
		myUnion(e.u,e.v);
	}
	}
	if(mst.size()==m-1) return mst;
	else return vector<Edge>();
}
const int MAXINT=numeric_limits<int>::max();
int main()
{

	freopen("input.txt","r",stdin);
	readGraph();
	auto mst=MST();
	printVec(mst);
	return 0;
}
