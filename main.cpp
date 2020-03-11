#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <chrono>
#include <array>
#include <cmath>
#include <stack>

using namespace std;

//Time Helper
struct ScopedTimer{
    chrono::high_resolution_clock::time_point start;
    ScopedTimer(){ start = chrono::high_resolution_clock::now(); }
    ~ScopedTimer(){
        auto stop = chrono::high_resolution_clock::now();
        auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
        cout<<"<duration "<<duration.count()<<" us>"<<endl;
    }
};
/*template <typename Functor, typename ... Args>
auto runningTime(Functor f, Args && ... args)
    -> decltype(f(std::forward<Args>(args)...))
{
    //return std::function<R(Args...)>(f);
    ScopedTimer timer;
    return f(forward<Args>(args)...);
}*/


//Print helper
template <typename T>
void printVec(vector<T> const& v){
	copy(v.begin(),v.end(),ostream_iterator<T>(cout," "));
}
class Solution {
	vector<int> tree;
	void buildTree(vector<int> const& h,int l,int r,int node){
        if(l>=r) return;
		if(l+1==r){
			tree[node]=l;
			return;
		}
		int mid=l+((r-l)>>1);
		buildTree(h,l,mid,node<<1);
		buildTree(h,mid,r,node<<1|1);
		tree[node]=h[tree[node<<1]]<=h[tree[node<<1|1]]?tree[node<<1]:tree[node<<1|1];
	}
	int getMinFast(vector<int> const& h,int l,int r,int node,int L,int R){
		if(L<=l&&R>=r) return tree[node];
		int resL=-1,resR=-1;
		int mid=l+((r-l)>>1);
		if(mid>L) resL=getMinFast(h,l,mid,node<<1,L,R);
		if(mid<R)  resR=getMinFast(h,mid,r,node<<1|1,L,R);
		if(resL!=-1&& resR!=-1) return h[resL]<=h[resR]? resL:resR;
		if(resL!=-1) return resL;
		return resR;
	}
	int getMin(vector<int> const& h, int l,int r){
		int minE=h[l];
		int minId=l;
		for(int i=l+1;i<r;++i)
		  if(h[i]<minE){
			  minE=h[i];
			  minId=i;
		  }
		return minId;
	}
	int _getArea(vector<int> const& h,int l,int r){
		if(l>=r) return 0;
		int minId=getMinFast(h,0,h.size(),1,l,r);
		int cur=h[minId]*(r-l);
		return max(cur,max(_getArea(h,l,minId),_getArea(h,minId+1,r)));
	}
	//Stack approach. Essentially, find left first smaller and right first smaller element.
	int getAreaStack(vector<int>& ht){
		stack<int> stk;
		vector<int> h;
		h.push_back(0);
		h.insert(h.end(),move(ht.begin()),move(ht.end()));
		h.push_back(0);
		int res=0;
		for(int i=0;i<h.size();++i){
			//Actually, > only guarantee the right first smaller one, the left is left first smaller or equal one.
			while(!stk.empty()&& h[stk.top()]>h[i]){
				int tmp=stk.top();stk.pop();
				res=max(res,(i-1-stk.top())*h[tmp]);
			}
			stk.push(i);
		}
		return res;
	}
public:
    int largestRectangleArea(vector<int>& heights) {
		if(heights.empty()) return 0;
		int n=heights.size();
		/*tree.resize(4*n);
		buildTree(heights,0,n,1);
		int res=0;
		res=_getArea(heights,0,n);*/
		int res=getAreaStack(heights);
		return res;
    }
};

int main()
{
    //Stdin redirect
    //freopen("input.txt","r",stdin);

    //istream_iterator<string> iit(cin),eit;
    //copy(iit,eit,back_inserter(testCases));
	
	//vector<int> heights{2,1,5,6,2,3};
	vector<int> heights {0,0,0,0,0,0,0,0,2147483647};
	Solution sol;
	auto x=sol.largestRectangleArea(heights);
	cout<<x<<endl;

    return 0;
}


