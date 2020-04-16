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
#include <queue>

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
	vector<vector<bool>> p;
	void prepare(string s) {
		int n=s.size();
		p=vector<vector<bool>>(n,vector<bool>(n));
		for(int i=0;i<n;++i) {
			p[i][i]=true;
		}
		for(int i=0;i<n-1;++i)
		  if(s[i]==s[i+1]){
			p[i][i+1]=true;
		  }
		for(int i=n-3;i>=0;--i){
			for(int j=i+2;j<n;++j){
				p[i][j]=p[i+1][j-1]&&s[i]==s[j];
			}
		}
		/*for(auto& v: p){
			printVec(v);
			cout<<endl;
		}*/
    }
	bool isPalindrome(string s){
		int p=0,q=s.size()-1;
		while(p<q){
			if(s[p]!=s[q]) return false;
			++p;--q;
		}
		return true;
	}
	unordered_map<string,vector<vector<string>>> vmap;
	vector<vector<string>> _partition(string& oriS,int b,int e) {
		if(e-b<1) return vector<vector<string>>(1);
		string s=oriS.substr(b,e-b);
		if(vmap.count(s)) return vmap[s];
		vector<vector<string>> ans;
		for(int i=0;i<s.size();++i){
			auto right=s.substr(i);
			if(p[b+i][e-1]){
				auto subPars=_partition(s,b,b+i);
				for(auto& v: subPars){
					v.push_back(right);
					ans.push_back(move(v));
				}
			}
		}
		vmap[s]=ans;
		return ans;
    }
public:
    vector<vector<string>> partition(string s) {
		prepare(s);
		return _partition(s,0,s.size());
	}
};

int main()
{

    //Stdin redirect
    //freopen("input.txt","r",stdin);

    //istream_iterator<string> iit(cin),eit;
    //copy(iit,eit,back_inserter(testCases));
	Solution sol;
	string s="aab";
	auto pars=sol.partition(s);
	for(auto& vec: pars){
		printVec(vec);
		cout<<endl;
	}
    return 0;
}


