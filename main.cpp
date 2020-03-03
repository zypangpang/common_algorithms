#include <iterator>
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <cassert>
#include <chrono>
#include <array>

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
	bool _canJump(int x,vector<int> const& nums,vector<int>& can){
		if(can[x]!=-1) return can[x]==1;
		if(x==nums.size()-1){
			can[x]=1;
			return true;
		}
		int maxSteps=x+nums[x]>=nums.size()?nums.size()-x-1:nums[x];
		for(int i=maxSteps;i>0;--i){
			if(_canJump(x+i,nums,can)){
				can[x+i]=1;
				return true;
			}else
			  can[x+i]=0;
		}
		can[x]=0;
		return false;
	}
public:
    bool canJump(vector<int>& nums) {
		int n=nums.size();
		int good=n-1;
		for(int i=n-2;i>=0;--i){
			int maxSteps=i+nums[i]>=n?n-i-1:nums[i];
			if(i+maxSteps>=good)
			  good=i;

		}
		return good==0;
    }
};;

int main()
{
    //Stdin redirect
    //freopen("input.txt","r",stdin);

    //istream_iterator<string> iit(cin),eit;
    //copy(iit,eit,back_inserter(testCases));
	
	vector<int> a{3};

	Solution sol;
	cout<<sol.canJump(a)<<endl;

    return 0;
}


