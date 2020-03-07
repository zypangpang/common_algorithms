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
	vector<vector<int>> ans;
	void _subset(int k,vector<int> const& nums,vector<int>& res){
		if(k>=nums.size()){
			ans.push_back(res);
			return;
		}
		_subset(k+1,nums,res);
		res.push_back(nums[k]);
		_subset(k+1,nums,res);
		res.pop_back();
	}
	vector<int> getSubset(int k,vector<int> const& s){
		vector<int> ans;
		for(int i=0;i<s.size();++i){
			if(k&1<<i) ans.push_back(s[i]);
		}
		return ans;
	}
public:
	vector<vector<int>> subsetsRecur(vector<int>& nums){
		vector<int> res;
		_subset(0,nums,res);
		return ans;
	}

    vector<vector<int>> subsetsIter(vector<int>& nums) {
		vector<vector<int>> ans;
		ans.push_back(vector<int>());
		for(auto cur: nums){
			vector<vector<int>> t=ans;
			for(auto& x: ans){
				x.push_back(cur);
			}
			ans.insert(ans.end(),move(t.begin()),move(t.end()));
		}
		
		return ans;
    }
	vector<vector<int>> subsetBit(vector<int>& nums){
		for(int i=0;i<1<<nums.size();++i){
			ans.push_back(getSubset(i,nums));
		}
		return ans;
	}
};

int main()
{
    //Stdin redirect
    //freopen("input.txt","r",stdin);

    //istream_iterator<string> iit(cin),eit;
    //copy(iit,eit,back_inserter(testCases));
	vector<int> a{1,2,3};

	Solution sol;
	auto const& x=sol.subsetBit(a);
	for(auto const& v: x){
		printVec(v);
		cout<<endl;
	}

    return 0;
}


